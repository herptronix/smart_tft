/**
 * @file gui_m_file_browser.c
 * @brief file browser macro (select a file of the SD card)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-10-27
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

#include "gui_m.h"
#include "gui_w.h"
#include "diskio.h"
#include "ff.h"
#include "resources.h"

/*signals of the macro' widgets*/
#define SIG_LIST            1
#define SIG_BTN_SELECT      2
#define SIG_BTN_ESC         3

/*hidden bytes: injected in str[0] of an item' string; not displayed, but used for sorting the list*/
/*e.g. this allows to sort folders BEFORE files*/
#define HDN_FOLDER          1
#define HDN_FILE            2
#define HDN_SIZE_1B         1
#define HDN_SIZE_10B        2
#define HDN_SIZE_100B       3
#define HDN_SIZE_1KB        4
#define HDN_SIZE_10KB       5
#define HDN_SIZE_100KB      6
#define HDN_SIZE_1MB        7
#define HDN_SIZE_10MB       8
#define HDN_SIZE_100MB      9
#define HDN_SIZE_1GB        10

/*max len of an item' str; 30 should be enough (FAT8.3 names, small str for size and modification date...)*/
#define STRING_ITEM         30

/**
 * local variables
 */
static uint16_t prevItemSelected;
static char *currentPath;
static uint16_t pathMaxLen;
static file_browser_mode_e mode;
static g_obj_st *btnSelect;

/**
 * local functions
 */
static signal_t GUI_M_FileBrowserHandler(signal_t signal);
static int8_t BrowseFolder(void);
static int8_t ComputeRect(rect_st *recWnd, rect_st *recList, rect_st *recEntry, rect_st *recBtnSelect, rect_st *recBtnEsc);
static int8_t AddItem(FILINFO *fno);
static gui_img_t GetFileIcon(const FILINFO *fno);
static void GetSizeStr(const FILINFO *fno, char *str, uint16_t strMaxLen);
static void GetLastModificationStr(const FILINFO *fno, char *str, uint16_t strMaxLen);
static void PreviousPath(void);
static void NextPath(char *folderName);


/**
 * @function GUI_M_FileBrowser
 * @brief file browser macro
 * @param file_browser_mode_e m: select mode (select file OR folder
 * @param char *path: pointer to an already allocated string (in/out)
 * @param uint16_t len: max path length
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_FileBrowser(file_browser_mode_e m, char *path, uint16_t len) {

  rect_st recWnd, recList, recEntry, recBtnSelect, recBtnEsc;
  int8_t res = -1;

  if(path != NULL && len > 10 && m < _FILE_BROWSER_SEL && ComputeRect(&recWnd, &recList, &recEntry, &recBtnSelect, &recBtnEsc) == 0) {

    /*store the input params*/
    currentPath = path;
    pathMaxLen = len;
    mode = m;

    /*open the top layer*/
    GUI_TopLayerOpen(GUI_M_FileBrowserHandler);

    /*window background*/
    P2D_SetColor(GetColor(G_COL_BACKGROUND));
    P2D_SetClip(&recWnd);
    P2D_FillRect(&recWnd);

    do {

      /*address entry (edition disabled)*/
      if(GUI_W_UsrEntryAdd(&recEntry, currentPath, pathMaxLen, false) == NULL) break;

      /*Select button*/
      GUI_W_ButtonSetPlacementOrder(0);
      btnSelect = GUI_W_ButtonAdd(&recBtnSelect, "Select", G_IMG_OK);
      if(btnSelect == NULL) break;
      GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_BTN_SELECT);

      /*Cancel button*/
      if(GUI_W_ButtonAdd(&recBtnEsc, "Cancel", G_IMG_NO) == NULL) break;
      GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_BTN_ESC);

      /*add the list; due to GUI_M_ListDeleteContent(), the list shall be the last allocated object !*/
      if(GUI_M_ListAdd(&recList, true, true, true, E_PUSHED_TO_RELEASED, SIG_LIST) < 0) break;
      if(GUI_M_ListAddCategoryToList(140, "Name") < 0) break;
      if(GUI_M_ListAddCategoryToList(65, "Size") < 0) break;
      if(GUI_M_ListAddCategoryToList(115, "Modified") < 0) break;

      /*try to browse the user path*/
      if(BrowseFolder() < 0) {

        /*error? the user may have include the file name; remove it & retry*/
        PreviousPath();
        if(BrowseFolder() < 0) {

          /*still error? the path may be wrong; go to root*/
          currentPath[0] = 0;
          (void) BrowseFolder();
        }
      }

      /*success*/
      res = 0;

    } while(0);
  }

  /*serious error*/
  if(res < 0) {
    GUI_TopLayerClose();
  }

  return res;
}


