/**
 * @file touchscreen.c
 * @brief resistive touchscreen driver
 * @author Duboisset Philippe
 * @version 0.3b
 * @date (yyyy-mm-dd)
 * 2013-07-13 initial version
 * 2013-09-22 modification of TouchScreenCalib(NULL)
 * 2013-09-26 modification to avoid the parasit capacitance error
 *
 * Copyright (C) <2013>  Duboisset Philippe <duboisset.philippe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "touchscreen.h"
#include "adc.h"
#include "gpio.h"
#include "sem.h"
#include "tmr.h"

#define X_P_PORT  B
#define X_P_PIN   8
#define X_N_PORT  B
#define X_N_PIN   10
#define Y_P_PORT  B
#define Y_P_PIN   9
#define Y_N_PORT  B
#define Y_N_PIN   11

#define NB_SAMPLE         6   /*number of sample for filtering; shall be >= 2 to make the filter effective*/
#define TOUCH_TRIG        100 /*touch detection threeshold; empiric value*/
#define SAMPLE_TOLERANCE  12  /*tolerance between successive samples; empiric value*/

/*
 * Local functions
 */
static void FlushSamples(void);
static uint16_t Delta(uint16_t a, uint16_t b);
static uint16_t Average(volatile uint16_t *p, uint8_t nbSample);
static void TouchScreenIsr(void);

/*
 * Static variable used by the touchscreen ISR
 */
static volatile uint16_t xRead[NB_SAMPLE], yRead[NB_SAMPLE];
static volatile uint8_t state, posSample;
static volatile sem_t sem;
static volatile bool bTouch;

/*
 * Static variable used for calibration
 */
static float cx = 0.0f;
static float ox = 0.0f;
static float cy = 0.0f;
static float oy = 0.0f;



/**
 * @function TouchScreenEnable
 * @brief turn ON the touchscreen; overwrite ADC & TMR3 configuration
 * @param none
 * @return none
 */
void TouchScreenEnable(void) {

  GPIO_SetPin(Y_N_PORT, Y_N_PIN, 0);      /*preconfigured for 0V  output*/
  GPIO_SetPin(Y_P_PORT, Y_P_PIN, 1);      /*preconfigured for 3V3 output*/
  GPIO_SetPin(X_N_PORT, X_N_PIN, 0);      /*preconfigured for 0V  output*/
  GPIO_SetPin(X_P_PORT, X_P_PIN, 1);      /*preconfigured for 3V3 output*/
  GPIO_SetPinMode(Y_P_PIN, GPIO_ANALOG);  /*Y_P_PIN as analog input or digital output*/
  GPIO_SetPinMode(X_P_PIN, GPIO_ANALOG);  /*X_P_PIN as analog input or digital output*/

  ADC_Init();

  /*variable init.*/
  FlushSamples();
  state = 0;
  bTouch = false;
  sem = SEM_UNLOCKED;

  /*set up & run touchscreen ISR @ 4kHz*/
  TmrSetFrequency(TMR_3, 4000);
  TmrSetCallback(TMR_3, TouchScreenIsr);
  TmrLaunch(TMR_3);
}


/**
 * @function TouchScreenDisable
 * @brief turn OFF the touchscreen
 * @param none
 * @return none
 */
void TouchScreenDisable(void) {

  /*kill touchscreen ISR*/
  TmrStop(TMR_3);

  /*consider touchscreen as released if disabled*/
  bTouch = false;

  /*release plate polarization, if any*/
  GPIO_SetPinDirection(X_N_PORT, X_N_PIN, GPIO_PIN_INPUT);
  GPIO_SetPinDirection(X_P_PORT, X_P_PIN, GPIO_PIN_INPUT);
  GPIO_SetPinDirection(Y_N_PORT, Y_N_PIN, GPIO_PIN_INPUT);
  GPIO_SetPinDirection(Y_P_PORT, Y_P_PIN, GPIO_PIN_INPUT);
}


/**
 * @function TouchScreenIsPressed
 * @brief return the touch screen state
 * @param none
 * @return bool: true if touched, false otherwise
 */
bool TouchScreenIsPressed(void) {
  return bTouch;
}


/**
 * @function TouchScreenReadRaw
 * @brief read the touchscreen filtered raw data
 * @param uint16_t *x, *y: x & y coordinate, in range[0 - (ADC_MAX_VALUE-1)]; ADC_RAW_ERR if touchscreen released
 * @return none
 */
