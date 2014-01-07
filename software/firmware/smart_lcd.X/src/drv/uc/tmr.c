/**
 * @file tmr.c
 * @brief hardware timer handling
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
 *
 * TODO: refactor functions, too much copy / paste !
 * TIMER#   PRIORITY      USAGE
 *   1      1.1 (lower)   sys/ticks (1000Hz)
 *   2      N/A           (spare) used for pwm generation, not accessible here
 *   3      3.1           touchscreen isr
 *   4      4.1           none
 *   5      5.1 (higher)  none
 *
 * Copyright (C) <2013>  Duboisset Philippe <duboisset.philippe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include "tmr.h"
 #include "hw_config.h"

/**
 * private variables definition
 */
static void (*tmr1PtrCallback) (void) = NULL;
static uint8_t timer1Configured = 0;
static void (*tmr3PtrCallback) (void) = NULL;
static uint8_t timer3Configured = 0;
static void (*tmr4PtrCallback) (void) = NULL;
static uint8_t timer4Configured = 0;
static void (*tmr5PtrCallback) (void) = NULL;
static uint8_t timer5Configured = 0;

/**
 * private functions prototypes
 */
static int8_t SetTimerFrequency(uint32_t desiredFrequency, uint16_t *tmrRegisterValue);


/**
 * @function TmrSetFrequency
 * @brief configure a given timer with a desired frequency
 * @param tmr_t tmr_id: timer id
 * @param uint32_t desiredFrequency: desired frequency, in Hz
 * @return int8_t: 0 sucess, otherwise error
 */
int8_t TmrSetFrequency(tmr_t tmr_id, uint32_t desiredFrequency) {

  uint16_t tmrValue = 0xFFFF;
  int8_t res = -1;

  if(SetTimerFrequency(desiredFrequency, &tmrValue) == 0) {
    switch(tmr_id) {
      case TMR_1:
        TmrStop(TMR_1);
        mT1ClearIntFlag();
        ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1 | T1_INT_SUB_PRIOR_1);
        OpenTimer1(T1_SOURCE_INT | T1_PS_1_8 | T1_IDLE_CON, tmrValue);
        timer1Configured = 1;
        res = 0;
        break;
      case TMR_3:
        TmrStop(TMR_3);
        mT3ClearIntFlag();
        ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_3 | T3_INT_SUB_PRIOR_1);
        OpenTimer3(T3_SOURCE_INT | T3_PS_1_8 | T3_IDLE_CON, tmrValue);
        timer3Configured = 1;
        res = 0;
        break;
      case TMR_4:
        TmrStop(TMR_4);
        mT4ClearIntFlag();
        ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_4 | T4_INT_SUB_PRIOR_1);
        OpenTimer4(T4_SOURCE_INT | T4_PS_1_8 | T4_IDLE_CON, tmrValue);
        timer4Configured = 1;
        res = 0;
        break;
      case TMR_5:
        TmrStop(TMR_5);
        mT5ClearIntFlag();
        ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_5 | T5_INT_SUB_PRIOR_1);
        OpenTimer5(T5_SOURCE_INT | T5_PS_1_8 | T5_IDLE_CON, tmrValue);
        timer5Configured = 1;
        res = 0;
        break;
      default:
        break;
    }
  }
  return res;
}


/**
 * @function TmrSetCallback
 * @brief associate a callback function to a given timer
 * @param tmr_t tmr_id: timer id
 * @param *ptrCallback: pointer to a void function(void)
 * @return none
 */
void TmrSetCallback(tmr_t tmr_id, void (*ptrCallback) (void)) {
  switch(tmr_id) {
    case TMR_1:
      TmrStop(TMR_1);
      tmr1PtrCallback = ptrCallback;
      break;
    case TMR_3:
      TmrStop(TMR_3);
      tmr3PtrCallback = ptrCallback;
      break;
    case TMR_4:
      TmrStop(TMR_4);
      tmr4PtrCallback = ptrCallback;
      break;
    case TMR_5:
      TmrStop(TMR_5);
      tmr5PtrCallback = ptrCallback;
      break;
    default:
      break;
  }
}