/**
 * @function GUI_M_FileBrowserHandler
 * @brief file browser handler
 * @param signal_t signal: input signal, coming from macro's widgets
 * @return signal_t 0 / SIG_BTN_SELECT / FILE_BROWSER_BTN_CANCEL
 */
static signal_t GUI_M_FileBrowserHandler(signal_t signal) {

  uint16_t id = 0xFFFF;
  signal_t res = 0;
  char str[STRING_ITEM];

  /*retrieve the name of the selected item*/
  str[0] = 0;
  GUI_M_ListGetSelectedItemField(0, str, STRING_ITEM);

  /*according to the selected item and the browser mode, enable/disable the select button*/
  if( (str[0] == 0) ||                                            /*no item selected*/
      (str[0] == HDN_FOLDER && mode == FILE_BROWSER_SEL_FILE)  || /*selected item is a folder, user wants a file*/
      (str[0] == HDN_FILE && mode == FILE_BROWSER_SEL_FOLDER)  || /*selected item is a file, user wants a folder*/
      (str[0] == HDN_FOLDER && str[1] == '.' && str[2] == '.')) { /*the <..> folder cannot be selected*/
    GUI_ObjSetDisabled(btnSelect, true);
  }
  else {
    GUI_ObjSetDisabled(btnSelect, false);
  }

  /*handle signals*/
  switch(signal) {

    /*select button*/
    case SIG_BTN_SELECT:
      res = FILE_BROWSER_BTN_SELECT;
      NextPath(&str[1]);
      break;

    /*cancel button*/
    case SIG_BTN_ESC:
      res = FILE_BROWSER_BTN_CANCEL;
      break;

    /*list*/
    case SIG_LIST:

      /*current item is the same than the older one && item is a folder?*/
      GUI_M_ListGetSelectedItemUid(&id);
      if(id == prevItemSelected && str[0] == HDN_FOLDER) {

        /*return to parent folder*/
        if(str[1] == '.' && str[2] == '.') PreviousPath();

        /*go to selected folder*/
        else NextPath(&str[1]);

        /*update list content with the new current path*/
        BrowseFolder();

      }
      else {
        prevItemSelected = id;
      }
      break;

    default:
      break;
  }

  /*select / cancel button => return to user page*/
  if(res != 0) {
    GUI_TopLayerClose();
  }

  return res;
}


/**
 * @function ComputeRect
 * @brief returns the dimension of objects composing the file browser macro
 * @param rect_st *recWnd: window
 * @param rect_st *recList: file list
 * @param rect_st *recEntry: address bar
 * @param rect_st *recBtnSelect: select button
 * @param rect_st *recBtnEsc: cancel button
 * @return 0
 */
static int8_t ComputeRect(rect_st *recWnd, rect_st *recList, rect_st *recEntry, rect_st *recBtnSelect, rect_st *recBtnEsc) {

  #define BTN_WIDTH   65
  #define BTN_HEIGHT  19
  #define PITCH       3

  recWnd->x = 10;
  recWnd->y = 15;
  recWnd->w = 300;
  recWnd->h = 210;

  recEntry->x = recWnd->x + PITCH;
  recEntry->y = recWnd->y + PITCH;
  recEntry->w = recWnd->w - 2 * PITCH;
  recEntry->h = P2D_GetTextHeight() + 4;

  recBtnEsc->x = recWnd->x + recWnd->w - PITCH - BTN_WIDTH;
  recBtnEsc->y = recWnd->y + recWnd->h - PITCH - BTN_HEIGHT;
  recBtnEsc->w = BTN_WIDTH;
  recBtnEsc->h = BTN_HEIGHT;

  recBtnSelect->x = recBtnEsc->x - PITCH - BTN_WIDTH;
  recBtnSelect->y = recBtnEsc->y;
  recBtnSelect->w = BTN_WIDTH;
  recBtnSelect->h = BTN_HEIGHT;

  recList->x = recEntry->x;
  recList->y = recEntry->y + recEntry->h + PITCH;
  recList->w = recEntry->w;
  recList->h = recBtnEsc->y - PITCH - recList->y;

  return 0;
}


/**
 * @function NextPath
 * @brief Add a folder (...or a file) name into the *currentPath
 * @param none
 * @return none
 */
static void NextPath(char *folderName) {

  char *path;
  uint16_t ii;

  ii = strlen(currentPath);
  path = &currentPath[ii];

  /*add the '/'*/
  if(ii < pathMaxLen - 1) {
    *path = '/';
    path++;
    ii++;
  }

  /*add the name*/
  while(*folderName != 0 && ii < pathMaxLen - 1) {
    *path = *folderName;
    path++;
    folderName++;
    ii++;
  }

  /*always terminate the current path with '\0'*/
  *path = 0;
}


/**
 * @function PreviousPath
 * @brief clear the right part of *currentPath from the last '/' (included)
 * @param none
 * @return none
 */
