/**
 * @file gui_w_tab.h
 * @brief tab implementation
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
#ifndef _gui_w_tab_h_
#define _gui_w_tab_h_

#include "gui.h"

/**
 * @function GUI_W_TabParentAdd
 * @brief add a tab container
 * @param const rect_st *rec: object dimension
 * @param length_t tabHeight: height of the tabs
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_TabParentAdd(const rect_st *rec, length_t tabHeight);

/**
 * @function GUI_W_TabAddToParent
 * @brief add a tab into a tab container
 * @param g_obj_st *obj: pointer to the tab container
 * @param const void *str: tab string
 * @param gui_img_t img: tab image
 * @param uint8_t selected
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_TabAddToParent(g_obj_st /*@null@*/ *obj, const void /*@null@*/ *str, gui_img_t img, uint8_t selected);


#endif
