/**
 * @file main.c
 * @brief SMART TFT software entry point
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd) 2013-11-01
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

#include "main.h"
#include "uc.h"
#include "ticks.h"
#include "delay.h"

#include "ILI9320.h"
#include "backlight.h"
#include "touchscreen.h"

#include "p2d.h"
#include "gui.h"
#include "setup.h"

#include "rtc.h"
#include "diskio.h"
#include "ff.h"


/**
 * global variable
 */
void (*pCurrentTask) (void) = NULL;


/**
 * local variable
 */
static FATFS Fatfs;


/**
 * @function main
 * @brief entry point
 * @param none
 * @return dummy
 */
int32_t main(void) {

  timer_t tmInit;

  UcInit();       /*uc init; shall be the first one*/
  TicksInit();    /*software clock init*/
  LCD_Init();     /*start the ILI932X*/

  /* start a timer; backlight will be turned on once this timer will elapse
   * -> this avoids a white flash*/
  tmInit = GetTimeout(120);

  P2D_Init();
  GUI_Init();
  TouchScreenCalib(NULL);
  TouchScreenEnable();

  /*mount the file system*/
  disk_initialize(0);
  f_mount(0, &Fatfs);

  /* wait the 120ms timeout */
  while(IsTimerElapsed(tmInit) == false) DelayMs(1);
  BacklightInit();

  /*set the main task*/
  pCurrentTask = &SetupTask;

  /*main loop*/
  while(1) {

    /*execute the main task, if any*/
    if(pCurrentTask != NULL) pCurrentTask();

    /*GUI task*/
    GUI_DrawObjects();
    GUI_DBG_Task();

    /*software RTC task*/
    RtcTask();

    /*CPU limiter; reduces the power consumption*/
    DelayMs(1);
  }

  /*never arrive here*/
  return -1;
}