static void PreviousPath(void) {

  int16_t ii;
  bool bDone = false;
  ii = strlen(currentPath);

  while(ii >= 0 && bDone == false) {
    if(currentPath[ii] == '/') bDone = true;
    currentPath[ii] = 0;
    ii--;
  }
}


/**
 * @function BrowseFolder
 * @brief Browse the current path and add the items of this path into the list
 * @param none
 * @return int8_t: 0 success, -1 error (invalid path), -2 error (GUI error)
 */
static int8_t BrowseFolder(void) {

  FILINFO fno;
  DIR dir;
  bool bDone = false;
  int8_t res = -1;

  /*clear the previous list' content*/
  GUI_M_ListDeleteContent();
  prevItemSelected = 0xFFFF;

  /*open the directory*/
  if(f_opendir(&dir, currentPath) == FR_OK) {

    /*if not root ("" or "/"), add the <..> for returning in parent directory*/
    if(strlen(currentPath) > 1) {
      fno.fattrib |= AM_DIR;
      fno.fdate = 0xFFFF;
      sprintf(fno.fname, "..");
      if(AddItem(&fno) < 0) {
        bDone = true;
        res = -2;
      }
    }

    /*add each item composing the current path*/
    while(bDone == false) {

      /*FS error? exit with error*/
      if(f_readdir(&dir, &fno) != FR_OK) {
        bDone = true;
      }
      /*No more items to add? exit with success*/
      else if(fno.fname[0] == 0) {
        res = 0;
        bDone = true;
      }
      /*add the current item (file or folder)*/
      else {
        /*error when adding an item to the list? exit with error*/
        if(AddItem(&fno) < 0) {
          bDone = true;
          res = -2;
        }
      }
    }

    /*f_closedir(&dir); f_closedir does not exist?? TODO: memory leak here? or not? TBD*/
  }

  return res;
}


/**
 * @function AddItem
 * @brief add an FILINFO into the list
 * @param const FILINFO *fno: pointer to the FILINFO
 * @return int8_t: 0 success, -1: error coming from GUI
 */
static int8_t AddItem(FILINFO *fno) {

  char str[STRING_ITEM];
  gui_img_t img;
  int8_t res = -1;

  do {

    /* 1) Create a new item into the list*/
    img = GetFileIcon(fno);
    if(GUI_M_ListAddItemToList(img, NULL) < 0) break;

    /* 2) Assemble the item name with the hidden byte*/
    str[0] = ((fno->fattrib & AM_DIR) != 0) ? HDN_FOLDER: HDN_FILE;
    gstrncpy(&str[1], fno->fname, STRING_ITEM - 1);
    if(GUI_M_ListAddFieldToLastItem(str) < 0) break;

    /* 3) Add the size*/
    GetSizeStr(fno, str, STRING_ITEM);
    if(GUI_M_ListAddFieldToLastItem(str) < 0) break;

    /* 4) Add the modification timestamp*/
    GetLastModificationStr(fno, str, STRING_ITEM);
    if(GUI_M_ListAddFieldToLastItem(str) < 0) break;

    res = 0;  /*success*/

  } while(0);

  return res;
}


/**
 * @function GetFileIcon
 * @brief return an icon according to the extension of a FILINFO
 * @param const FILINFO *fno: pointer to the FILINFO
 * @return gui_img_t
 */
static gui_img_t GetFileIcon(const FILINFO *fno) {

  gui_img_t img;
  uint16_t ii;
  const char *str;

  #define SUPPORTED_EXT 18  /*canot use flexible array in declaration...*/
  typedef struct {
    const char *ext;
    gui_img_t img;
  } file_icon_st;

  const file_icon_st iconAr[SUPPORTED_EXT] = {
    {"TXT", G_IMG_FILE_TXT},
    {"BIN", G_IMG_FILE_APP},
    {"EXE", G_IMG_FILE_APP_WIN},
    {"ZIP", G_IMG_FILE_ZIP},
    {"RAR", G_IMG_FILE_ZIP},
    {"WAV", G_IMG_FILE_AUDIO},
    {"MP3", G_IMG_FILE_AUDIO},
    {"TMP", G_IMG_FILE_TMP},
    {"TTF", G_IMG_FILE_FONT},
    {"BMP", G_IMG_FILE_IMG},
    {"JPG", G_IMG_FILE_IMG},
    {"PNG", G_IMG_FILE_IMG},
    {"ASM", G_IMG_FILE_ASM},
    {"C", G_IMG_FILE_C},
    {"H", G_IMG_FILE_H},
    {"SH", G_IMG_FILE_SCRIPT},
    {"HTM", G_IMG_FILE_HTML},
    {"MAN", G_IMG_FILE_INFO}
  };

  if(fno->fattrib & AM_DIR) {
    img = G_IMG_FOLDER;
  }
  else {

    img = G_IMG_FILE_EMPTY;

    /*find the extension*/
    str = &(fno->fname[0]);
    while(*str != 0 && *str != '.') str++;

    /*check that the extension exists*/
    if(*str == '.') {
      str++;

      /*find the associated icon*/
      for(ii = 0; ii < SUPPORTED_EXT && img == G_IMG_FILE_EMPTY; ii++) {
        if(strcmp(str, iconAr[ii].ext) == 0) img = iconAr[ii].img;
      }
    }
    /*no extension ?*/
    else {
      img = G_IMG_FILE_UNKNOWN;
    }
  }

  return img;
}


