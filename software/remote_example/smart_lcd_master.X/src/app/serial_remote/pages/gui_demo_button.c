/**
 * @file gui_demo_button.c
 * @brief common widgets demo (serialized, master side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-30
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


/**
 *  local functions
 */
static void Gui_DemoButtonRead(void);
static void Gui_DemoButtonHandle(void);

/**
 *  widget groups enumeration
 */
enum {
  GRP_DEFAULT = 0,
  GRP_NOTIFIED,
  GRP_DISABLED
};

/**
 *  signal enumeration
 */
enum {
  SIG_NOTIFY_OBJ = 1, /*remember: 0 means NO_SIGNAL*/
  SIG_DISABLE_OBJ,
  SIG_CHECKBOX_1,
  SIG_CHECKBOX_2,
  SIG_CHECKBOX_3,
  SIG_CHECKBOX_4,
  SIG_CHECKBOX_5,
  SIG_RADIO_1_A,
  SIG_RADIO_1_B,
  SIG_RADIO_1_C,
  SIG_RADIO_2_A,
  SIG_RADIO_2_B,
  SIG_RADIO_2_C,
};

/**
 *  radio id enumeration
 */
enum {
  ID_RADIO_A = 0,
  ID_RADIO_B,
  ID_RADIO_C
};

/**
 *  memory offsets enumeration
 */
enum {
  OFFSET_CHECKBOX_1 = 0,  /*correct offset is in range [0 to SSM_SIZE-1]*/
  OFFSET_CHECKBOX_2,
  OFFSET_CHECKBOX_3,
  OFFSET_CHECKBOX_4,
  OFFSET_CHECKBOX_5,
  OFFSET_RADIO_1,
  OFFSET_RADIO_2,
  OFFSET_CHECKBOX_NOTIFY,
  OFFSET_CHECKBOX_DISABLE,

  MEM_SIZE
};

/**
 *  local variables
 */
static uint8_t widgetsMem[MEM_SIZE];


/**
 * @function Gui_DemoButton
 * @brief common widgets demo
 * @param none
 * @return none
 */
