/**
 * @file gui_w_scroller.h
 * @brief scroller bar implementation
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-08-27  : initial version
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

#ifndef _gui_w_scroller_h_
#define _gui_w_scroller_h_

#include "gui.h"

/**
 * scroll_param_st
 */
typedef struct {
  uint16_t offset;
  uint16_t wndSize;
  uint16_t totSize;
} scroll_param_st;

/**
 * @function GUI_W_ScrollerAdd
 * @brief add a scroller bar
 * @param const rect_st *rec: object dimension
 * @param g_obj_st *refreshObj: object to refresh when scroll changes
 * @param scroll_param_st *param: already-allocated scroller param
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param);

/**
 * @function GUI_W_ScrollerSetOffset
 * @brief set the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @param int32_t offset: new value
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerSetOffset(scroll_param_st *p, int32_t offset);

/**
 * @function GUI_W_ScrollerIncOffset
 * @brief increment the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerIncOffset(scroll_param_st *p);

/**
 * @function GUI_W_ScrollerDecOffset
 * @brief decrement the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerDecOffset(scroll_param_st *p);

#endif
