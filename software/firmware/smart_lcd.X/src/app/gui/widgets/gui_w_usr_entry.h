/**
 * @file gui_w_usr_entry.h
 * @brief user string entry (with text selection capability) implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-09-15 : initial version
 *  0.2b  2014-02-01 : minor bug fix (refresh insert bar ONLY if entry is editable)
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

#ifndef _gui_w_usr_entry_h_
#define _gui_w_usr_entry_h_

#include "gui.h"

/**
 * @function GUI_W_UsrEntryAdd
 * @brief add user entry
 * @param const rect_st *rec: object dimension
 * @param const void *buffer: text of the user entry (may be modified)
 * @param uint16_t sizeMax: size (in bytes) of the buffer, including the \0
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_UsrEntryAdd(const rect_st *rec, void *buffer, uint16_t sizeMax, bool bEditable);

/**
 * @function GUI_W_UsrEntryInsert
 * @brief insert a string into the string of the entry key, at current user insert position
 * @param void *_g_obj: generic object
 * @param const uint8_t *strIns: string to insert
 * @return none
 */
void GUI_W_UsrEntryInsert(g_obj_st *obj, const uint8_t *strIns);

/**
 * @function GUI_W_UsrEntrySelectAll
 * @brief select the whole string of the entry key
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntrySelectAll(g_obj_st *obj);

/**
 * @function GUI_W_UsrEntryGetSelection
 * @brief copy the selected string part into a given buffer
 * @param void *_g_obj: generic object
 * @param uint8_t *buffer: user buffer; will be \0 terminated
 * @param uint16_t bufSize: size of the user buffer
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntryGetSelection(g_obj_st *obj, uint8_t *buffer, uint16_t bufSize);

/**
 * @function GUI_W_UsrEntryDelete
 * @brief Delete the selected string part (if any), or the car corresponding to insert line position
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntryDelete(g_obj_st *obj);

#endif
