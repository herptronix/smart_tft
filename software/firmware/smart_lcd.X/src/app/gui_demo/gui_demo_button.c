/**
 * @file gui_demo_button.c
 * @brief common widgets demo
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
#include "gui_demo_button.h"
#include "resources.h"

#ifdef INCLUDE_GUI_DEMO

/*group #id*/
#define GRP_DEFAULT           0
#define GRP_NOTIFIED          1
#define GRP_DISABLED          2

/*widget' signals*/
#define SIG_DISABLE_OBJ       3
#define SIG_NOTIFY_OBJ        4
#define SIG_CHECKBOX_1        5
#define SIG_CHECKBOX_2        6
#define SIG_CHECKBOX_3        7
#define SIG_CHECKBOX_4        8
#define SIG_CHECKBOX_5        9
#define SIG_RADIO_1_A         10
#define SIG_RADIO_1_B         11
#define SIG_RADIO_1_C         12
#define SIG_RADIO_2_A         20
#define SIG_RADIO_2_B         21
#define SIG_RADIO_2_C         22

/**
 * Local variable
 */
static uint8_t disableObj, notifyObj, check1, check2, check3, check4, check5, radio1, radio2;

/**
 * Local functions
 */
void Gui_DemoButtonHandler(signal_t sig);


/**
 * @function Gui_DemoButton
 * @brief common widgets demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoButton(signal_t sig) {

  rect_st rec;
  disableObj = notifyObj = check1 = check2 = check3 = check4 = check5 = 0;
  radio1 = radio2 = 1;

  Gui_DemoNewPage("Common widgets");

  /**
   * add some various buttons (not connected to any signal)
   */
  rec = GUI_Rect(10, 25, 68, 21);
  GUI_W_ButtonAdd(&rec, "no image", 0);

  rec = GUI_Rect(80, 25, 20, 21);
  GUI_W_ButtonAdd(&rec, NULL /*no text*/, G_IMG_CONFIG);

  rec = GUI_Rect(10, 47, 90, 21);
  GUI_W_ButtonAdd(&rec, "Image", G_IMG_SAVE);

  rec = GUI_Rect(10, 69, 90, 21);
  SetColor(G_COL_TEXT, P2D_Color(255, 0, 0));
  GUI_W_ButtonAdd(&rec, "color", G_IMG_EDIT);
  SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));

  rec = GUI_Rect(10, 91, 90, 21);
  SetFont(G_FONT_BOLD);
  GUI_W_ButtonAdd(&rec, "font", G_IMG_INFO);
  SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(10, 113, 90, 21);
  GUI_SetGroup(GRP_NOTIFIED);
  GUI_W_ButtonAdd(&rec, "notify me", G_IMG_REFRESH);
  GUI_SetGroup(GRP_DEFAULT);

  rec = GUI_Rect(10, 135, 90, 21);
  GUI_SetGroup(GRP_DISABLED);
  GUI_W_ButtonAdd(&rec, "disable me", G_IMG_FIND);
  GUI_SetGroup(GRP_DEFAULT);

  /**
   * add some various checkbox
   */
  rec = GUI_Rect(110, 25, 90, 19);
  GUI_W_CheckBoxAdd(&rec, "normal", &check1);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_1);

  rec = GUI_Rect(110, 47, 90, 19);
  SetColor(G_COL_TEXT, P2D_Color(0, 140, 0));
  GUI_W_CheckBoxAdd(&rec, "color", &check2);
  SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_2);

  rec = GUI_Rect(110, 69, 90, 19);
  SetFont(G_FONT_ITALIC);
  GUI_W_CheckBoxAdd(&rec, "italic", &check3);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_3);
  SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(110, 91, 90, 19);
  GUI_SetGroup(GRP_NOTIFIED);
  GUI_W_CheckBoxAdd(&rec, "notify me", &check4);
  GUI_SetGroup(GRP_DEFAULT);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_4);

  rec = GUI_Rect(110, 113, 90, 19);
  GUI_SetGroup(GRP_DISABLED);
  GUI_W_CheckBoxAdd(&rec, "disable me", &check5);
  GUI_SetGroup(GRP_DEFAULT);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_5);

  /**
   * add some various radio
   */
  rec = GUI_Rect(210, 25, 90, 19);
  GUI_W_RadioAdd(&rec, "choice 1.a", &radio1, 1);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_A);

  rec = GUI_Rect(210, 47, 90, 19);
  SetColor(G_COL_TEXT, P2D_Color(0, 0, 255));
  GUI_W_RadioAdd(&rec, "choice 1.b", &radio1, 2);
  SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_B);

  rec = GUI_Rect(210, 69, 90, 19);
  SetFont(G_FONT_ITALIC);
  GUI_W_RadioAdd(&rec, "choice 1.c", &radio1, 3);
  SetFont(G_FONT_DEFAULT);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_C);

  rec = GUI_Rect(210, 113, 90, 19);
  GUI_W_RadioAdd(&rec, "default", &radio2, 1);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_A);

  rec = GUI_Rect(210, 135, 90, 19);
  GUI_SetGroup(GRP_NOTIFIED);
  GUI_W_RadioAdd(&rec, "notify me", &radio2, 2);
  GUI_SetGroup(GRP_DEFAULT);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_B);

  rec = GUI_Rect(210, 157, 90, 19);
  GUI_SetGroup(GRP_DISABLED);
  GUI_W_RadioAdd(&rec, "disable me", &radio2, 3);
  GUI_SetGroup(GRP_DEFAULT);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_C);

  /**
   * widget control
   */
  rec = GUI_Rect(10, 185, 110, 19);
  GUI_W_CheckBoxAdd(&rec, "Notify objects", &notifyObj);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_NOTIFY_OBJ);

  rec = GUI_Rect(130, 185, 115, 19);
  GUI_W_CheckBoxAdd(&rec, "Disable objects", &disableObj);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DISABLE_OBJ);

  /* => page creation is now completed. Jump to the page's handler*/
  GUI_SetUserTask(Gui_DemoButtonHandler);
}


/**
 * @function Gui_DemoButtonHandler
 * @brief handler of Gui_DemoButton
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
void Gui_DemoButtonHandler(signal_t sig) {

  switch(sig) {

    /*dummy management*/
    case SIG_CHECKBOX_1: check1 = !check1; break;
    case SIG_CHECKBOX_2: check2 = !check2; break;
    case SIG_CHECKBOX_3: check3 = !check3; break;
    case SIG_CHECKBOX_4: check4 = !check4; break;
    case SIG_CHECKBOX_5: check5 = !check5; break;
    case SIG_RADIO_1_A: radio1 = 1; break;
    case SIG_RADIO_1_B: radio1 = 2; break;
    case SIG_RADIO_1_C: radio1 = 3; break;
    case SIG_RADIO_2_A: radio2 = 1; break;
    case SIG_RADIO_2_B: radio2 = 2; break;
    case SIG_RADIO_2_C: radio2 = 3; break;

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
  }
}

#endif
