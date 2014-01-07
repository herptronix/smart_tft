/**
 * @file gui_demo_file_browser.c
 * @brief file bowser menu
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

#include "gui_demo_file_browser.h"
#include "resources.h"

#ifdef INCLUDE_GUI_DEMO

/*path max length*/
#define PATH_BUFF_SIZE 200

/*widget' signals*/
#define SIG_SELECT_FILE 1
#define SIG_SELECT_FOLDER 2

/**
 * Local variable
 */
static char *path_file = NULL, *path_folder = NULL;

/**
 * Local functions
 */
static void Gui_DemoFileBrowserHandler(signal_t sig);
static void CleanExit(void);


/**
 * @function Gui_DemoFileBrowser
 * @brief File browser demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoFileBrowser(signal_t sig) {

  rect_st rec;
  coord_t hEntry, y, pitch;

  Gui_DemoNewPage("built-in file browser");

  /*allocate memory for storing file paths*/
  if(path_file == NULL) path_file = salloc(PATH_BUFF_SIZE);
  if(path_folder == NULL) path_folder = salloc(PATH_BUFF_SIZE);
  if(path_file != NULL && path_folder != NULL) {

    SetFont(G_FONT_DEFAULT);
    hEntry = P2D_GetTextHeight() + 4;
    pitch = hEntry - 3;
    y = 20;

    /**
     * widgets for file selection
     */
    path_file[0] = 0;
    rec = GUI_Rect(15, y, 295, hEntry);
    GUI_W_TextAdd(&rec, "Select a file"); y += pitch;

    rec = GUI_Rect(15, y, 265, hEntry);
    GUI_W_UsrEntryAdd(&rec, path_file, PATH_BUFF_SIZE, false);

    rec = GUI_Rect(285, y, hEntry, hEntry);
    GUI_W_ButtonAdd(&rec, NULL, G_IMG_OPEN);
    GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_SELECT_FILE);

    /**
     * widgets for folder selection
     */
    path_folder[0] = 0;
    y += pitch*2;
    rec = GUI_Rect(15, y, 295, hEntry);
    GUI_W_TextAdd(&rec, "Select a folder"); y += pitch;

    rec = GUI_Rect(15, y, 265, hEntry);
    GUI_W_UsrEntryAdd(&rec, path_folder, PATH_BUFF_SIZE, false);

    rec = GUI_Rect(285, y, hEntry, hEntry);
    GUI_W_ButtonAdd(&rec, NULL, G_IMG_OPEN);
    GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_SELECT_FOLDER);

    /* => page creation is now completed. Jump to the page's handler*/
    GUI_SetUserTask(Gui_DemoFileBrowserHandler);
  }
  else {

    /*critical: salloc error*/
    CleanExit();
  }
}


/**
 * @function Gui_DemoFileBrowserHandler
 * @brief file browser demo handler
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
static void Gui_DemoFileBrowserHandler(signal_t sig) {

  switch(sig) {

    case SIG_SELECT_FILE:
      GUI_M_FileBrowser(FILE_BROWSER_SEL_FILE, path_file, PATH_BUFF_SIZE);
      break;
    case SIG_SELECT_FOLDER:
      GUI_M_FileBrowser(FILE_BROWSER_SEL_FOLDER, path_folder, PATH_BUFF_SIZE);
      break;

    /*'menu' button*/
    case SIG_DEMO_MENU:
      CleanExit();
      break;

    /*build-in file browser buttons*/
    case FILE_BROWSER_BTN_SELECT:
    case FILE_BROWSER_BTN_CANCEL:
    default:
      break;
  }
}


/**
 * @function CleanExit
 * @brief clear path pointers before exit!
 * @param none
 * @return none
 */
static void CleanExit(void) {
  path_file = path_folder = NULL;
  GUI_SetUserTask(Gui_Demo);
}

#endif