void Gui_DemoButton(void) {

  rect_st rec;
  uint8_t ii;

  Gui_DemoNewPage("Common widgets");

  /*clear widgets' memory*/
  for(ii = 0; ii < MEM_SIZE; ii++) widgetsMem[ii] = 0;
  R_MEM_WriteU8Arr(OFFSET_CHECKBOX_1, MEM_SIZE, widgetsMem);

  /**
   * add some various buttons (not connected to any signal)
   */
  rec = GUI_Rect(10, 25, 68, 21);
  R_GUI_W_ButtonAdd(&rec, "no image", 0);

  rec = GUI_Rect(80, 25, 20, 21);
  R_GUI_W_ButtonAdd(&rec, NULL /*no text*/, G_IMG_CONFIG);

  rec = GUI_Rect(10, 47, 90, 21);
  R_GUI_W_ButtonAdd(&rec, "Image", G_IMG_SAVE);

  rec = GUI_Rect(10, 69, 90, 21);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(255, 0, 0));
  R_GUI_W_ButtonAdd(&rec, "color", G_IMG_EDIT);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));

  rec = GUI_Rect(10, 91, 90, 21);
  R_GUI_SetFont(G_FONT_BOLD);
  R_GUI_W_ButtonAdd(&rec, "font", G_IMG_INFO);
  R_GUI_SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(10, 113, 90, 21);
  R_GUI_SetGroup(GRP_NOTIFIED);
  R_GUI_W_ButtonAdd(&rec, "notify me", G_IMG_REFRESH);
  R_GUI_SetGroup(GRP_DEFAULT);

  rec = GUI_Rect(10, 135, 90, 21);
  R_GUI_SetGroup(GRP_DISABLED);
  R_GUI_W_ButtonAdd(&rec, "disable me", G_IMG_FIND);
  R_GUI_SetGroup(GRP_DEFAULT);

  /**
   * add some various checkbox
   */
  rec = GUI_Rect(110, 25, 90, 19);
  R_GUI_W_CheckBoxAdd(&rec, "normal", OFFSET_CHECKBOX_1);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_1);

  rec = GUI_Rect(110, 47, 90, 19);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 140, 0));
  R_GUI_W_CheckBoxAdd(&rec, "color", OFFSET_CHECKBOX_2);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_2);

  rec = GUI_Rect(110, 69, 90, 19);
  R_GUI_SetFont(G_FONT_ITALIC);
  R_GUI_W_CheckBoxAdd(&rec, "italic", OFFSET_CHECKBOX_3);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_3);
  R_GUI_SetFont(G_FONT_DEFAULT);

  rec = GUI_Rect(110, 91, 90, 19);
  R_GUI_SetGroup(GRP_NOTIFIED);
  R_GUI_W_CheckBoxAdd(&rec, "notify me", OFFSET_CHECKBOX_4);
  R_GUI_SetGroup(GRP_DEFAULT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_4);

  rec = GUI_Rect(110, 113, 90, 19);
  R_GUI_SetGroup(GRP_DISABLED);
  R_GUI_W_CheckBoxAdd(&rec, "disable me", OFFSET_CHECKBOX_5);
  R_GUI_SetGroup(GRP_DEFAULT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CHECKBOX_5);

  /**
   * add some various radio
   */
  rec = GUI_Rect(210, 25, 90, 19);
  R_GUI_W_RadioAdd(&rec, "choice 1.a", OFFSET_RADIO_1, ID_RADIO_A);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_A);

  rec = GUI_Rect(210, 47, 90, 19);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 0, 255));
  R_GUI_W_RadioAdd(&rec, "choice 1.b", OFFSET_RADIO_1, ID_RADIO_B);
  R_GUI_SetColor(G_COL_TEXT, P2D_Color(0, 0, 0));
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_B);

  rec = GUI_Rect(210, 69, 90, 19);
  R_GUI_SetFont(G_FONT_ITALIC);
  R_GUI_W_RadioAdd(&rec, "choice 1.c", OFFSET_RADIO_1, ID_RADIO_C);
  R_GUI_SetFont(G_FONT_DEFAULT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_1_C);

  rec = GUI_Rect(210, 113, 90, 19);
  R_GUI_W_RadioAdd(&rec, "default", OFFSET_RADIO_2, ID_RADIO_A);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_A);

  rec = GUI_Rect(210, 135, 90, 19);
  R_GUI_SetGroup(GRP_NOTIFIED);
  R_GUI_W_RadioAdd(&rec, "notify me", OFFSET_RADIO_2, ID_RADIO_B);
  R_GUI_SetGroup(GRP_DEFAULT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_B);

  rec = GUI_Rect(210, 157, 90, 19);
  R_GUI_SetGroup(GRP_DISABLED);
  R_GUI_W_RadioAdd(&rec, "disable me", OFFSET_RADIO_2, ID_RADIO_C);
  R_GUI_SetGroup(GRP_DEFAULT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_RADIO_2_C);

  /**
   * widget control
   */
  rec = GUI_Rect(10, 185, 110, 19);
  R_GUI_W_CheckBoxAdd(&rec, "Notify objects", OFFSET_CHECKBOX_NOTIFY);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_NOTIFY_OBJ);

  rec = GUI_Rect(130, 185, 115, 19);
  R_GUI_W_CheckBoxAdd(&rec, "Disable objects", OFFSET_CHECKBOX_DISABLE);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DISABLE_OBJ);

  R_GUI_Debug(true);

  R_GUI_SetTask(Gui_DemoButtonRead);
}


