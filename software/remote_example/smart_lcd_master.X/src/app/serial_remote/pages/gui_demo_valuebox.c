/**
 * @file gui_demo_valuebox.c
 * @brief value box & sliders demo (serialized, master side)
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
static void Gui_DemoValueBoxHandler(void);
static void Gui_DemoValueBoxRead(void);

/**
 * local variables
 */
static uint8_t disableObj, notifyObj, u8Slider = 0;


/**
 * SSM description
 */
enum {

  /*@0*/
  OFFSET_FLOAT = 0,
    _OFFSET_FLOAT,__OFFSET_FLOAT,___OFFSET_FLOAT,
  
  /*@4*/
  OFFSET_INT32,
    _OFFSET_INT32,__OFFSET_INT32,___OFFSET_INT32,
  
  /*@8*/
  OFFSET_UINT16,
    _OFFSET_UINT16,
  
  /*@10*/
  OFFSET_INT8,
  
  OFFSET_DISABLE_OBJ,
  OFFSET_NOTIFY_OBJ,
  
  MEM_SIZE
};


/**
 * @function Gui_DemoValueBox
 * @brief value box demo
 * @param none
 * @return none
 */
void Gui_DemoValueBox(void) {

  rect_st rec;
  disableObj = notifyObj = 0;

  Gui_DemoNewPage("Text area");
  
  R_MEM_Memset(OFFSET_FLOAT, MEM_SIZE, 0);

  /**
   * some value boxes
   */
  rec = GUI_Rect(10, 20, 220, 19);
  R_GUI_W_TextAdd(&rec, "Default value box, (e.g. float):");
  rec = GUI_Rect(230, 20, 75, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_FLOAT, BOX_T_FLOAT, "%.3f");

  rec = GUI_Rect(10, 42, 220, 19);
  R_GUI_W_TextAdd(&rec, "Value box with format string:");
  rec = GUI_Rect(230, 42, 75, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_FLOAT, BOX_T_FLOAT, "I=%.2f µA");

  rec = GUI_Rect(10, 70, 300, 19);
  R_GUI_W_TextAdd(&rec, "Value boxes of different type, format & style:");
  rec = GUI_Rect(10, 92, 55, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_INT8, BOX_T_INT8, "i8:%d");
  rec = GUI_Rect(75, 92, 55, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_INT8, BOX_T_UINT8, "u8:%d");
  rec = GUI_Rect(140, 92, 75, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_UINT16, BOX_T_INT16, "i16:%d");
  rec = GUI_Rect(225, 92, 75, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_UINT16, BOX_T_UINT16, "u16:%d");

  rec = GUI_Rect(10, 114, 110, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_INT32, BOX_T_INT32, "i32:%d");

  R_GUI_SetColor(G_COL_TEXT, P2D_Color(255, 0, 0));
  rec = GUI_Rect(125, 114, 65, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_UINT16, BOX_T_UINT16, "0x%04X");
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));

  R_GUI_SetFont(G_FONT_DIGIT);
  rec = GUI_Rect(195, 114, 65, 19);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_UINT16, BOX_T_UINT16, "%04d");
  R_GUI_SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(10, 136, 125, 19);
  R_GUI_SetGroup(GRP_DISABLED);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_INT8, BOX_T_UINT8, "Disable me! u8:%d");
  R_GUI_SetGroup(GRP_DEFAULT);

  rec = GUI_Rect(140, 136, 135, 19);
  R_GUI_SetGroup(GRP_NOTIFIED);
  R_GUI_W_ValueBoxAdd(&rec, OFFSET_INT8, BOX_T_UINT8, "Notify me! u8:%d");
  R_GUI_SetGroup(GRP_DEFAULT);

  /**
   * some sliders
   */
  R_GUI_SetGroup(GRP_DISABLED);
  rec = GUI_Rect(20, 165, 255, 15);
  R_GUI_W_SliderAdd(&rec, OFFSET_INT8);
  rec = GUI_Rect(285, 117, 15, 85);
  R_GUI_W_SliderAdd(&rec, OFFSET_INT8);
  R_GUI_SetGroup(GRP_DEFAULT);

  /**
   * disable control
   */
  rec = GUI_Rect(10, 185, 110, 19);
  R_GUI_W_CheckBoxAdd(&rec, "Notify objects", OFFSET_NOTIFY_OBJ);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_NOTIFY_OBJ);

  rec = GUI_Rect(130, 185, 115, 19);
  R_GUI_W_CheckBoxAdd(&rec, "Disable objects", OFFSET_DISABLE_OBJ);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DISABLE_OBJ);

  /* => page creation is now completed. Jump to the page's handler*/
  R_GUI_SetTask(Gui_DemoValueBoxRead);
}


/**
 * @function Gui_DemoValueBoxRead
 * @brief Send <read signal> & <read sliderValue> requests to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoValueBoxRead(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_MEM_ReadU8(OFFSET_INT8);
    R_GUI_SetTask(Gui_DemoValueBoxHandler);
  }
}


/**
 * @function Gui_DemoRead
 * @brief wait requests & handle them
 * @param none
 * @return none
 */
static void Gui_DemoValueBoxHandler(void) {

  float fVal;
  uint16_t u16Val;
  uint32_t u32Val;
  
  R_GUI_SetTask(Gui_DemoValueBoxRead);
  
  signal_t sig = RxGetU16();
  uint8_t tmp = RxGetU8();

  if(RxStatus() == 0) {
  
    if(tmp != u8Slider) {
      u8Slider = tmp;
      
      fVal = (float) u8Slider / 255;
      u16Val = fVal * 0xFFFF;
      u32Val = fVal * 0xFFFFFFFF;
      
      R_MEM_WriteU32(OFFSET_FLOAT, *((uint32_t *) &fVal));  /*alias: pls fixme*/
      R_MEM_WriteU32(OFFSET_INT32, u32Val);
      R_MEM_WriteU16(OFFSET_UINT16, u16Val);
    }

    switch(sig) {

      /*widget control*/
      case SIG_NOTIFY_OBJ:
        notifyObj = !notifyObj;
        R_GUI_GroupNotify(GRP_NOTIFIED, notifyObj);
        R_MEM_WriteU8(OFFSET_NOTIFY_OBJ, notifyObj);
        break;
      case SIG_DISABLE_OBJ:
        disableObj = !disableObj;
        R_GUI_GroupDisable(GRP_DISABLED, disableObj);
        R_MEM_WriteU8(OFFSET_DISABLE_OBJ, disableObj);
        break;

      /*'menu' button*/
      case SIG_DEMO_MENU:
        R_GUI_SetTask(Gui_Demo);
        break;

        default:
        break;
    }
  }
}
