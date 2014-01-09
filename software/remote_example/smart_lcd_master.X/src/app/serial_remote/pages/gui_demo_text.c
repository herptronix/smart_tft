/**
 * @file gui_demo_text.c
 * @brief text area demo (serialized, master side)
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

#include "gui_demo_text.h"

/*group #id*/
#define GRP_DEFAULT           0
#define GRP_DISABLED          2

/*widget' signals*/
#define SIG_DISABLE_OBJ       3
#define SIG_RADIO_TL          (G_ALIGN_H_LEFT   | G_ALIGN_V_TOP)
#define SIG_RADIO_TC          (G_ALIGN_H_CENTER | G_ALIGN_V_TOP)
#define SIG_RADIO_TR          (G_ALIGN_H_RIGHT  | G_ALIGN_V_TOP)
#define SIG_RADIO_CL          (G_ALIGN_H_LEFT   | G_ALIGN_V_CENTER)
#define SIG_RADIO_CC          (G_ALIGN_H_CENTER | G_ALIGN_V_CENTER)
#define SIG_RADIO_CR          (G_ALIGN_H_RIGHT  | G_ALIGN_V_CENTER)
#define SIG_RADIO_BL          (G_ALIGN_H_LEFT   | G_ALIGN_V_BOTTOM)
#define SIG_RADIO_BC          (G_ALIGN_H_CENTER | G_ALIGN_V_BOTTOM)
#define SIG_RADIO_BR          (G_ALIGN_H_RIGHT  | G_ALIGN_V_BOTTOM)

/*offsets*/
#define OFFSET_RADIO          0
#define OFFSET_DISABLE_CHK    1

/**
 * local function
 */
static void Gui_DemoTextHandler(void);
static void Gui_DemoTextReadSignal(void);

/**
 * local variables
 */
static uint8_t disableObj, align = SIG_RADIO_TL;


/**
 * @function Gui_DemoText
 * @brief text area demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoText(void) {

  rect_st rec;
  disableObj = 0;
  
  R_MEM_WriteU8(OFFSET_RADIO, align);
  R_MEM_WriteU8(OFFSET_DISABLE_CHK, disableObj);

  Gui_DemoNewPage("Text area");

  rec = GUI_Rect(10, 20, 299, 137);
  R_GUI_SetAlign(align);
  R_GUI_SetGroup(GRP_DISABLED);
  R_GUI_W_TextAdd(&rec,
      "This program is free software: you can redistribute it and/or modify "
      "it under the terms of the GNU General Public License as published by "
      "the Free Software Foundation, either version 3 of the License, or "
      "(at your option) any later version.");
  R_GUI_SetGroup(GRP_DEFAULT);
  R_GUI_SetAlign(0); /*reset the alignment (recommended)*/

  /*draw the dimension of the text area*/
  rec.x--;
  rec.y--;
  rec.w += 2;
  rec.h += 2;
  R_P2D_SetLineType(LINE_SOLID);
  R_P2D_SetColor(COLOR_PURPLE);
  R_P2D_Rect(&rec);


  /**
   * alignment controls
   */
  rec = GUI_Rect(253, 160, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_TL);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_TL);
  rec = GUI_Rect(273, 160, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_TC);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_TC);
  rec = GUI_Rect(293, 160, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_TR);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_TR);

  rec = GUI_Rect(253, 178, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_CL);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_CL);
  rec = GUI_Rect(273, 178, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_CC);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_CC);
  rec = GUI_Rect(293, 178, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_CR);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_CR);

  rec = GUI_Rect(253, 196, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_BL);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_BL);
  rec = GUI_Rect(273, 196, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_BC);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_BC);
  rec = GUI_Rect(293, 196, 17, 17);
  R_GUI_W_RadioAdd(&rec, NULL, OFFSET_RADIO, SIG_RADIO_BR);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_BR);

  /**
   * disable control
   */
  rec = GUI_Rect(10, 160, 115, 19);
  R_GUI_W_CheckBoxAdd(&rec, "Disable objects", OFFSET_DISABLE_CHK);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DISABLE_OBJ);

  /* => page creation is now completed. Jump to the page's handler*/
  R_GUI_SetTask(Gui_DemoTextReadSignal);
}


/**
 * @function Gui_DemoTextReadSignal
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoTextReadSignal(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_GUI_SetTask(Gui_DemoTextHandler);
  }
}


/**
 * @function Gui_DemoTextHandler
 * @brief wait the <read signal> request & handle it
 * @param none
 * @return none
 */
static void Gui_DemoTextHandler(void) {

  signal_t sig = RxGetU16();
  
  if(RxStatus() == 0) {

    switch(sig) {

      /*widget control*/
      case SIG_DISABLE_OBJ:
        disableObj = !disableObj;
        R_GUI_GroupDisable(GRP_DISABLED, disableObj);
        R_MEM_WriteU8(OFFSET_DISABLE_CHK, disableObj);
        R_GUI_SetTask(Gui_DemoTextReadSignal);
        break;

      /*'menu' button*/
      case SIG_DEMO_MENU:
        R_GUI_SetTask(Gui_Demo);
        break;

      /*no signal*/
      case 0:
        R_GUI_SetTask(Gui_DemoTextReadSignal);
        break;

      /*at this point, the signal has been generated by a radio*/
      default:
        align = sig;
        R_GUI_SetTask(Gui_DemoText);
        break;
    }
  }
}
