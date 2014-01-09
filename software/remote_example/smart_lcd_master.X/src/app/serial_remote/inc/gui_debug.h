/**
 * @file gui_debug.h
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

#ifndef _gui_debug_h
#define _gui_debug_h

#include "gui.h"

/**
 * @function GUI_DBG_DispMemUsage
 * @brief enable/disable the debug display
 * @param bool bDisp: true/false <-> display/hide
 * @return none
 */
void GUI_DBG_DispMemUsage(bool bDisp);

/**
 * @function GUI_DBG_Task
 * @brief debug display task
 * @param none
 * @return none
 */
void GUI_DBG_Task(void);

#endif