/**
 * @file gui_demo_valuebox.c
 * @brief value box & sliders demo
 * @author Duboisset Philippe
 * @version 0.1b
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

#include "gui_demo_valuebox.h"

#ifdef INCLUDE_GUI_DEMO

/*group #id*/
#define GRP_DEFAULT           0
#define GRP_NOTIFIED          1
#define GRP_DISABLED          2

/*widget' signals*/
#define SIG_DISABLE_OBJ       3
#define SIG_NOTIFY_OBJ        4

/**
 * local function
 */
void Gui_DemoValueBoxHandler(signal_t sig);

/**
 * local variables
 */
static uint8_t disableObj, notifyObj, u8Slider = 128;
static float fVal;
static uint16_t u16Val;
static uint32_t u32Val;


/**
 * @function Gui_DemoValueBox
 * @brief value box demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoValueBox(signal_t sig) {

  rect_st rec;
  disableObj = notifyObj = 0;

  Gui_DemoNewPage("Text area");

  /**
   * some value boxes
   */
  rec = GUI_Rect(10, 20, 220, 19);
  GUI_W_TextAdd(&rec, "Default value box, (e.g. float):");
  rec = GUI_Rect(230, 20, 75, 19);
  GUI_W_ValueBoxAdd(&rec, &fVal, BOX_T_FLOAT, "%.3f");

  rec = GUI_Rect(10, 42, 220, 19);
  GUI_W_TextAdd(&rec, "Value box with format string:");
  rec = GUI_Rect(230, 42, 75, 19);
  GUI_W_ValueBoxAdd(&rec, &fVal, BOX_T_FLOAT, "I=%.2f µA");

  rec = GUI_Rect(10, 70, 300, 19);
  GUI_W_TextAdd(&rec, "Value boxes of different type, format & style:");
  rec = GUI_Rect(10, 92, 55, 19);
  GUI_W_ValueBoxAdd(&rec, &u8Slider, BOX_T_INT8, "i8:%d");
  rec = GUI_Rect(75, 92, 55, 19);
  GUI_W_ValueBoxAdd(&rec, &u8Slider, BOX_T_UINT8, "u8:%d");
  rec = GUI_Rect(140, 92, 75, 19);
  GUI_W_ValueBoxAdd(&rec, &u16Val, BOX_T_INT16, "i16:%d");
  rec = GUI_Rect(225, 92, 75, 19);
  GUI_W_ValueBoxAdd(&rec, &u16Val, BOX_T_UINT16, "u16:%d");

  rec = GUI_Rect(10, 114, 110, 19);
  GUI_W_ValueBoxAdd(&rec, &u32Val, BOX_T_INT32, "i32:%d");

  SetColor(G_COL_TEXT, P2D_Color(255, 0, 0));
  rec = GUI_Rect(125, 114, 65, 19);
  GUI_W_ValueBoxAdd(&rec, &u16Val, BOX_T_UINT16, "0x%04X");
  SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));

  SetFont(G_FONT_DIGIT);
  rec = GUI_Rect(195, 114, 65, 19);
  GUI_W_ValueBoxAdd(&rec, &u16Val, BOX_T_UINT16, "%04d");
  SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(10, 136, 125, 19);
  GUI_SetGroup(GRP_DISABLED);
  GUI_W_ValueBoxAdd(&rec, &u8Slider, BOX_T_UINT8, "Disable me! u8:%d");
  GUI_SetGroup(GRP_DEFAULT);

  rec = GUI_Rect(140, 136, 135, 19);
  GUI_SetGroup(GRP_NOTIFIED);
  GUI_W_ValueBoxAdd(&rec, &u8Slider, BOX_T_UINT8, "Notify me! u8:%d");
  GUI_SetGroup(GRP_DEFAULT);

  /**
   * some sliders
   */
  GUI_SetGroup(GRP_DISABLED);
  rec = GUI_Rect(20, 165, 255, 15);
  GUI_W_SliderAdd(&rec, &u8Slider);
  rec = GUI_Rect(285, 117, 15, 85);
  GUI_W_SliderAdd(&rec, &u8Slider);
  GUI_SetGroup(GRP_DEFAULT);

  /**
   * disable control
   */
  rec = GUI_Rect(10, 185, 110, 19);
  GUI_W_CheckBoxAdd(&rec, "Notify objects", &notifyObj);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_NOTIFY_OBJ);

  rec = GUI_Rect(130, 185, 115, 19);
  GUI_W_CheckBoxAdd(&rec, "Disable objects", &disableObj);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DISABLE_OBJ);

  /* => page creation is now completed. Jump to the page's handler*/
  GUI_SetUserTask(Gui_DemoValueBoxHandler);
}


/**
 * @function Gui_DemoValueBoxHandler
 * @brief value box demo
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
void Gui_DemoValueBoxHandler(signal_t sig) {

  /**
   * user process
   */
   fVal = (float) u8Slider / 255;
   u16Val = fVal * 0xFFFF;
   u32Val = fVal * 0xFFFFFFFF;

  switch(sig) {

    /*widget control*/
    case SIG_NOTIFY_OBJ:
      notifyObj = !notifyObj;
      GUI_GroupNotify(GRP_NOTIFIED, notifyObj);
      break;
    case SIG_DISABLE_OBJ:
      disableObj = !disableObj;
      GUI_GroupDisable(GRP_DISABLED, disableObj);
      break;

    /*'menu' button*/
    case SIG_DEMO_MENU:
      GUI_SetUserTask(Gui_Demo);
      break;

      default:
      break;
  }
}

#endif