void TouchScreenReadRaw(uint16_t *x, uint16_t *y) {

  static uint16_t oldX = ADC_MAX_VALUE, oldY = ADC_MAX_VALUE;
  uint16_t avgX, avgY, cnt;
  bool bBounce = false;

  if(x != NULL && y != NULL) {

    /*lock touchscreen ISR*/
    SemLock(sem);

    /*check if the touchscreen is actually pressed*/
    if(bTouch == true) {

      /*compute average x & y*/
      avgX = Average(xRead, NB_SAMPLE);
      avgY = Average(yRead, NB_SAMPLE);

      /*check if a sample is not too far (possible bounces issue)*/
      for(cnt = 0; bBounce == false && cnt < NB_SAMPLE; cnt++) {
        if(Delta(avgX, xRead[cnt]) > SAMPLE_TOLERANCE) bBounce = true;
        if(Delta(avgY, yRead[cnt]) > SAMPLE_TOLERANCE) bBounce = true;
      }
      /*if no bounce issue, return the new point*/
      if(bBounce == false) {
        *x = avgX;
        *y = avgY;
      }
      /*if bounce issue and screen still pressed, return the previous point*/
      else {
        *x = oldX;
        *y = oldY;
      }
    }
    else {
      *x = ADC_RAW_ERR;
      *y = ADC_RAW_ERR;
    }

    /*always save current result*/
    oldX = *x;
    oldY = *y;

    /*release ISR*/
    SemUnlock(sem);
  }
}


/**
 * @function TouchScreenRead
 * @brief read the touchscreen filtered coordinate (relative to screen dimension)
 * @param coord_t *x: range[0 - LCD_GetWidth()-1]; -1 if touchscreen released
 * @param coord_t *y: range[0 - LCD_GetHeight()-1]; -1 if touchscreen released
 * @return none
 */
void TouchScreenRead(coord_t *x, coord_t *y) {

  uint16_t xt, yt;

  if(x != NULL && y != NULL) {

    /*read touchscreen raw*/
    TouchScreenReadRaw(&xt, &yt);

    /*touchscreen pressed*/
    if(xt != ADC_MAX_VALUE && yt != ADC_MAX_VALUE) {

      /*convert x & y*/
      *x = (coord_t) (cx*xt + ox);
      *y = (coord_t) (cy*yt + oy);

      /*check overlap*/
      if(*x < 0) *x = 0;
      else if(*x >= LCD_GetWidth()) *x = LCD_GetWidth() - 1;
      if(*y < 0) *y = 0;
      else if(*y >= LCD_GetHeight()) *y = LCD_GetHeight() - 1;
    }
    /*touchscreen released*/
    else {
      *x = -1;
      *y = -1;
    }
  }
}


/**
 * @function TouchScreenCalib
 * @brief set calibration parameters, based on 2 points
 * @param const touch_calib_st *z: calibration points (touchscreen data & relative coordinates)
 * @return int8_t: 0=success, -1=error (invalid parameters leading to /0 )
 */
int8_t TouchScreenCalib(const touch_calib_st *z) {

  int8_t res = -1;
  int16_t denom;

  if(z != NULL) {

    do {

      cx = z->xd1 - z->xd2;
      denom = z->xt1 - z->xt2;
      if(denom == 0) break;
      else cx /= denom;

      ox = z->xt1 * z->xd2 - z->xt2 * z->xd1;
      denom = z->xt1 - z->xt2;
      if(denom == 0) break;
      else ox /= denom;

      cy = z->yd1 - z->yd2;
      denom = z->yt1 - z->yt2;
      if(denom == 0) break;
      else cy /= denom;

      oy = z->yt1 * z->yd2 - z->yt2 * z->yd1;
      denom = z->yt1 - z->yt2;
      if(denom == 0) break;
      else oy /= denom;

      res = 0;

    } while(0);
  }

  /*in case of errors, set coeff to default values*/
  if(res < 0) {
    cx = 0.3897f;
    ox = -31.52f;
    cy = -0.3174f;
    oy = 277.8f;
  }

  return res;
}


/**
 * @function TouchScreenIsr
 * @brief ...touchscreen isr
 * @param none
 * @return none
 */