/**
 * @function Gui_DemoButtonRead
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoButtonRead(void) {

  static timer_t tmRefresh = 0;

  /**
   * Read widget signal every 30ms;
   * refresh time (for reading signal) should always be between
   * 20ms (high reactive, medium CPU load) and 100ms (medium reactive, low CPU load)
   *
   * This part is not required if you use only P2D (i.e. write only)
   */
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);

    /**
     * R_GUI_ReadSignal
     * This function asks to the TFT to send back the last <!= 0 && not yet read> signal,
     * by writting it in the answser message; the result will be accessible in the next answer
     * message coming from the TFT;
     * Here, answser message will be in form:
     *  [55 55 seqId sigLsb sigMsb AA AA]
     * where:
     *  55 55: two start tokens, already handled by low level functions
     *  seqId: sequence number (1 byte), already handled by low level functions
     *  sigLsb, sigMsb: two bytes consitituing the signal (coded on a uint16)
     *  AA AA: two stop tokens, already handled by low level functions
     */
    R_GUI_ReadSignal();

    /**
     * The signal will be processed in Gui_DemoButtonHandle()
     */
    R_GUI_SetTask(Gui_DemoButtonHandle);
  }

  /**
   * when leaving Gui_DemoButtonRead():
   *  - if the timer was not elapsed, nothing will be sent to the TFT; RemoteTask will
   *    re execute Gui_DemoButtonRead() at next software cycle
   *  - if the timer was elapsed, a message will be sent to the TFT; RemoteTask will handle
   *    the communication fsm; once the answser received from the TFT, RemoteTask will
   *    execute Gui_DemoButtonHandle()
   */
}


/**
 * @function Gui_DemoButtonHandle
 * @brief wait the <read signal> request & handle it
 * @param none
 * @return none
 */
static void Gui_DemoButtonHandle(void) {

  /**
   * This function is executed once the answer message of Gui_DemoButtonRead() is received
   */

  /**
   * extract signal from RX message
   * start tokens & sequence number are already unstacked by lower level functions
   * RxGetUxx functions directly give 'usefull' data
   */
  signal_t sig = RxGetU16();
  bool bExit = false;

  if(RxStatus() == 0 && sig != 0) {

    /*handle widget signal*/
    switch(sig) {
      case SIG_CHECKBOX_1: widgetsMem[OFFSET_CHECKBOX_1] = !widgetsMem[OFFSET_CHECKBOX_1]; break;
      case SIG_CHECKBOX_2: widgetsMem[OFFSET_CHECKBOX_2] = !widgetsMem[OFFSET_CHECKBOX_2]; break;
      case SIG_CHECKBOX_3: widgetsMem[OFFSET_CHECKBOX_3] = !widgetsMem[OFFSET_CHECKBOX_3]; break;
      case SIG_CHECKBOX_4: widgetsMem[OFFSET_CHECKBOX_4] = !widgetsMem[OFFSET_CHECKBOX_4]; break;
      case SIG_CHECKBOX_5: widgetsMem[OFFSET_CHECKBOX_5] = !widgetsMem[OFFSET_CHECKBOX_5]; break;

      case SIG_RADIO_1_A: widgetsMem[OFFSET_RADIO_1] = ID_RADIO_A; break;
      case SIG_RADIO_1_B: widgetsMem[OFFSET_RADIO_1] = ID_RADIO_B; break;
      case SIG_RADIO_1_C: widgetsMem[OFFSET_RADIO_1] = ID_RADIO_C; break;

      case SIG_RADIO_2_A: widgetsMem[OFFSET_RADIO_2] = ID_RADIO_A; break;
      case SIG_RADIO_2_B: widgetsMem[OFFSET_RADIO_2] = ID_RADIO_B; break;
      case SIG_RADIO_2_C: widgetsMem[OFFSET_RADIO_2] = ID_RADIO_C; break;

      case SIG_NOTIFY_OBJ: widgetsMem[OFFSET_CHECKBOX_NOTIFY] = !widgetsMem[OFFSET_CHECKBOX_NOTIFY]; break;
      case SIG_DISABLE_OBJ: widgetsMem[OFFSET_CHECKBOX_DISABLE] = !widgetsMem[OFFSET_CHECKBOX_DISABLE]; break;

      case SIG_DEMO_MENU: bExit = true;

      default: break;
    }

    /*update the TFT memory*/
    R_MEM_WriteU8Arr(OFFSET_CHECKBOX_1, MEM_SIZE, widgetsMem);

    /*update the disabled / notified groups*/
    R_GUI_GroupNotify(GRP_NOTIFIED, widgetsMem[OFFSET_CHECKBOX_NOTIFY]);
    R_GUI_GroupDisable(GRP_DISABLED, widgetsMem[OFFSET_CHECKBOX_DISABLE]);
  }

  /**
   * The signal has been handled; ask a new one, or exit if 'menu' buton
   */
  if(bExit) R_GUI_SetTask(Gui_Demo);
  else R_GUI_SetTask(Gui_DemoButtonRead);
}
