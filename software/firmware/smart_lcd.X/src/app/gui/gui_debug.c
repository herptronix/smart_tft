/**
 * @file gui_debug.c
 * @brief some debug tools for GUI
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-10-16
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

#include "gui_debug.h"
#include "salloc.h"
#include "resources.h"

/**
 * local variables
 */
static bool bDispMem = false;
static timer_t tmDisp = 0;
static uint32_t cycleCnt = 0;


/**
 * @function GUI_DBG_DispMemUsage
 * @brief enable/disable the debug display
 * @param bool bDisp: true/false <-> display/hide
 * @return none
 */
void GUI_DBG_DispMemUsage(bool bDisp) {
  bDispMem = bDisp;
  cycleCnt = 0;
  tmDisp = 0;
}


/**
 * @function GUI_DBG_Task
 * @brief debug display task
 * @param none
 * @return none
 */
void GUI_DBG_Task(void) {

  gui_font_t font;
  #define DEBUG_STR 50
  char str[DEBUG_STR];

  if(bDispMem) {

    /*display every 1s*/
    if(IsTimerElapsed(tmDisp)) {

      /*save current user font*/
      font = GetCurrentFont();

      /*configure P2D*/
      P2D_SetDisplayMode(DISPLAY_SOLID);
      P2D_SetClip(NULL);
      SetFont(G_FONT_DEFAULT);
      P2D_SetColors(COLOR_BLACK, COLOR_LIGHT_GREY);
      snprintf(str, DEBUG_STR, "MEM:%06d/%06dB   CY:%04d", sallocGetUsed(), sallocGetTotal(), cycleCnt);

      /*display info*/
      P2D_PutText(0, LCD_GetHeight() - P2D_GetTextHeight(), str);

      /*restore current user font*/
      SetFont(font);

      tmDisp = GetPeriodicTimeout(1000);
      cycleCnt = 0;
    }
    cycleCnt++;
  }
}
