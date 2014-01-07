/**
 * @file gui_demo_list.c
 * @brief flexible list (through macro) demo
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

#include "gui_demo_list.h"
#include "resources.h"

#ifdef INCLUDE_GUI_DEMO

#define SIG_LIST 1

/**
 * local variables
 */
const char *strImgName[] = {
  "NONE",
  "G_IMG_OK",
  "G_IMG_NO",
  "G_IMG_ADD",
  "G_IMG_REMOVE",
  "G_IMG_LEFT_ARROW",
  "G_IMG_LEFT_D_ARROW",
  "G_IMG_DOWN_ARROW",
  "G_IMG_DOWN_D_ARROW",
  "G_IMG_RIGHT_ARROW",
  "G_IMG_RIGHT_D_ARROW",
  "G_IMG_UP_ARROW",
  "G_IMG_UP_D_ARROW",
  "G_IMG_GO_LEFT",
  "G_IMG_GO_DOWN",
  "G_IMG_GO_RIGHT",
  "G_IMG_GO_UP",
  "G_IMG_CONFIG",
  "G_IMG_FORBID",
  "G_IMG_ERROR",
  "G_IMG_SAVE",
  "G_IMG_OPEN",
  "G_IMG_EDIT",
  "G_IMG_INFO",
  "G_IMG_HELP",
  "G_IMG_HOME",
  "G_IMG_REFRESH",
  "G_IMG_IMPORTANT",
  "G_IMG_EXIT",
  "G_IMG_EJECT",
  "G_IMG_PAUSE",
  "G_IMG_STOP",
  "G_IMG_REC",
  "G_IMG_FIND",
  "G_IMG_ZOOM_1",
  "G_IMG_ZOOM_OUT",
  "G_IMG_ZOOM_IN",
  "G_IMG_ACCEPT",
  "G_IMG_DECLINE",
  "G_IMG_SORT_DOWN",
  "G_IMG_SORT_UP",
  "G_IMG_BOOKMARK",
  "G_IMG_GRAPH_ADD",
  "G_IMG_GRAPH_REMOVE",
  "G_IMG_GRAPH_EDIT",
  "G_IMG_DOWNLOAD",
  "G_IMG_CLEAR",
  "G_IMG_CUT",
  "G_IMG_DRAG",
  "G_IMG_SMILE",
  "G_IMG_HISTOGRAM",
  "G_IMG_LOCK",
  "G_IMG_BULB",
  "G_IMG_OSCILLOSCOPE",
  "G_IMG_TASK",
  "G_IMG_WARNING",

  "G_IMG_DEVICE",
  "G_IMG_SND_MUTE",
  "G_IMG_SOUND_MIN",
  "G_IMG_SOUND_MEDIUM",
  "G_IMG_SOUND_MAX",
  "G_IMG_BATTERY_MIN",
  "G_IMG_BATTERY_MEDIUM",
  "G_IMG_BATTERY_GOOD",
  "G_IMG_BATTERY_MAX",
  "G_IMG_BATTERY_C_MIN",
  "G_IMG_BATTERY_C_MEDIUM",
  "G_IMG_BATTERY_C_GOOD",
  "G_IMG_BATTERY_C_MAX",
  "G_IMG_COMPUTER",
  "G_IMG_SD_CARD",
  "G_IMG_SIGNAL_NONE",
  "G_IMG_SIGNAL_MIN",
  "G_IMG_SIGNAL_MEDIUM",
  "G_IMG_SIGNAL_GOOD",
  "G_IMG_SIGNAL_MAX",
  "G_IMG_SAFE",
  "G_IMG_UNSAFE",
  "G_IMG_USB",
  "G_IMG_CLOCK",

  "G_IMG_FILE_INFO",
  "G_IMG_FILE_APP",
  "G_IMG_FILE_APP_WIN",
  "G_IMG_FILE_ZIP",
  "G_IMG_FILE_AUDIO",
  "G_IMG_FILE_PACK",
  "G_IMG_FILE_ENCRYPTED",
  "G_IMG_FILE_IMPORTANT",
  "G_IMG_FILE_TMP",
  "G_IMG_FOLDER",
  "G_IMG_FILE_FONT",
  "G_IMG_FILE_IMGS",
  "G_IMG_FILE_IMG",
  "G_IMG_FILE_PACK2",
  "G_IMG_FILE_HTML",
  "G_IMG_FILE_ASM",
  "G_IMG_FILE_H",
  "G_IMG_FILE_C",
  "G_IMG_FILE_TXT",
  "G_IMG_FILE_EMPTY",
  "G_IMG_FILE_SCRIPT",
  "G_IMG_FILE_UNKNOWN",

  "G_IMG_CALC",
  "G_IMG_LOCALE_US",
  "G_IMG_LOCALE_FR",
  "G_IMG_BOMB",
  "G_IMG_BOOKS",
  "G_IMG_PACKAGE",
  "G_IMG_BRICKS",
  "G_IMG_CART",
  "G_IMG_CREDIT_CARDS",
  "G_IMG_DB_ERROR",
  "G_IMG_EYE",
  "G_IMG_FLAG_BLUE",
  "G_IMG_FLAG_GREEN",
  "G_IMG_FLAG_ORANGE",
  "G_IMG_FLAG_PINK",
  "G_IMG_FLAG_PURPLE",
  "G_IMG_FLAG_RED",
  "G_IMG_FLAG_YELLOW",
  "G_IMG_PICTURES",
  "G_IMG_WINDOWS",
  "G_IMG_MONEY",
  "G_IMG_MUSIC",
  "G_IMG_SHEETS",
  "G_IMG_PACKAGE2",
  "G_IMG_ROSETTE",
  "G_IMG_TAG_BLUE",
  "G_IMG_TAG_GREEN",
  "G_IMG_TAG_ORANGE",
  "G_IMG_TAG_PINK",
  "G_IMG_TAG_PURPLE",
  "G_IMG_TAG_RED",
  "G_IMG_TAG_YELLOW",
  "G_IMG_TUX",
  "G_IMG_USER_BLUE",
  "G_IMG_USER_PURPLE",
  "G_IMG_USER_GREY",
  "G_IMG_USER_GREEN",
  "G_IMG_USER_ORANGE",
  "G_IMG_USER_RED",
  "G_IMG_USER_BLUE2"
};

