/**
 * @file gui_demo.c
 * @brief demo menu (serialized, master side)
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

#include "gui_demo.h"


#define SIG_LIST      1     /*when the list is pressed*/


/**
 * Local variable
 */
typedef struct {
  char *title;
  char *description;
  void (*pFunction)(void);
} demo_item_st;

#define DEMO_ITEM_CNT 10
const demo_item_st demoItems[DEMO_ITEM_CNT] = {
  {"01-Common"        , "Common widgets (buttons, checkbox, radio)" , &Gui_DemoButton},
  {"02-Text"          , "Text area, with word wrap & alignment"     , &Gui_DemoText},
  {"03-ValueBox"      , "ValueBoxes & sliders exemples"             , &Gui_DemoValueBox},
  {"04-Dial"          , "Rotary encoder exemples"                   , &Gui_DemoRotaryButton},
  {"05-Graph #1"      , "Big graph, with several curves"            , NULL},
  {"06-Graph #2"      , "Small graphs"                              , &Gui_DemoGraph2},
  {"07-List"          , "Select a sprite with dynamic lists"        , &Gui_DemoList},
  {"08-Keyboard"      , "AZERTY / QWERTY / NUM keyboards"           , &Gui_DemoKeyboard},
  {"09-Popup"         , "Annoy users with popups !"                 , NULL},
  {"11-File browser"  , "Yep, an embedded file browser"             , &Gui_DemoFileBrowser},
};
static uint16_t previousId;


/**
 * Local functions
 */
static void Gui_DemoHandler(void);
static void Gui_DemoRead(void);

/**
 * @function Gui_DemoFrame
 * @brief clear the screen, delete obejcts & draw a frame
 * @param const void *str: frame title
 * @return none
 */
void Gui_DemoFrame(const void *str) {

  rect_st rec;

  /*clear all*/
  R_GUI_ClearAll();

  /*add frame*/
  rec = GUI_Rect(5, 0, 310, 215);
  R_P2D_SetFont(G_FONT_BOLD);
  R_GUI_W_FrameAdd(&rec, str);
  R_P2D_SetFont(G_FONT_DEFAULT);
}


/**
 * @function Gui_DemoNewPage
 * @brief erase all, add a frame & and 'menu' button; used by most demo pages
 * @param const void *str: frame title
 * @return none
 */
void Gui_DemoNewPage(const void *str) {

  rect_st rec;

  /*clear all & add frame*/
  Gui_DemoFrame(str);

  /*button 'Menu' */
  rec = GUI_Rect(255, 218, 60, 20);
  R_GUI_W_ButtonAdd(&rec, "Menu", G_IMG_HOME);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_DEMO_MENU);
}


/**
 * @function Gui_Demo
 * @brief Main menu of the GUI demo
 * @param none
 * @return none
 */
void Gui_Demo(void) {

  rect_st rec;
  uint16_t ii;

  /*local init.*/
  previousId = 0xFFFF;

  /*clear + frame*/
  Gui_DemoFrame("P2D/GUI demo");

  /*text area*/
  rec = GUI_Rect(10, 17, 300, 15);
  R_GUI_W_TextAdd(&rec, "Double-touch an item:");

  /*new list, with header, H & V scrollers*/
  rec = GUI_Rect(10, 37, 300, 174);
  R_GUI_M_ListAdd(&rec, true, true, true, E_PUSHED_TO_RELEASED, SIG_LIST);

  /*add categories*/
  R_GUI_M_ListAddCategoryToList(110, "Module");
  R_GUI_M_ListAddCategoryToList(300, "Description");

  /*add demo items*/
  for(ii = 0; ii < DEMO_ITEM_CNT; ii++) {
    R_GUI_M_ListAddItemToList(0 /*no sprite*/);
    R_GUI_M_ListAddFieldToLastItem(demoItems[ii].title);
    R_GUI_M_ListAddFieldToLastItem(demoItems[ii].description);
  }

  /*done; go to handler*/
  R_GUI_SetTask(Gui_DemoRead);
}


/**
 * @function Gui_DemoRead
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoRead(void) {

  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_GUI_M_ListGetSelectedItemUid();
    R_GUI_SetTask(Gui_DemoHandler);
  }
}


/**
 * @function Gui_DemoRead
 * @brief wait the <read signal> request & handle it
 * @param none
 * @return none
 */
static void Gui_DemoHandler(void) {

  signal_t sig = RxGetU16();
  uint16_t id = RxGetU16();

  R_GUI_SetTask(Gui_DemoRead);

  /*list pressed?*/
  if(RxStatus() == 0) {

    if(sig == SIG_LIST) {

      /*id != ? store it*/
      if(id != previousId) {
        previousId = id;
      }
      /*else, same item pressed 2 times -> launch the corresponding demo*/
      else {
        if(id < DEMO_ITEM_CNT) {
          if(demoItems[id].pFunction != NULL) {
            R_GUI_SetTask(demoItems[id].pFunction);
          }
        }
      }
    }

    else {
      /*nothing*/
    }
  }
}