/**
 * @function GetSizeStr
 * @brief return a formatted str (3digits + unit) of the size of a FILINFO
 * @param const FILINFO *fno: pointer to the FILINFO
 * @param char *str: output string (must be allocated)
 * @param uint16_t strMaxLen: max string length
 * @return none
 */
static void GetSizeStr(const FILINFO *fno, char *str, uint16_t strMaxLen) {

  uint8_t ii;
  char strSize[20];

  #define SIZE_STR_FMT_CNT (HDN_SIZE_1GB)
  typedef struct {
    uint32_t size;
    uint32_t div;
    uint8_t hdn, dot;
    const char *unit;
  } file_size_fmt_st;

  const file_size_fmt_st sizeFmtArray[SIZE_STR_FMT_CNT] = {
    {(uint32_t)10         , (uint32_t)1         , HDN_SIZE_1B   , 0, "B"},
    {(uint32_t)100        , (uint32_t)1         , HDN_SIZE_10B  , 0, "B"},
    {(uint32_t)1000       , (uint32_t)1         , HDN_SIZE_100B , 0, "B"},
    {(uint32_t)10000      , (uint32_t)10        , HDN_SIZE_1KB  , 1, "KB"},
    {(uint32_t)100000     , (uint32_t)100       , HDN_SIZE_10KB , 2, "KB"},
    {(uint32_t)1000000    , (uint32_t)1000      , HDN_SIZE_100KB, 0, "KB"},
    {(uint32_t)10000000   , (uint32_t)10000     , HDN_SIZE_1MB  , 1, "MB"},
    {(uint32_t)100000000  , (uint32_t)100000    , HDN_SIZE_10MB , 2, "MB"},
    {(uint32_t)1000000000 , (uint32_t)1000000   , HDN_SIZE_100MB, 0, "MB"},
    {(uint32_t)0xFFFFFFFF , (uint32_t)1000000000, HDN_SIZE_1GB  , 0, "GB"}
  };

  /*if the item is a folder, just return a " " (FatFS returns size == 0 for folder)*/
  if(fno->fattrib & AM_DIR) {
    sprintf(str, " ");
  }

  /*if the item is a file, return a formatted string*/
  else {

    /*find the format which correspond to the file size*/
    for(ii = 0; ii < SIZE_STR_FMT_CNT; ii++) {
      if(fno->fsize < sizeFmtArray[ii].size) break;
    }

    /*printf the 3 most significant digits*/
    sprintf(strSize, "%ld", fno->fsize / sizeFmtArray[ii].div);

    /*insert the dot '.', if any*/
    switch(sizeFmtArray[ii].dot) {

      case 1:
        strSize[4] = 0;
        strSize[3] = strSize[2];
        strSize[2] = strSize[1];
        strSize[1] = '.';
        break;

      case 2:
        strSize[4] = 0;
        strSize[3] = strSize[2];
        strSize[2] = '.';
        break;

      default:
        break;
    }

    /*assemble the final str*/
    snprintf(str, strMaxLen, "%c%s %s", sizeFmtArray[ii].hdn, strSize, sizeFmtArray[ii].unit);
  }
}


/**
 * @function GetLastModificationStr
 * @brief return the last modification date/time of a FILINFO
 * @param const FILINFO *fno: pointer to the FILINFO
 * @param char *str: output string (must be allocated)
 * @param uint16_t strMaxLen: max string length
 * @return none
 */
static void GetLastModificationStr(const FILINFO *fno, char *str, uint16_t strMaxLen) {

  uint16_t year;
  uint8_t month, date, hour, min;

  /*check if the date is 'valid': no date for the <..> folder> */
  if(fno->fdate != 0xFFFF) {
    year = (fno->fdate >> 9) + 1980;
    month = (uint8_t) ( (fno->fdate >> 5) & 0x000F);
    date = (uint8_t) (fno->fdate & 0x001F);

    hour = (uint8_t) ( (fno->ftime >> 11) & 0x001F);
    min = (uint8_t) ( (fno->ftime >> 5) & 0x001F);

    snprintf(str, strMaxLen, "%d/%02d/%02d %02d:%02d", year, month, date, hour, min);
  }
  else {
    snprintf(str, strMaxLen, " ");
  }
}