/**
 * local functions
 */
static void Gui_DemoListHandler(signal_t sig);


/**
 * @function Gui_DemoList
 * @brief lists demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoList(signal_t sig) {

  rect_st rec;
  int16_t ii = 0;
  char str[50];

  Gui_DemoNewPage("Flexible lists");

  /*create the list*/
  rec = GUI_Rect(10, 20, 300, 162);
  GUI_M_ListAdd(&rec, true, true, false, E_PUSHED_TO_RELEASED, SIG_LIST);

  /*add categories*/
  GUI_M_ListAddCategoryToList(70, "id");
  GUI_M_ListAddCategoryToList(220, "name");

  /*add items*/
  while(ii <= G_IMG_USER_BLUE2) {
    GUI_M_ListAddItemToList(ii, NULL);
    sprintf(str, "%03d", ii);
    GUI_M_ListAddFieldToLastItem(str);
    sprintf(str, "%s", strImgName[ii]);
    GUI_M_ListAddFieldToLastItem(str);
    ii++;
  }

  /*done; go to handler*/
  GUI_SetUserTask(Gui_DemoListHandler);
}


/**
 * @function Gui_DemoListHandler
 * @brief lists demo handler
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
static void Gui_DemoListHandler(signal_t sig) {

  uint16_t id;

  switch(sig) {

    /*'menu' button*/
    case SIG_DEMO_MENU:
      GUI_SetUserTask(Gui_Demo);
      break;

    /*list*/
    case SIG_LIST:
      GUI_M_ListGetSelectedItemUid(&id);
      /*process id...*/
      break;

    default:
      break;
  }
}

#endif
