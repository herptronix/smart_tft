/**
 * @file gui_m_file_browser.h
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

#ifndef _gui_m_file_browser_h_
#define _gui_m_file_browser_h_

#include "gui.h"

#define FILE_BROWSER_BTN_SELECT   0xF0F1
#define FILE_BROWSER_BTN_CANCEL   0xF0F2

typedef enum {
  FILE_BROWSER_SEL_FILE,
  FILE_BROWSER_SEL_FOLDER,
  _FILE_BROWSER_SEL
} file_browser_mode_e;


/**
 * @function GUI_M_FileBrowser
 * @brief file browser macro
 * @param file_browser_mode_e m: select mode (select file OR folder
 * @param char *path: pointer to an already allocated string (in/out)
 * @param uint16_t len: max path length
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_FileBrowser(file_browser_mode_e m, char *path, uint16_t len);


#endif
