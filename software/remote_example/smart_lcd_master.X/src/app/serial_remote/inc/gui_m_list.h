/**
 * @file gui_m_list.h
 * @brief macro for list; the easy way
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-10-10
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

#ifndef _gui_m_list_h_
#define _gui_m_list_h_

#include "gui.h"

/**
 * @function GUI_M_ListAdd
 * @brief create a list and its scrollers
 * @param const rect_st *rec: total dimension; list + scrollers will be contained into it
 * @param bool bHeader: if true, categories will be displayed
 * @param bool bVscroll: if true, a vertical scroller will be added
 * @param bool hVscroll: if true, a horizontal scroller will be added
 * @param event_e event, signal_t signal: signal from the list
 * @return g_obj_st *: pointer to the associated generic object of the list if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_M_ListAdd(const rect_st *rec, bool bHeader, bool bVscroll, bool bHscroll, event_e event, signal_t signal);

/**
 * @function GUI_M_ListAddCategoryToList
 * @brief add a new category into the last added list by GUI_M_ListAdd
 * @param length_t w: width (in pixel)
 * @param const void *name: name of the category
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddCategoryToList(length_t w, const void *name);

/**
 * @function GUI_M_ListAddItemToList
 * @brief add a new item into the last added list by GUI_M_ListAdd
 * @param gui_img_t sprite: sprite of the item
 * @param uint16_t *uid: if non null, the uid of the new item will be written into it
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddItemToList(gui_img_t sprite, uint16_t /*@null@*/ *uid);

/**
 * @function GUI_M_ListAddFieldToLastItem
 * @brief add a field to the last added item of the last added list by GUI_M_ListAdd, after the last added field
 * @param const void *str: content of the field
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddFieldToLastItem(const void *str);

/**
 * @function GUI_M_ListDeleteContent
 * @brief delete all items of the last added list by GUI_M_ListAdd. ITEMS SHALL BE THE LAST ALLOCATED ELEMENTS !!
 * @param none
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListDeleteContent(void);

/**
 * @function GUI_M_ListGetSelectedItemUid
 * @brief gets the UID of the selected item of the last added list by GUI_M_ListAdd
 * @param uint16_t *uid: will contain the uid of selected item; if no selected item, *uid will not be modified
 * @return int8_t: 0 success, -1 error (no selected item / *obj is not a list)
 */
int8_t GUI_M_ListGetSelectedItemUid(uint16_t *uid);

/**
 * @function GUI_M_ListGetSelectedItemField
 * @brief gets the content of the field of the selected item of the last added list by GUI_M_ListAdd, corresponding to a categoy #id
 * @param uint8_t catId: category #id
 * @param void *str: will contain the content of the selected item; if no selected item, *str will not be modified
 * @param uint16_t len: *str length (in byte)
 * @return int8_t: 0 success, -1 error (no selected item / invalid catId / *obj is not a list / *str==NULL)
 */
int8_t GUI_M_ListGetSelectedItemField(uint8_t catId, void *str, uint16_t len);

#endif
