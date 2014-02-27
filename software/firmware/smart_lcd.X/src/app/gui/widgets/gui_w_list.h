/**
 * @file gui_w_list.h
 * @brief list implementation; use GUI_M_List instead
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd) 2013-10-10 initial version
 *                    2014-01-30 minor bug fix
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

#ifndef _gui_w_list_h_
#define _gui_w_list_h_

#include "gui_w.h"

/**
 * @function GUI_W_ListCreate
 * @brief add list container
 * @param const rect_st *rec: list dimension
 * @param bool bHeader: if true, categories will be displayed (*rec will be shared between list & its header)
 * @param scroll_param_st **pvScroll: if non null, will recieve the addr of the internal vertical scroll struct
 * @param scroll_param_st **phScroll: if non null, will recieve the addr of the internal horizontal scroll struct
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ListCreate(const rect_st *rec, bool bHeader, scroll_param_st /*@null@*/ **pvScroll, scroll_param_st /*@null@*/ **phScroll);

/**
 * @function GUI_W_ListAddCategoryToList
 * @brief add a new category into a list
 * @param g_obj_st *obj: pointer to list
 * @param length_t w: width (in pixel)
 * @param const void *name: name of the category
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddCategoryToList(g_obj_st /*@null@*/ *obj, length_t w, const void *name);

/**
 * @function GUI_W_ListAddItemToList
 * @brief add a new item into a list
 * @param g_obj_st *obj: pointer to list
 * @param gui_img_t sprite: sprite of the item
 * @param uint16_t *uid: if non null, the uid of the new item will be written into it
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddItemToList(g_obj_st /*@null@*/ *obj, gui_img_t sprite, uint16_t /*@null@*/ *uid);

/**
 * @function GUI_W_ListAddFieldToLastItem
 * @brief add a field to the last added item, after the last added field
 * @param g_obj_st *obj: pointer to list
 * @param const void *str: content of the field
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddFieldToLastItem(g_obj_st /*@null@*/ *obj, const void *str);

/**
 * @function GUI_W_ListDeleteContent
 * @brief delete all items of a given list. ITEMS SHALL BE THE LAST ALLOCATED ELEMENTS !!
 * @param g_obj_st *obj: pointer to list
 * @return none
 */
void GUI_W_ListDeleteContent(g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_W_ListGetSelectedItemUid
 * @brief gets the UID of the selected item
 * @param g_obj_st *obj: pointer to list
 * @param uint16_t *uid: will contain the uid of selected item; if no selected item, *uid will not be modified
 * @return int8_t: 0 success, -1 error (no selected item / *obj is not a list)
 */
int8_t GUI_W_ListGetSelectedItemUid(g_obj_st /*@null@*/ *obj, uint16_t *uid);

/**
 * @function GUI_W_ListGetSelectedItemField
 * @brief gets the content of the field of the selected item, corresponding to a categoy #id
 * @param g_obj_st *obj: pointer to list
 * @param uint8_t catId: category #id
 * @param void *str: will contain the content of the selected item; if no selected item, *str will not be modified
 * @param uint16_t len: *str length (in byte)
 * @return int8_t: 0 success, -1 error (no selected item / invalid catId / *obj is not a list / *str==NULL)
 */
int8_t GUI_W_ListGetSelectedItemField(g_obj_st /*@null@*/ *obj, uint8_t catId, void *str, uint16_t len);

#endif