static void TouchScreenIsr(void) {

  if(IsSemUnlocked(sem)) {

    switch(state) {

      /*touch detection settings*/
      case 0:
        GPIO_SetPinDirection(X_N_PORT, X_N_PIN, GPIO_PIN_OUTPUT);
        GPIO_SetPinDirection(X_P_PORT, X_P_PIN, GPIO_PIN_INPUT);
        GPIO_SetPinDirection(Y_N_PORT, Y_N_PIN, GPIO_PIN_INPUT);
        GPIO_SetPinDirection(Y_P_PORT, Y_P_PIN, GPIO_PIN_INPUT);
        ADC_SelectChannel(Y_P_PIN);
        state++;
        break;

      /*start sampling*/
      case 1:
        ADC_StartSampling();
        state++;
        break;

      /*start conversion & process result*/
      case 2:
        ADC_StartConversion();
        while(ADC_IsBusy());
        if(ADC_Read() > TOUCH_TRIG) {
          if(bTouch == true) {
            FlushSamples();
            bTouch = false;
          }
          state = 0;
        }
        else {
          bTouch = true;
          posSample++;
          posSample = posSample % NB_SAMPLE;
          state++;
        }
        break;

      /*Y read: release Y plate, polarize X plate*/
      case 3:
        GPIO_SetPinDirection(Y_N_PORT, Y_N_PIN, GPIO_PIN_OUTPUT); /*discharge the parasit capacitance*/
        GPIO_SetPinDirection(Y_P_PORT, Y_P_PIN, GPIO_PIN_INPUT);
        GPIO_SetPinDirection(X_N_PORT, X_N_PIN, GPIO_PIN_OUTPUT);
        GPIO_SetPinDirection(X_P_PORT, X_P_PIN, GPIO_PIN_OUTPUT);
        GPIO_SetPinDirection(Y_N_PORT, Y_N_PIN, GPIO_PIN_INPUT);
        ADC_SelectChannel(Y_P_PIN);
        state++;
        break;

      /*start sampling Y*/
      case 4:
        ADC_StartSampling();
        state++;
        break;

      /*Y conversion*/
      case 5:
        ADC_StartConversion();
        while(ADC_IsBusy());
        yRead[posSample] = ADC_Read();
        state++;
        break;

      /*X read: release X plate, polarize Y plate*/
      case 6:
        GPIO_SetPinDirection(X_N_PORT, X_N_PIN, GPIO_PIN_OUTPUT); /*discharge the parasit capacitance*/
        GPIO_SetPinDirection(X_P_PORT, X_P_PIN, GPIO_PIN_INPUT);
        GPIO_SetPinDirection(Y_N_PORT, Y_N_PIN, GPIO_PIN_OUTPUT);
        GPIO_SetPinDirection(Y_P_PORT, Y_P_PIN, GPIO_PIN_OUTPUT);
        GPIO_SetPinDirection(X_N_PORT, X_N_PIN, GPIO_PIN_INPUT);
        ADC_SelectChannel(X_P_PIN);
        state++;
        break;

      /*start sampling X*/
      case 7:
        ADC_StartSampling();
        state++;
        break;

      /*X conversion*/
      case 8:
        ADC_StartConversion();
        while(ADC_IsBusy());
        xRead[posSample] = ADC_Read();
        state = 0;
        break;

      default:
        state = 0;
        break;
    }
  }
}


/**
 * @function FlushSamples
 * @brief clear sampled point arrays
 * @param none
 * @return none
 */
static void FlushSamples(void) {
  for(posSample = 0; posSample < NB_SAMPLE; posSample++) {
    xRead[posSample] = ADC_MAX_VALUE;
    yRead[posSample] = ADC_MAX_VALUE;
  }
  posSample = 0;
}


/**
 * @function Delta
 * @brief return |a-b|
 * @param uint16_t a,b
 * @return uint16_t: |a-b|
 */
static uint16_t Delta(uint16_t a, uint16_t b) {
  uint16_t res;
  if(a < b) res = b - a;
  else res = a - b;
  return res;
}


/**
 * @function Average
 * @brief return the average of an array
 * @param volatile uint16_t *p: array; shall be != NULL
 * @param uint8_t nbSample: size of array; shall be > 0
 * @return uint16_t: average
 */
static uint16_t Average(volatile uint16_t *p, uint8_t nbSample) {
  uint16_t cnt, avg = 0;
  for(cnt = 0; cnt < nbSample; cnt++) {
    avg += p[cnt];
  }
  avg = avg / nbSample;
  return avg;
}
