/**
 * @file gui_m_list.c
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

#include "gui_w.h"

#define LEN_SCROLL  10   /*length of a scroller (in pixel)*/
#define PITCH       2   /*space between scrollers & list (in pixel)*/


/**
 * Local functions
 */
static int8_t ComputeRects(const rect_st *rec, rect_st *list_rec, rect_st *vScroll_rec, rect_st *hScroll_rec, bool bVscroll, bool bHscroll);

/**
 * Local variables
 */
static g_obj_st *pList = NULL;


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
g_obj_st /*@null@*/ *GUI_M_ListAdd(const rect_st *rec, bool bHeader, bool bVscroll, bool bHscroll, event_e event, signal_t signal) {

  rect_st list_rec, vScroll_rec, hScroll_rec;
  scroll_param_st *vScrollParam, *hScrollParam;
  g_obj_st *res = NULL, *pvScroll = NULL, *phScroll = NULL;

  /*last added list = NULL*/
  pList = NULL;

  /*computes rect of list, scroller V & scroller H*/
  if(ComputeRects(rec, &list_rec, &vScroll_rec, &hScroll_rec, bVscroll, bHscroll) == 0) {

    /*create the list*/
    pList = GUI_W_ListCreate(
      &list_rec,
      bHeader,
      bVscroll == false? NULL : &vScrollParam,
      bHscroll == false? NULL : &hScrollParam
    );

    if(pList != NULL) {

      /*set the user signal*/
      if(signal > 0) GUI_SetSignal(event, signal);

      /*create the scrollers, if any*/
      if(bVscroll) pvScroll = GUI_W_ScrollerAdd(&vScroll_rec, pList, vScrollParam);
      if(bHscroll) phScroll = GUI_W_ScrollerAdd(&hScroll_rec, pList, hScrollParam);

      /*return value: pList if success, NULL if error (salloc / wrong coords)*/
      if( (bVscroll == false || pvScroll != NULL) && (bHscroll == false || phScroll != NULL) ) res = pList;
    }
  }

  return res;
}


/**
 * @function GUI_M_ListAddCategoryToList
 * @brief add a new category into the last added list by GUI_M_ListAdd
 * @param length_t w: width (in pixel)
 * @param const void *name: name of the category
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddCategoryToList(length_t w, const void *name) {
  int8_t res = -1;
  if(pList != NULL) {
    res = GUI_W_ListAddCategoryToList(pList, w, name);
  }
  return res;
}


/**
 * @function GUI_M_ListAddItemToList
 * @brief add a new item into the last added list by GUI_M_ListAdd
 * @param gui_img_t sprite: sprite of the item
 * @param uint16_t *uid: if non null, the uid of the new item will be written into it
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddItemToList(gui_img_t sprite, uint16_t /*@null@*/ *uid) {
  int8_t res = -1;
  if(pList != NULL) {
    res = GUI_W_ListAddItemToList(pList, sprite, uid);
  }
  return res;
}


/**
 * @function GUI_M_ListAddFieldToLastItem
 * @brief add a field to the last added item of the last added list by GUI_M_ListAdd, after the last added field
 * @param const void *str: content of the field
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListAddFieldToLastItem(const void *str) {
  int8_t res = -1;
  if(pList != NULL) {
    res = GUI_W_ListAddFieldToLastItem(pList, str);
  }
  return res;
}


/**
 * @function GUI_M_ListDeleteContent
 * @brief delete all items of the last added list by GUI_M_ListAdd. ITEMS SHALL BE THE LAST ALLOCATED ELEMENTS !!
 * @param none
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_M_ListDeleteContent(void) {
  int8_t res = -1;
  if(pList != NULL) {
    GUI_W_ListDeleteContent(pList);
    res = 0;
  }
  return res;
}


/**
 * @function GUI_M_ListGetSelectedItemUid
 * @brief gets the UID of the selected item of the last added list by GUI_M_ListAdd
 * @param uint16_t *uid: will contain the uid of selected item; if no selected item, *uid will not be modified
 * @return int8_t: 0 success, -1 error (no selected item / *obj is not a list)
 */
int8_t GUI_M_ListGetSelectedItemUid(uint16_t *uid) {
  int8_t res = -1;
  if(pList != NULL) {
    res = GUI_W_ListGetSelectedItemUid(pList, uid);
  }
  return res;
}


/**
 * @function GUI_M_ListGetSelectedItemField
 * @brief gets the content of the field of the selected item of the last added list by GUI_M_ListAdd, corresponding to a categoy #id
 * @param uint8_t catId: category #id
 * @param void *str: will contain the content of the selected item; if no selected item, *str will not be modified
 * @param uint16_t len: *str length (in byte)
 * @return int8_t: 0 success, -1 error (no selected item / invalid catId / *obj is not a list / *str==NULL)
 */
int8_t GUI_M_ListGetSelectedItemField(uint8_t catId, void *str, uint16_t len) {
  int8_t res = -1;
  if(pList != NULL) {
    res = GUI_W_ListGetSelectedItemField(pList, catId, str, len);
  }
  return res;
}


/**
 * @function ComputeRects
 * @brief computes rect of list, v scroll & h scroll
 * @param const rect_st *rec: total dimension
 * @param rect_st *list_rec: list rect (out)
 * @param rect_st *vScroll_rec: v scroll rect (out)
 * @param rect_st *hScroll_rec: h scroll rect (out)
 * @param bool bVscroll, bHscroll: computes rect with/without scrolls
 * @return int8_t: 0 success, -1 error
 */
static int8_t ComputeRects(const rect_st *rec, rect_st *list_rec, rect_st *vScroll_rec, rect_st *hScroll_rec, bool bVscroll, bool bHscroll) {

  int8_t res = -1;

  if(rec != NULL) {

    *list_rec = *rec;

    do {

      if(bVscroll) {
        if(rec->w > LEN_SCROLL + PITCH) list_rec->w = rec->w - LEN_SCROLL - PITCH;
        else break;
      }

      if(bHscroll) {
        if(rec->h > LEN_SCROLL + PITCH) list_rec->h = rec->h - LEN_SCROLL - PITCH;
        else break;
      }

      if(bVscroll) {
        vScroll_rec->x = list_rec->x + list_rec->w + PITCH;
        vScroll_rec->y = list_rec->y;
        vScroll_rec->w = LEN_SCROLL;
        vScroll_rec->h = list_rec->h;
      }

      if(bHscroll) {
        hScroll_rec->x = list_rec->x;
        hScroll_rec->y = list_rec->y + list_rec->h + PITCH;
        hScroll_rec->w = list_rec->w;
        hScroll_rec->h = LEN_SCROLL;
      }

      res = 0;

    } while(0);
  }

  return res;
}
