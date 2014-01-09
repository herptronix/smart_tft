/**
 * @file gui_demo_keyboard.c
 * @brief keyboard demo (serialized, master side)
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
#include "gui_demo_keyboard.h"


/*offsets*/
#define KBD_BUFF_SIZE       200
#define OFFSET_START        0
#define OFFSET_AZERTY       (OFFSET_START)
#define OFFSET_AZERTY_ECHO  (KBD_BUFF_SIZE + OFFSET_AZERTY)
#define OFFSET_QWERTY       (KBD_BUFF_SIZE + OFFSET_AZERTY_ECHO)
#define OFFSET_QWERTY_ECHO  (KBD_BUFF_SIZE + OFFSET_QWERTY)
#define OFFSET_NUM          (KBD_BUFF_SIZE + OFFSET_QWERTY_ECHO)
#define OFFSET_NUM_ECHO     (KBD_BUFF_SIZE + OFFSET_NUM)
#define _MEM_SIZE           (KBD_BUFF_SIZE + OFFSET_NUM_ECHO)


/*widget' signals*/
enum {
  SIG_CREATE_AZERTY = 1,
  SIG_CREATE_QWERTY,
  SIG_CREATE_NUM,
  SIG_KBD_OK,
  SIG_KBD_ESC
};


/**
 * local functions
 */
static void Gui_DemoKeyboardRead(void);
static void Gui_DemoKeyboardHandler(void);
static void Gui_DemoKeyboardUpdateEntry(void);

/**
 * @function Gui_DemoKeyboard
 * @brief keyboard demo
 * @param none
 * @return none
 */
void Gui_DemoKeyboard(void) {

  rect_st rec;
  coord_t hEntry, y, pitch;

  Gui_DemoNewPage("built-in keyboards");

  /*clear the memory area dedicated to strings*/
  R_MEM_Memset(OFFSET_START, _MEM_SIZE, 0);

  R_GUI_SetFont(G_FONT_DEFAULT);
  hEntry = 19;
  pitch = hEntry - 3;
  y = 20;

  /**
   * widgets for azerty
   */
  rec = GUI_Rect(15, y, 295, hEntry);
  R_GUI_W_TextAdd(&rec, "String input, with AZERTY keyboard"); y += pitch;

  rec = GUI_Rect(15, y, 265, hEntry);
  R_GUI_W_UsrEntryAdd(&rec, OFFSET_AZERTY_ECHO, KBD_BUFF_SIZE);

  rec = GUI_Rect(285, y, hEntry, hEntry);
  R_GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_AZERTY);

  /**
   * widgets for qwerty
   */
  y += pitch*2;
  rec = GUI_Rect(15, y, 295, hEntry);
  R_GUI_W_TextAdd(&rec, "String input, with QWERTY keyboard"); y += pitch;

  rec = GUI_Rect(15, y, 265, hEntry);
  R_GUI_W_UsrEntryAdd(&rec, OFFSET_QWERTY_ECHO, KBD_BUFF_SIZE);

  rec = GUI_Rect(285, y, hEntry, hEntry);
  R_GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_QWERTY);

  /**
   * widgets for num
   */
  y += pitch*2;
  rec = GUI_Rect(15, y, 295, hEntry);
  R_GUI_W_TextAdd(&rec, "String input, with NUM keyboard"); y += pitch;

  rec = GUI_Rect(15, y, 265, hEntry);
  R_GUI_W_UsrEntryAdd(&rec, OFFSET_NUM_ECHO, KBD_BUFF_SIZE);

  rec = GUI_Rect(285, y, hEntry, hEntry);
  R_GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_NUM);

  /* => page creation is now completed. Jump to the page's handler*/
  R_GUI_SetTask(Gui_DemoKeyboardRead);
}


/**
 * @function Gui_DemoKeyboardRead
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoKeyboardRead(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_GUI_SetTask(Gui_DemoKeyboardHandler);
  }
}


/**
 * @function Gui_DemoKeyboardHandler
 * @brief wait the <read signal> request & handle it
 * @param none
 * @return none
 */
static void Gui_DemoKeyboardHandler(void) {

  signal_t sig = RxGetU16();
  
  R_GUI_SetTask(Gui_DemoKeyboardRead);
  
  if(RxStatus() == 0) {
  
    switch(sig) {

      case SIG_CREATE_AZERTY:
        R_GUI_M_KeyboardCreate(20, 90, KEYBOARD_TYPE_FR_FR, OFFSET_AZERTY, KBD_BUFF_SIZE, SIG_KBD_OK, SIG_KBD_ESC);
        break;
      case SIG_CREATE_QWERTY:
        R_GUI_M_KeyboardCreate(20, 90, KEYBOARD_TYPE_EN_US, OFFSET_QWERTY, KBD_BUFF_SIZE, SIG_KBD_OK, SIG_KBD_ESC);
        break;
      case SIG_CREATE_NUM:
        R_GUI_M_KeyboardCreate(200, 90, KEYBOARD_TYPE_NUM, OFFSET_NUM, KBD_BUFF_SIZE, SIG_KBD_OK, SIG_KBD_ESC);
        break;

      case SIG_KBD_OK:
        R_MEM_ReadStr(OFFSET_AZERTY, KBD_BUFF_SIZE);
        R_MEM_ReadStr(OFFSET_QWERTY, KBD_BUFF_SIZE);
        R_MEM_ReadStr(OFFSET_NUM, KBD_BUFF_SIZE);
        R_GUI_SetTask(Gui_DemoKeyboardUpdateEntry);
        break;
        
      case SIG_KBD_ESC:
        /*nothing; do not echo*/
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


/**
 * @function Gui_DemoKeyboardUpdateEntry
 * @brief read string & echo it
 * @param none
 * @return none
 */
static void Gui_DemoKeyboardUpdateEntry(void) {

  /**
   * This function is executed once the answer message of R_MEM_ReadStr() is received
   */
  const uint8_t *azerty = NULL, *qwerty = NULL, *num = NULL;
  
  /**
   * extract path strings from the received RX message
   * RxGetTxt() gives pointer to the string begining, and dequeue the RX message
   * until '\0'; content of pathFile & pathFolder is safe as long as no
   * message is sent to the TFT (i.e. safe until the end of this function, RX IRQ is masqued)
   */
  RxGetTxt(&azerty);
  RxGetTxt(&qwerty);
  RxGetTxt(&num);
  
  if(RxStatus() == 0) {
    /*echo received strings*/
    R_MEM_WriteStr(OFFSET_AZERTY_ECHO, KBD_BUFF_SIZE, azerty);
    R_MEM_WriteStr(OFFSET_QWERTY_ECHO, KBD_BUFF_SIZE, qwerty);
    R_MEM_WriteStr(OFFSET_NUM_ECHO, KBD_BUFF_SIZE, num);
  }
  R_GUI_SetTask(Gui_DemoKeyboardRead);
}