/**
 * @function TmrLaunch
 * @brief enable a given timer, if this one is correctly configured
 * @param tmr_t tmr_id: timer id
 * @return none
 */
void TmrLaunch(tmr_t tmr_id) {
  switch(tmr_id) {
    case TMR_1:
      if(timer1Configured == 1 && tmr1PtrCallback != NULL) {
        mT1ClearIntFlag();
        T1CONSET = 0x8000;
      }
      break;
    case TMR_3:
      if(timer3Configured == 1 && tmr3PtrCallback != NULL) {
        mT3ClearIntFlag();
        T3CONSET = 0x8000;
      }
      break;
    case TMR_4:
      if(timer4Configured == 1 && tmr4PtrCallback != NULL) {
        mT4ClearIntFlag();
        T4CONSET = 0x8000;
      }
      break;
    case TMR_5:
      if(timer5Configured == 1 && tmr5PtrCallback != NULL) {
        mT5ClearIntFlag();
        T5CONSET = 0x8000;
      }
      break;
    default:
      break;
  }
}


/**
 * @function TmrStop
 * @brief stop a given timer
 * @param tmr_t tmr_id: timer id
 * @return none
 */
void TmrStop(tmr_t tmr_id) {
  switch(tmr_id) {
    case TMR_1:
      T1CONCLR = 0x8000;
      break;
    case TMR_3:
      T3CONCLR = 0x8000;
      break;
    case TMR_4:
      T4CONCLR = 0x8000;
      break;
    case TMR_5:
      T5CONCLR = 0x8000;
      break;
  }
}


/**
 * @function Timer1Handler
 * @brief Timer1 interruption handler
 * @param none
 * @return none
 */
void __ISR(_TIMER_1_VECTOR, ipl1) Timer1Handler(void) {
  tmr1PtrCallback();
  mT1ClearIntFlag();
}


/**
 * @function Timer3Handler
 * @brief Timer3 interruption handler
 * @param none
 * @return none
 */
void __ISR(_TIMER_3_VECTOR, ipl3) Timer3Handler(void) {
  tmr3PtrCallback();
  mT3ClearIntFlag();
}


/**
 * @function Timer4Handler
 * @brief Timer4 interruption handler
 * @param none
 * @return none
 */
void __ISR(_TIMER_4_VECTOR, ipl4) Timer4Handler(void) {
  tmr4PtrCallback();
  mT4ClearIntFlag();
}


/**
 * @function Timer5Handler
 * @brief Timer5 interruption handler
 * @param none
 * @return none
 */
void __ISR(_TIMER_5_VECTOR, ipl5) Timer5Handler(void) {
  tmr5PtrCallback();
  mT5ClearIntFlag();
}


/**
 * private functions implementation
 */

 /**
 * @function SetTimerFrequency
 * @brief compute an APPROXIMATE tmr register value according to a given frequency
 * @param uint32_t desiredFrequency: desired frequency, in Hz
 * @param *tmrRegisterValue: pointer to use to write the corresponding register value
 * @return int8_t: -1 error (freq out of scope), 0 ok
 *
 * hardware timer input stage:
 *               ---------      --------------
 *  PER_CLK --->|PRESCALER|--->|TMRx (16 bits)|<-----
 *               ---------      --------------       |
 *                                   |  |            | reset TMRx & generate interrupt
 *                              --------------       |
 *                             |PRx compare   |------
 *                              --------------  TMRx == PRx?
 *
 */
static int8_t SetTimerFrequency(uint32_t desiredFrequency, uint16_t *tmrRegisterValue) {

  uint32_t  tmrValue;
  uint16_t prescale;
  int8_t res = -1;

  if(desiredFrequency > 0 && tmrRegisterValue != NULL) {

    prescale = 8;  /*fixed prescale value to simplify -> 1 pulse every 0.1us @ 80MHz*/
    tmrValue = (uint32_t) PER_CLK / (desiredFrequency * prescale);

    /*Check is the tmrValue value fits in TMRx maximum value (16bits)*/
    if(tmrValue >= 1 && tmrValue <= 65535) {
      *tmrRegisterValue = (uint16_t) tmrValue;
      res = 0;
    }
  }

  return res;
}
