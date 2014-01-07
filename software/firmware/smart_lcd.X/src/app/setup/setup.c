/**
 * @file setup.c
 * @brief quick & dirty setup menu
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

#include "setup.h"
#include "p2d.h"
#include "resources.h"
#include "touchscreen.h"
#include "delay.h"
#include "timer.h"
#include "gui_demo.h"
#include "touchCalib.h"
#include "usr_main.h"
#include "serial_remote.h"
#include "gamma.h"

/**
 * Local variables
 */
static timer_t timeout;
static uint16_t itemSelected = 0;
static bool bWasPressed;

/**
 * Local functions
 */
static void BootTask(void);
static void SetupMenuHandleTask(void);


/**
 * @function SetupTask
 * @brief First task to be executed; enter setup if touchscreen pressed, run BootTask otherwise
 * @param none
 * @return none
 */
void SetupTask(void) {

  TouchLoadConfig();
  GammaLoadConfig();

  /*enter setup if the touchscreen is pressed during the power on*/
  if(TouchScreenIsPressed()) {
    pCurrentTask = &SetupMenuDisplayTask;
  }
  else {
    pCurrentTask = &BootTask;
  }
}


/**
 * @function BootTask
 * @brief launch the main task, according to SMART_TFT_SLAVE_MODE flag
 * @param none
 * @return none
 */
static void BootTask(void) {
  #ifdef SMART_TFT_SLAVE_MODE
  pCurrentTask = &SerialRemoteTask;
  #else
  pCurrentTask = &UserTask;
  #endif
}


/**
 * Some defines & variables declaration for setup menu
 */
#ifdef INCLUDE_GUI_DEMO
  #define SETUP_ITEM_CNT 4
#else
  #define SETUP_ITEM_CNT 3
#endif

typedef struct {
  const char *title;
  void (*pFunc) (void);
} setup_item_st;

static const setup_item_st setupItems[SETUP_ITEM_CNT] = {
  {"Exit setup", &BootTask},
  {"Touchscreen calibration", &TouchCalibTask},
  {"Gamma adjustement", &GammaTask}
  #ifdef INCLUDE_GUI_DEMO
  , {"P2D/GUI demonstration", &Gui_DemoLaunchTask}
  #endif
};


/**
 * @function SetupMenuDisplayTask
 * @brief Display the setup screen
 * @param none
 * @return none
 */
void SetupMenuDisplayTask(void) {

  uint16_t ii;
  char str[100];
  rect_st rec;
  coord_t x = 10, y = 10;
  color_t selColor = P2D_Color(0, 150, 230), backColor = GetColor(G_COL_BACKGROUND);

  /*clear all*/
  GUI_ClearAll();
  GUI_SetUserTask(NULL);
  P2D_SetClip(NULL);  /*using P2D, so don't forget to reset the clip!*/
  P2D_Clear();
  P2D_SetFont(FontFreeSerif_4bpp_n_16);

  /*top text*/
  P2D_SetColors(COLOR_BLACK, backColor);
  P2D_PutText(x, y, "Touch the screen to select the next entry,"); y+= P2D_GetTextHeight();
  P2D_PutText(x, y, "Wait 3s to validate it."); y+= P2D_GetTextHeight();

  /*items list*/
  y += 10;
  for(ii = 0; ii < SETUP_ITEM_CNT; ii++) {
    if(ii == itemSelected) {

      /*fill the whole line in blue if selected*/
      P2D_SetColor(selColor);
      rec.x = x;
      rec.y = y;
      rec.w = LCD_GetWidth() - x * 2;
      rec.h = P2D_GetTextHeight();
      P2D_FillRect(&rec);
      P2D_SetColors(COLOR_WHITE, selColor);
    }
    else {
      P2D_SetColors(COLOR_BLACK, backColor);
    }

    /*display item*/
    P2D_PutText(x, y, setupItems[ii].title);
    y+= P2D_GetTextHeight();
  }

  /*bottom text*/
  y = 180;
  P2D_SetColors(COLOR_BLACK, backColor);
  P2D_PutText(x, y, "(C) 2013 Herptronix"); y+= P2D_GetTextHeight();
  sprintf(str, "SMART TFT rev. A  build %s, %s", __DATE__, __TIME__);
  P2D_PutText(x, y, str); y+= P2D_GetTextHeight();
  #ifdef SMART_TFT_SLAVE_MODE
  P2D_PutText(x, y, "Slave mode");
  #else
  P2D_PutText(x, y, "Embedded app mode");
  #endif

  timeout = GetTimeout(3000);
  bWasPressed = true;
  pCurrentTask = &SetupMenuHandleTask;
}


/**
 * @function SetupMenuHandleTask
 * @brief Handle the setup screen
 * @param none
 * @return none
 */
static void SetupMenuHandleTask(void) {

  /*act on touch transition only (released to pressed)*/
  if(TouchScreenIsPressed()) {

    /*just pressed? next item, redraw all*/
    if(bWasPressed == false) {
      itemSelected++;
      if(itemSelected >= SETUP_ITEM_CNT) itemSelected = 0;
      pCurrentTask = &SetupMenuDisplayTask;
    }
    /*just released? init. timer*/
    else {
      timeout = GetTimeout(3000);
    }
  }
  else {

    /*timer elapsed? launch the selected entry*/
    if(IsTimerElapsed(timeout)) {
      if(setupItems[itemSelected].pFunc != NULL) {
        pCurrentTask = setupItems[itemSelected].pFunc;
      }
      else {
        pCurrentTask = &BootTask;
      }
    }
  }

  bWasPressed = TouchScreenIsPressed();
}
