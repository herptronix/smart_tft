/**
 * @file touchCalib.c
 * @brief quick & dirty functions for touchscreen calibration procedure
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-03
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

#include "touchCalib.h"
#include "p2d.h"
#include "touchscreen.h"
#include "timer.h"
#include "resources.h"
#include "delay.h"
#include "setup.h"
#include "ff.h"

/**
 * Local variables
 */
static timer_t tm;
static touch_calib_st calib;
static uint32_t nbSample;
static const char *str = "Press the red point during 3 seconds";
static const char *strFile = "touchscr.cfg";  /*located at the root of the SD card*/

/**
 * Local functions
 */
static void TouchSaveConfig(void);
static void TouchCalibTaskDrawP1(void);
static void TouchCalibTaskCalibP1(void);
static void TouchCalibTaskDrawP2(void);
static void TouchCalibTaskCalibP2(void);


/**
 * @function TouchLoadConfig
 * @brief Configure the touchscreen with the <touchscr.cfg> file content
 * @param none
 * @return none TODO: return & robustness enhancement
 */
void TouchLoadConfig(void) {

  FIL pFile;
  UINT byteRead;

  if(f_open(&pFile, strFile, FA_OPEN_EXISTING | FA_READ) == FR_OK) {
    if(f_read(&pFile, &calib, sizeof(calib), &byteRead) == FR_OK && byteRead == sizeof(calib)) {
      TouchScreenCalib(&calib);
    }
    f_close(&pFile);
  }
}


/**
 * @function TouchSaveConfig
 * @brief Save the touchscreen configuration in the <touchscr.cfg> file
 * @param none
 * @return none TODO: return & robustness enhancement
 */
static void TouchSaveConfig(void) {

  FIL pFile;
  UINT byteWritten;

  if(f_open(&pFile, strFile, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
    (void) f_write(&pFile, &calib, sizeof(calib), &byteWritten);
    f_close(&pFile);
  }
}


/**
 * @function TouchCalibTask
 * @brief Touchscreen calibration: init. task
 * @param none
 * @return none
 */
void TouchCalibTask(void) {

  /*calibration point: at x,y 10% / 90% of the screen*/
  calib.xd1 = (float) LCD_GetWidth() / 10;
  calib.yd1 = (float) LCD_GetHeight() / 10;
  calib.xd2 = (float) LCD_GetWidth() - calib.xd1;
  calib.yd2 = (float) LCD_GetHeight() - calib.yd1;
  calib.xt1 = 0.0f;
  calib.xt2 = 0.0f;
  calib.yt1 = 0.0f;
  calib.yt2 = 0.0f;
  pCurrentTask = TouchCalibTaskDrawP1;
}


/**
 * @function TouchCalibTaskDrawP1
 * @brief Touchscreen calibration: draw first calibration point
 * @param none
 * @return none
 */
static void TouchCalibTaskDrawP1(void) {

  /*clear all*/
  P2D_SetColor(COLOR_LIGHT_GREY);
  P2D_SetClip(NULL);
  P2D_Clear();

  /*draw the first red point*/
  P2D_SetColor(COLOR_RED);
  P2D_FillCircle(calib.xd1, calib.yd1, 4);

  /*display text*/
  P2D_SetFont(FontFreeSerif_4bpp_n_16);
  P2D_SetColors(COLOR_BLACK, COLOR_LIGHT_GREY);
  P2D_PutText(calib.xd1 + 10, calib.yd1 - (P2D_GetTextHeight() / 2), str);

  /*init. calibration*/
  pCurrentTask = TouchCalibTaskCalibP1;
  tm = GetTimeout(3000);
  nbSample = 0;

  /*wait for touchscreen release before gathering samples for the calibration*/
  while(TouchScreenIsPressed()) DelayMs(1);
}


/**
 * @function TouchCalibTaskCalibP1
 * @brief Touchscreen calibration: draw first calibration point
 * @param none
 * @return none
 */
static void TouchCalibTaskCalibP1(void) {

  uint16_t xt, yt;

  /*timer elapsed? -> user has pressed the point during 3s; save & go to next task*/
  if(IsTimerElapsed(tm)) {
    if(nbSample > 0) {
      calib.xt1 /= nbSample;
      calib.yt1 /= nbSample;
      pCurrentTask = TouchCalibTaskDrawP2;
    }
  }
  /*timer NOT elapsed && touchscreen pressed? gather samples*/
  else if(TouchScreenIsPressed()) {
    TouchScreenReadRaw(&xt, &yt);
    nbSample++;
    calib.xt1 += xt;
    calib.yt1 += yt;
  }
  /*touchscreen NOT pressed? reset timer & samples*/
  else {
    tm = GetTimeout(3000);
    nbSample = 0;
    calib.xt1 = 0;
    calib.yt1 = 0;
  }

  /*give extra time to touchscreen ISR*/
  DelayMs(5);
}


/**
 * @function TouchCalibTaskDrawP2
 * @brief Touchscreen calibration: draw second calibration point
 * @param none
 * @return none
 */
static void TouchCalibTaskDrawP2(void) {

  /*clear all*/
  P2D_SetColor(COLOR_LIGHT_GREY);
  P2D_SetClip(NULL);
  P2D_Clear();

  /*draw the second red point*/
  P2D_SetColor(COLOR_RED);
  P2D_FillCircle(calib.xd2, calib.yd2, 4);

  /*display text*/
  P2D_SetFont(FontFreeSerif_4bpp_n_16);
  P2D_SetColors(COLOR_BLACK, COLOR_LIGHT_GREY);
  P2D_PutText(calib.xd2 - P2D_GetTextWidth(str) - 10, calib.yd2 - (P2D_GetTextHeight() / 2), str);

  /*init. calibration*/
  pCurrentTask = TouchCalibTaskCalibP2;
  tm = GetTimeout(3000);
  nbSample = 0;

  /*wait for touchscreen release before gathering samples for the calibration*/
  while(TouchScreenIsPressed()) DelayMs(1);
}


/**
 * @function TouchCalibTaskCalibP1
 * @brief Touchscreen calibration: draw first calibration point
 * @param none
 * @return none
 */
static void TouchCalibTaskCalibP2(void) {

  uint16_t xt, yt;

  /*timer elapsed? -> user has pressed the point during 3s; save in file & exit*/
  if(IsTimerElapsed(tm)) {
    if(nbSample > 0) {
      calib.xt2 /= nbSample;
      calib.yt2 /= nbSample;
      pCurrentTask = SetupTask;
      TouchScreenCalib(&calib);
      TouchSaveConfig();
    }
  }
  /*timer NOT elapsed && touchscreen pressed? gather samples*/
  else if(TouchScreenIsPressed()) {
    TouchScreenReadRaw(&xt, &yt);
    nbSample++;
    calib.xt2 += xt;
    calib.yt2 += yt;
  }
  /*touchscreen NOT pressed? reset timer & samples*/
  else {
    tm = GetTimeout(3000);
    nbSample = 0;
    calib.xt2 = 0;
    calib.yt2 = 0;
  }

  /*give extra time to touchscreen ISR*/
  DelayMs(5);
}
