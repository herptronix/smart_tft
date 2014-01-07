/**
 * @file gui_demo_keyboard.c
 * @brief keyboard demo
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
#include "resources.h"

#ifdef INCLUDE_GUI_DEMO

#define KBD_BUFF_SIZE 200

/*widget' signals*/
#define SIG_CREATE_AZERTY 1
#define SIG_CREATE_QWERTY 2
#define SIG_CREATE_NUM    3
#define SIG_KBD_OK        123 /*dummy, not used here*/
#define SIG_KBD_ESC       456 /*dummy, not used here*/


/**
 * local variables
 */
static void *buf_azerty = NULL, *buf_qwerty = NULL, *buf_num = NULL;

/**
 * local functions
 */
static void Gui_DemoKeyboardHandler(signal_t sig);
static void CleanExit(void);


/**
 * @function Gui_DemoKeyboard
 * @brief keyboard demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoKeyboard(signal_t sig) {

  rect_st rec;
  coord_t hEntry, y, pitch;

  Gui_DemoNewPage("built-in keyboards");

  /*allocate memory for usr entries*/
  if(buf_azerty == NULL) buf_azerty = salloc(KBD_BUFF_SIZE);
  if(buf_qwerty == NULL) buf_qwerty = salloc(KBD_BUFF_SIZE);
  if(buf_num == NULL) buf_num = salloc(KBD_BUFF_SIZE);
  if(buf_azerty != NULL && buf_qwerty != NULL && buf_num != NULL) {

    SetFont(G_FONT_DEFAULT);
    hEntry = P2D_GetTextHeight() + 4;
    pitch = hEntry - 3;
    y = 20;

    /**
     * widgets for azerty
     */
    rec = GUI_Rect(15, y, 295, hEntry);
    GUI_W_TextAdd(&rec, "String input, with AZERTY keyboard"); y += pitch;

    snprintf(buf_azerty, KBD_BUFF_SIZE, "azerty"); /*make sure that the buffer is \0 terminated*/

    rec = GUI_Rect(15, y, 265, hEntry);
    GUI_W_UsrEntryAdd(&rec, buf_azerty, KBD_BUFF_SIZE, false);

    rec = GUI_Rect(285, y, hEntry, hEntry);
    GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
    GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_AZERTY);

    /**
     * widgets for qwerty
     */
    y += pitch*2;
    rec = GUI_Rect(15, y, 295, hEntry);
    GUI_W_TextAdd(&rec, "String input, with QWERTY keyboard"); y += pitch;

    snprintf(buf_qwerty, KBD_BUFF_SIZE, "qwerty");

    rec = GUI_Rect(15, y, 265, hEntry);
    GUI_W_UsrEntryAdd(&rec, buf_qwerty, KBD_BUFF_SIZE, false);

    rec = GUI_Rect(285, y, hEntry, hEntry);
    GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
    GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_QWERTY);

    /**
     * widgets for num
     */
    y += pitch*2;
    rec = GUI_Rect(15, y, 295, hEntry);
    GUI_W_TextAdd(&rec, "String input, with NUM keyboard"); y += pitch;
    snprintf(buf_num, KBD_BUFF_SIZE, "0");

    rec = GUI_Rect(15, y, 265, hEntry);
    GUI_W_UsrEntryAdd(&rec, buf_num, KBD_BUFF_SIZE, false);

    rec = GUI_Rect(285, y, hEntry, hEntry);
    GUI_W_ButtonAdd(&rec, NULL, G_IMG_EDIT);
    GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_CREATE_NUM);


    /* => page creation is now completed. Jump to the page's handler*/
    GUI_SetUserTask(Gui_DemoKeyboardHandler);
  }
  else {

    /*critical: salloc error*/
    CleanExit();
  }
}


/**
 * @function Gui_DemoKeyboardHandler
 * @brief keyboard demo handler
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
static void Gui_DemoKeyboardHandler(signal_t sig) {

  switch(sig) {

    case SIG_CREATE_AZERTY:
      GUI_M_KeyboardCreate(20, 90, KEYBOARD_TYPE_FR_FR, buf_azerty, 200, SIG_KBD_OK, SIG_KBD_ESC);
      break;
    case SIG_CREATE_QWERTY:
      GUI_M_KeyboardCreate(20, 90, KEYBOARD_TYPE_EN_US, buf_qwerty, 200, SIG_KBD_OK, SIG_KBD_ESC);
      break;
    case SIG_CREATE_NUM:
      GUI_M_KeyboardCreate(200, 90, KEYBOARD_TYPE_NUM, buf_num, 200, SIG_KBD_OK, SIG_KBD_ESC);
      break;

    /*'menu' button*/
    case SIG_DEMO_MENU:
      CleanExit();
      break;

    default:
      break;
  }
}


/**
 * @function CleanExit
 * @brief keyboard exit
 * @param none
 * @return none
 */
static void CleanExit(void) {
  buf_azerty = buf_qwerty = buf_num = NULL;
  GUI_SetUserTask(Gui_Demo);
}

#endif
