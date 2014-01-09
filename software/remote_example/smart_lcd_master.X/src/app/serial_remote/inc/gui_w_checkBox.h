/**
 * @file gui_w_checkBox.h
 * @brief basic checkBox implementation
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-07-13
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
#ifndef _gui_w_checkBox_h_
#define _gui_w_checkBox_h_

#include "gui.h"

/**
 * @function GUI_W_CheckBoxAdd
 * @brief add a basic check box
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the checkbox (will be copied into it)
 * @param const uint8_t *pState: pointer to the state of the checkbox (*p == 0: untick, tick otherwise)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_CheckBoxAdd(const rect_st *rec, const void /*@null@*/ *str, const uint8_t *pState);


#endif
