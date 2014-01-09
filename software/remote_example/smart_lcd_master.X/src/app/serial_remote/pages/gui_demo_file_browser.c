/**
 * @file gui_demo_file_browser.c
 * @brief file bowser menu (serialized, master side)
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

/*path length; 200 bytes should be enought*/
#define PATH_BUFF_SIZE 200

/**
 * strings offset
 * OFFSET_PATH_FILE_ECHO & OFFSET_PATH_FOLDER_ECHO are defined only to give
 *  an exemple of read / write management.
 * R_GUI_W_UsrEntryAdd() and R_GUI_M_FileBrowser() can share the same memory
 */
#define OFFSET_START              0
#define OFFSET_PATH_FILE          (OFFSET_START)
#define OFFSET_PATH_FILE_ECHO     (PATH_BUFF_SIZE + OFFSET_PATH_FILE)
#define OFFSET_PATH_FOLDER        (PATH_BUFF_SIZE + OFFSET_PATH_FILE_ECHO)
#define OFFSET_PATH_FOLDER_ECHO   (PATH_BUFF_SIZE + OFFSET_PATH_FOLDER)
#define _MEM_SIZE                 (PATH_BUFF_SIZE + OFFSET_PATH_FOLDER_ECHO)

/*widget' signals*/
#define SIG_SELECT_FILE   1
#define SIG_SELECT_FOLDER 2


/**
 * Local functions
 */
static void Gui_DemoFileBrowserWaitSignal(void);
static void Gui_DemoFileBrowserHandler(void);
static void Gui_DemoFileBrowserUpdateEntry(void);


/**
 * @function Gui_DemoFileBrowser
 * @brief File browser demo
 * @param none
 * @return none
 */
void Gui_DemoFileBrowser(void) {

  rect_st rec;
  coord_t hEntry, y, pitch;

  Gui_DemoNewPage("built-in file browser");
  
  /*clear the memory area dedicated to strings*/
  R_MEM_Memset(OFFSET_START, _MEM_SIZE, 0);

  R_GUI_SetFont(G_FONT_DEFAULT);
  hEntry = 19;
  pitch = hEntry - 3;
  y = 20;

  /**
   * widgets for file selection
   */
  rec = GUI_Rect(15, y, 295, hEntry);
  R_GUI_W_TextAdd(&rec, "Select a file"); y += pitch;

  rec = GUI_Rect(15, y, 265, hEntry);
  R_GUI_W_UsrEntryAdd(&rec, OFFSET_PATH_FILE_ECHO, PATH_BUFF_SIZE);

  rec = GUI_Rect(285, y, hEntry, hEntry);
  R_GUI_W_ButtonAdd(&rec, NULL, G_IMG_OPEN);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_SELECT_FILE);

  /**
   * widgets for folder selection
   */
  y += pitch*2;
  rec = GUI_Rect(15, y, 295, hEntry);
  R_GUI_W_TextAdd(&rec, "Select a folder"); y += pitch;

  rec = GUI_Rect(15, y, 265, hEntry);
  R_GUI_W_UsrEntryAdd(&rec, OFFSET_PATH_FOLDER_ECHO, PATH_BUFF_SIZE);

  rec = GUI_Rect(285, y, hEntry, hEntry);
  R_GUI_W_ButtonAdd(&rec, NULL, G_IMG_OPEN);
  R_GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_SELECT_FOLDER);

  /* => page creation is now completed. Jump to the page's handler*/
  R_GUI_SetTask(Gui_DemoFileBrowserWaitSignal);
}


/**
 * @function Gui_DemoFileBrowserWaitSignal
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoFileBrowserWaitSignal(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_GUI_SetTask(Gui_DemoFileBrowserHandler);
  }
}


/**
 * @function Gui_DemoFileBrowserHandler
 * @brief wait the <read signal> request & handle it
 * @param none
 * @return none
 */
static void Gui_DemoFileBrowserHandler(void) {

  signal_t sig = RxGetU16();
  
  R_GUI_SetTask(Gui_DemoFileBrowserWaitSignal);
  
  if(RxStatus() == 0) {
  
    switch(sig) {

      case SIG_SELECT_FILE:
        R_GUI_M_FileBrowser(FILE_BROWSER_SEL_FILE, OFFSET_PATH_FILE, PATH_BUFF_SIZE);
        break;
      case SIG_SELECT_FOLDER:
        R_GUI_M_FileBrowser(FILE_BROWSER_SEL_FOLDER, OFFSET_PATH_FOLDER, PATH_BUFF_SIZE);
        break;

      /*'menu' button*/
      case SIG_DEMO_MENU:
        R_GUI_SetTask(Gui_Demo);
        break;

      /*user has selected an item from the file browser; we have to read back the path*/
      case FILE_BROWSER_BTN_SELECT:
      
        /**
         * Send a read str request to the smart TFT;
         * Handle the answer of this request in Gui_DemoFileBrowserUpdateEntry()
         */
        R_MEM_ReadStr(OFFSET_PATH_FILE, PATH_BUFF_SIZE);
        R_MEM_ReadStr(OFFSET_PATH_FOLDER, PATH_BUFF_SIZE);
        R_GUI_SetTask(Gui_DemoFileBrowserUpdateEntry);
        break;
        
      default:
        break;
    }
  }
}


/**
 * @function Gui_DemoFileBrowserUpdateEntry
 * @brief read path and echo it
 * @param none
 * @return none
 */
static void Gui_DemoFileBrowserUpdateEntry(void) {

  /**
   * This function is executed once the answer message of R_MEM_ReadStr() is received
   */

  const uint8_t *pathFile = NULL, *pathFolder = NULL;
  
  /**
   * extract path strings from the received RX message
   * RxGetTxt() gives pointer to the string begining, and dequeue the RX message
   * until '\0'; content of pathFile & pathFolder is safe as long as no
   * message is sent to the TFT (i.e. safe until the end of this function, RX IRQ is masqued)
   */
  RxGetTxt(&pathFile);
  RxGetTxt(&pathFolder);
  
  /**
   * could also copy the string into a local buffer
   * strcpy(myLocalString, pathFile);
   */
  if(RxStatus() == 0) {
    /*echo received strings*/
    R_MEM_WriteStr(OFFSET_PATH_FILE_ECHO, PATH_BUFF_SIZE, pathFile);
    R_MEM_WriteStr(OFFSET_PATH_FOLDER_ECHO, PATH_BUFF_SIZE, pathFolder);
  }
  R_GUI_SetTask(Gui_DemoFileBrowserWaitSignal);

}
