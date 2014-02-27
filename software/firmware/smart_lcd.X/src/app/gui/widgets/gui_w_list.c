/**
 * @file gui_w_list.c
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

#include "gui_w.h"
#include "resources.h"

#define LIST_W_MIN  100   /*minimal width, in pixel*/
#define LIST_H_MIN  3     /*minimal height, in line*/


/**
 * field_st
 * content of one field of one item
 */
typedef struct field_t {
  struct field_t *pVn;        /*pointer to the vertical next; if NULL, I'm the tail of my category_t*/
  struct field_t *pVp;        /*pointer to the vertical previous; if NULL, I'm the head of my category_t*/
  struct field_t *pHn;        /*pointer to the horizontal next*/
  struct item_t *pItem;       /*pointer to the item (i.e. horizontal origin)*/
  uint8_t *str;               /*string of the field*/
} field_st;

/**
 * category_st
 * header; contains the list of all fields belonging to the same category (i.e. of the same column)
 */
typedef struct category_t {
  struct category_t *next;    /*pointer to the next category of the list*/
  field_st *head;
  field_st *tail;
  uint8_t *name;              /*name of the current category*/
  length_t w;                 /*width, in pixel*/
} category_st;

/**
 * item_st
 * one item (i.e. one line of the list)
 */
typedef struct item_t {
  field_st *pHn;              /*pointer to the item's fields linked list*/
  uint16_t uid;               /*unique identifier*/
  gui_img_t sprite;           /*will be displayed at the begin of the first field*/
} item_st;

/**
 * list_st
 * the overall object
 */
typedef struct {
  category_st *pCategory;           /*pointer to the head of categories*/
  category_st *pSelectedCategory;   /*pointer to the category used for display sort*/
  uint8_t categoryCount;            /*number of category*/
  bool bReversedSort;               /*if false, sort 'a' to 'z', else 'z' to 'a'*/

  item_st *pLastItem;               /*pointer to the last added item*/
  item_st *pSelectedItem;           /*pointer to the selected item*/
  bool bLastItemDefined;            /*if true, the last item were completely defined (all fields are defined)*/

  scroll_param_st vScroll;          /*vertical scrolling parameters*/
  scroll_param_st hScroll;          /*horizontal scrolling parameters*/
  g_obj_st *g_obj_header;

  length_t wSpriteMax;              /*maximal length of a sprite used in the list*/
  length_t hItem;                   /*height of a line (== to font height)*/
  color_t colBackOdd, colBackEven;
  gui_font_t font;

} list_st;


/**
 * list_header_st
 * header of a list
 */
typedef struct {
  g_obj_st *g_obj_list;
  coord_t xt;
} list_header_st;


/**
 * local functions
 */
static void DrawItem(const list_st *list, const rect_st *rec, const item_st *item, int16_t itemPos, coord_t x);
static void ListDraw(void *_g_obj, void *_obj);
static void ListRefresh(void *_g_obj, void *_obj);
static list_st /*@null@*/ *GetList(g_obj_st /*@null@*/ *obj);
static void InsertInCategory(list_st *list, uint8_t catId, field_st *field);
static field_st /*@null@*/ *GetFirstField(list_st *list);
static field_st /*@null@*/ *GetNextField(field_st *field, bool bReversedSort);
static void HeaderDraw(void *_g_obj, void *_obj);
static void HeaderRefresh(void *_g_obj, void *_obj);


/**
 * @function GUI_W_ListCreate
 * @brief add list container
 * @param const rect_st *rec: list dimension
 * @param bool bHeader: if true, categories will be displayed (*rec will be shared between list & its header)
 * @param scroll_param_st **pvScroll: if non null, will recieve the addr of the internal vertical scroll struct
 * @param scroll_param_st **phScroll: if non null, will recieve the addr of the internal horizontal scroll struct
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ListCreate(const rect_st *rec, bool bHeader, scroll_param_st /*@null@*/ **pvScroll, scroll_param_st /*@null@*/ **phScroll) {

  g_obj_st *g_obj = NULL, *g_obj_header = NULL, *res = NULL;
  list_st *list = NULL;
  list_header_st *header = NULL;
  length_t hItem = P2D_GetTextHeight();
  rect_st lrec;

  /*create the generic object for the list's header; configure it later*/
  if(bHeader) {
    g_obj_header = GUI_AddGenericObject();
    if(g_obj_header != NULL) {
      header = (list_header_st *) salloc(sizeof(list_header_st));
    }
  }

  /*check parameters*/
  if(rec != NULL && rec->w >= LIST_W_MIN && hItem > 0 && rec->h >= hItem * LIST_H_MIN && (header != NULL || bHeader == false)) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate and init the list*/
      list = (list_st *) salloc(sizeof(list_st));
      if(list != NULL) {

        /* *rec may be shared between list & its header*/
        lrec = *rec;
        if(bHeader) {
          lrec.y += hItem + 2;
          lrec.h -= hItem + 2;
        }

        /*ensures that all internal links are NULL & var = 0*/
        gmemset( (void *) list, 0, sizeof(list_st));

        /*init. the list*/
        list->font = GetCurrentFont();
        list->hItem = hItem;
        list->colBackOdd = GetColor(G_COL_E_BACKGROUND);
        list->colBackEven = P2D_Alpha_a_on_b(GetColor(G_COL_SPECIAL), list->colBackOdd, 32);
        list->vScroll.wndSize = lrec.h / hItem;
        list->hScroll.wndSize = lrec.w;
        list->g_obj_header = g_obj_header;

        /*return scroller addresses*/
        if(pvScroll != NULL) *pvScroll = &(list->vScroll);
        if(phScroll != NULL) *phScroll = &(list->hScroll);

        /*linkage between generic obj & list*/
        g_obj->rec = lrec;
        g_obj->draw = ListDraw;
        g_obj->task = ListRefresh;
        g_obj->obj = list;
        GUI_ObjSetStatic(g_obj, true);  /*list_st handle refresh event itself*/

        /*header linkage, if any*/
        if(header != NULL) {
          lrec.y = rec->y;
          lrec.h = hItem + 2;
          header->xt = -1;
          header->g_obj_list = g_obj;
          g_obj_header->rec = lrec;
          g_obj_header->draw = HeaderDraw;
          g_obj_header->task = HeaderRefresh;
          g_obj_header->obj = header;
          GUI_ObjSetStatic(g_obj, true);  /*header handles refresh event itself*/
        }

        res = g_obj;
      }
    }
  }

  return res;
}


/**
 * @function GUI_W_ListAddCategoryToList
 * @brief add a new category into a list
 * @param g_obj_st *obj: pointer to list
 * @param length_t w: width (in pixel)
 * @param const void *name: name of the category
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddCategoryToList(g_obj_st /*@null@*/ *obj, length_t w, const void *name) {

  int8_t res = -1;
  list_st *list = NULL;
  category_st *category = NULL, **seek = NULL;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);
  if(list != NULL) {

    /*a new category can be added only if the list does not contains any item*/
    if(list->vScroll.totSize == 0 && list->categoryCount < 255) {

      /*allocate memory for the new field header*/
      category = (category_st *) salloc(sizeof(category_st));
      if(category != NULL) {

        /*init. the category*/
        gmemset( (void *)category, 0, sizeof(category_st));
        category->w = w;
        category->name = AllocateAndCopyStr(name);

        if(name == NULL || category->name != NULL) {

          /*insert the category into its list*/
          seek = &(list->pCategory);
          while(*seek != NULL) seek = &((*seek)->next);
          *seek = category;

          /*update the category counter & the selected category (user for sort)*/
          list->categoryCount++;
          if(list->pSelectedCategory == NULL) list->pSelectedCategory = category;

          /*update the horizontal scroll size*/
          list->hScroll.totSize += w;

          res = 0;
        }
      }
    }
  }
  return res;
}


/**
 * @function GUI_W_ListAddItemToList
 * @brief add a new item into a list
 * @param g_obj_st *obj: pointer to list
 * @param gui_img_t sprite: sprite of the item
 * @param uint16_t *uid: if non null, the uid of the new item will be written into it
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddItemToList(g_obj_st /*@null@*/ *obj, gui_img_t sprite, uint16_t /*@null@*/ *uid) {

  int8_t res = -1;
  item_st *item = NULL;
  list_st *list = NULL;
  length_t wSprite;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);

  /*add item if: no item OR last item fully defined*/
  if(list != NULL && (list->pLastItem == NULL || list->bLastItemDefined == true)) {

    /*allocate memory for the new item*/
    item = (item_st *) salloc(sizeof(item_st));
    if(item != NULL) {

      /*init. the item & export uid*/
      gmemset( (void *) item, 0, sizeof(item_st));
      item->uid = list->vScroll.totSize;
      item->sprite = sprite;
      if(uid != NULL) *uid = item->uid;

      /*update the V scroll size*/
      list->vScroll.totSize++;

      /*just added, so item's fields are not yet defined*/
      list->bLastItemDefined = false;

      /*update the maximal sprite width*/
      wSprite = SpriteGetWidth(sprite);
      if(list->wSpriteMax < wSprite) list->wSpriteMax = wSprite;

      res = 0;
    }

    /*save the address of the last added item*/
    list->pLastItem = item;
  }

  return res;
}


/**
 * @function GUI_W_ListDeleteContent
 * @brief delete all items of a given list. ITEMS SHALL BE THE LAST ALLOCATED ELEMENTS !!
 * @param g_obj_st *obj: pointer to list
 * @return none
 */
void GUI_W_ListDeleteContent(g_obj_st /*@null@*/ *obj) {

  list_st *list = NULL;
  field_st *field = NULL;
  void *addr = NULL;
  category_st *category = NULL;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);
  if(list != NULL) {

    /*find the item #0*/
    field = GetFirstField(list);
    while(field != NULL && addr == NULL) {
      if(field->pItem->uid == 0) addr = (void *)field->pItem;
      else field = GetNextField(field, list->bReversedSort);
    }

    if(addr != NULL) {

      /*item found? clear all memory from its addr*/
      sfreeFrom(addr);

      /*reset list*/
      category = list->pCategory;
      while(category != NULL) {
        category->head = category->tail = NULL;
        category = category->next;
      }
      list->pLastItem = NULL;
      list->pSelectedItem = NULL;
      list->wSpriteMax = 0;
      list->vScroll.totSize = 0;

      /*need to refresh (for clearing window content)*/
      GUI_ObjSetNeedRefresh(obj, true);
    }
  }
}


/**
 * @function GUI_W_ListAddFieldToLastItem
 * @brief add a field to the last added item, after the last added field
 * @param g_obj_st *obj: pointer to list
 * @param const void *str: content of the field
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_ListAddFieldToLastItem(g_obj_st /*@null@*/ *obj, const void *str) {

  int8_t res = -1;
  uint8_t field_cnt;
  list_st *list = NULL;
  field_st *field = NULL, **seek = NULL;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);
  if(list != NULL && list->pLastItem != NULL) {

    /*retrieve the pointer to the current field and its position*/
    seek = &(list->pLastItem->pHn);
    field_cnt = 0;
    while(*seek != NULL) {
      seek = &((*seek)->pHn);
      field_cnt++;
    }

    /*check if the current item has less fields than the number of categories*/
    if(field_cnt < list->categoryCount) {

      /*allocate memory for the item's field*/
      field = (field_st *) salloc(sizeof(field_st));
      if(field != NULL) {

        /*init. the field*/
        gmemset( (void *)field, 0, sizeof(field_st));
        field->pItem = list->pLastItem;
        field->str = AllocateAndCopyStr(str);
        if(str == NULL || field->str != NULL) {

          /*insert in the horizontal list (i.e. linked to the item)*/
          *seek = field;

          /*insert in the vertical list (i.e. linked to the category)*/
          InsertInCategory(list, field_cnt, field);

          /*if all fields are defined, bLastItemDefined becomes true*/
          field_cnt++;
          if(field_cnt == list->categoryCount) list->bLastItemDefined = true;

          res = 0;
        }
      }
    }
  }

  return res;
}


/**
 * @function GUI_W_ListGetSelectedItemUid
 * @brief gets the UID of the selected item
 * @param g_obj_st *obj: pointer to list
 * @param uint16_t *uid: will contain the uid of selected item; if no selected item, *uid will not be modified
 * @return int8_t: 0 success, -1 error (no selected item / *obj is not a list)
 */
int8_t GUI_W_ListGetSelectedItemUid(g_obj_st /*@null@*/ *obj, uint16_t *uid) {

  int8_t res = -1;
  list_st *list;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);

  /*get the uid*/
  if(uid != NULL && list != NULL && list->pSelectedItem != NULL) {
    *uid = list->pSelectedItem->uid;
    res = 0;
  }

  return res;
}


/**
 * @function GUI_W_ListGetSelectedItemField
 * @brief gets the content of the field of the selected item, corresponding to a categoy #id
 * @param g_obj_st *obj: pointer to list
 * @param uint8_t catId: category #id
 * @param void *str: will contain the content of the selected item; if no selected item, *str will not be modified
 * @param uint16_t len: *str length (in byte)
 * @return int8_t: 0 success, -1 error (no selected item / invalid catId / *obj is not a list / *str==NULL)
 */
int8_t GUI_W_ListGetSelectedItemField(g_obj_st /*@null@*/ *obj, uint8_t catId, void *str, uint16_t len) {

  int8_t res = -1;
  list_st *list;
  field_st *field;

  /*retrieve the list corresponding to the generic object*/
  list = GetList(obj);
  if(str != NULL && list != NULL && list->pSelectedItem != NULL) {

    field = list->pSelectedItem->pHn;

    /*go to the field which correspond to the category #id*/
    while(catId > 0 && field != NULL) {
      field = field->pHn;
      catId--;
    }

    /*copy the field content into *str*/
    if(field != NULL) {
      gstrncpy(str, field->str, len);
      res = 0;
    }
  }

  return res;
}


/**
 * @function DrawItem
 * @brief draw an item (display all item's fields on a line)
 * @param const list_st *list: pointer to the parent list
 * @param const rect_st *rec: rec corresponding to the visible part of the line
 * @param const item_st *item: pointer to the item
 * @param int16_t itemPos: position in list (used for selecting background color)
 * @param coord_t x: x start
 * @return none
 */
static void DrawItem(const list_st *list, const rect_st *rec, const item_st *item, int16_t itemPos, coord_t x) {

  field_st *field = item->pHn;
  category_st *category = list->pCategory;
  color_t colBack, colText;
  coord_t y, xOffset;

  /*select colors*/
  if(item == list->pSelectedItem) {
    colText = GetColor(G_COL_TEXT_REVERSE);
    colBack = GetColor(G_COL_SPECIAL);
  }
  else {
    colText = GetColor(G_COL_TEXT);
    if(itemPos % 2 != 0) colBack = list->colBackEven; else colBack = list->colBackOdd;
  }

  /*clear the line & update colors (for LUT updating for font & sprite)*/
  P2D_SetColor(colBack);
  P2D_FillRect(rec);
  P2D_SetColors(colText, colBack);

  /*display the sprite*/
  y = rec->y + ((coord_t)rec->h - SpriteGetHeight(item->sprite)) / 2;
  xOffset = 2;
  Sprite(x + xOffset, y, item->sprite);

  /*finally, the first field starts at x + 2 + wSpriteMax + 2*/
  xOffset += list->wSpriteMax + 2;

  /*display all fields; objects out of screen will be automatically clipped*/
  while(field) {

    P2D_PutText(x + xOffset, rec->y, field->str);
    xOffset = 0;

    field = field->pHn;
    x += category->w;
    category = category->next;
  }
}


/**
 * @function ListDraw
 * @brief list draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: list object
 * @return none
 */
static void ListDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  list_st *list;
  field_st *field;
  uint16_t itemPos;
  rect_st lrec;
  coord_t x, yEnd;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    list =  (list_st*) _obj;

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    SetFont(list->font);

    /*find the first field to display, according to vertical offset, selected category and sort (normal/reverse) */
    itemPos = 0;
    field = GetFirstField(list);
    while(field != NULL && itemPos < list->vScroll.offset) {
      field = GetNextField(field, list->bReversedSort);
      itemPos++;
    }

    /*display items*/
    lrec = g_obj->rec;
    lrec.h = list->hItem;
    yEnd = g_obj->rec.y + g_obj->rec.h;
    x = g_obj->rec.x - list->hScroll.offset;

    while(field != NULL && lrec.y < yEnd) {

      DrawItem(list, &lrec, field->pItem, itemPos, x);

      lrec.y += lrec.h;
      itemPos++;
      field = GetNextField(field, list->bReversedSort);
    }

    /*...if there is not enought item to fill the object dimension*/
    if(lrec.y < yEnd) {
      lrec.h = g_obj->rec.h;
      P2D_SetColor(GetColor(G_COL_E_BACKGROUND));
      P2D_FillRect(&lrec);
    }
  }
}


/**
 * @function ListRefresh
 * @brief list task
 * @param void *_g_obj: generic object
 * @param void *_obj: list object
 * @return none
 */
static void ListRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  list_st *list;
  coord_t yt, y;
  uint16_t itemPos;
  field_st *field;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    list =  (list_st*) _obj;

    /*if the list need a refresh before ListRefresh() exec, it means that
      an external event leaded to this refresh(e.g. scroll) -> we need to
      maually refresh the header of the list */
    if(GUI_ObjIsNeedRefresh(g_obj) && list->g_obj_header != NULL) {
      GUI_ObjSetNeedRefresh(list->g_obj_header, true);
    }

    /*handle touchscreen interaction*/
    if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {
      GUI_ReadTouchScreen(NULL, &yt);

      /*retrieve the first item visible (according to the scroller pos)*/
      itemPos = 0;
      field = GetFirstField(list);
      while(field != NULL && itemPos < list->vScroll.offset) {
        field = GetNextField(field, list->bReversedSort);
        itemPos++;
      }

      /*find the item corresponding to the touchscreen y*/
      y = g_obj->rec.y;
      while(field != NULL && y + list->hItem < yt) {
        field = GetNextField(field, list->bReversedSort);
        y += list->hItem;
      }

      /*item selected != of the previous one? refresh list*/
      if(field != NULL) {
        if(list->pSelectedItem != field->pItem) {
          list->pSelectedItem = field->pItem;
          GUI_ObjSetNeedRefresh(g_obj, true);
        }
      }
      else {
        if(list->pSelectedItem != NULL) {
          list->pSelectedItem = NULL;
          GUI_ObjSetNeedRefresh(g_obj, true);
        }
      }
    }
  }
}


/**
 * @function GetList
 * @brief retrieve the pointer to the list from the generic object
 * @param void *_g_obj: generic object
 * @return list_st *: pointer to the list if success, NULL if error
 */
static list_st /*@null@*/ *GetList(g_obj_st /*@null@*/ *obj) {

  list_st *res = NULL;

  /*if null, retrieve the last added object*/
  if(obj == NULL) obj = GUI_GetLastAddedObject();

  /*make sure that the object is a list*/
  if(obj != NULL && obj->draw == ListDraw) {
    res = (list_st *) obj->obj;
  }

  return res;
}


/**
 * @function InsertInCategory
 * @brief insert a field in its corresponding category
 * @param list_st *list: pointer to the list
 * @param catId: category #id
 * @param field_st *field: field to insert
 * @return none
 */
static void InsertInCategory(list_st *list, uint8_t catId, field_st *field) {

  category_st *category = NULL;
  field_st *seek = NULL;
  bool bInserted = false;

  /* retrieve the category according to catId.
   * functions GUI_W_Listxxx ensure that (catId == 0) before (category == NULL) */
  category = list->pCategory;
  while(catId > 0) {
    category = category->next;
    catId--;
  }

  /*retrieve the first node*/
  seek = category->head;

  /*empty list? the *field becomes the head & the tail of its category*/
  if(seek == NULL) {
    category->head = field;
    category->tail = field;
  }
  /*otherwise, search its insert position*/
  else {

    while(bInserted == false) {

      /*insert: if the field's str is 'lower' than the seek's one (e.g. field->str = "a" & seek->str = "b"*/
      if(strcmp((void *)field->str, (void *)seek->str) < 0) {

        /*insert in n-1; if n-1 == NULL, *field becomes the head of its category*/
        if(seek->pVp != NULL) seek->pVp->pVn = field;
        else category->head = field;

        /*update the *field's links AND THEN the n-1 links (order matters!)*/
        field->pVp = seek->pVp;
        field->pVn = seek;
        seek->pVp = field;

        bInserted = true;
      }

      /*if the tail is reached, *field becomes the tail of its category*/
      else if(seek->pVn == NULL) {

        /*update the tail*/
        category->tail = field;

        /*update the *field's links AND THEN the n-1 links (order matters!)*/
        field->pVp = seek;
        field->pVn = seek->pVn;
        seek->pVn = field;

        bInserted = true;
      }

      /*else (*field not inserted && seek != tail), go to the next node*/
      else {
        seek = seek->pVn;
      }
    }
  }
}


/**
 * @function GetFirstField
 * @brief returns the first top field (according to selected category & sort order)
 * @param list_st *list: pointer to the list
 * @return field_st *: pointer to the top field
 */
static field_st /*@null@*/ *GetFirstField(list_st *list) {

  field_st *res = NULL;

  if(list->pSelectedCategory != NULL) {
    if(list->bReversedSort) res = list->pSelectedCategory->tail;
    else res = list->pSelectedCategory->head;
  }

  return res;
}


/**
 * @function GetNextField
 * @brief returns the next field (according to previous field & sort order)
 * @param field_st *field: previous field
 * @param bool bReversedSort: sort order (normal / reverse)
 * @return field_st *: pointer to the next field
 */
static field_st /*@null@*/ *GetNextField(field_st *field, bool bReversedSort) {

  field_st *res = NULL;

  if(bReversedSort) res = field->pVp;
  else res = field->pVn;

  return res;
}


/**
 * @function HeaderDraw
 * @brief List header draw function
 * @param void *_g_obj: pointer to the generic object of the header
 * @param void *_obj: pointer to the specific object of the header
 * @return none
 */
static void HeaderDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  list_header_st *header;
  list_st *list;
  color_t colBack, colLine, colText;
  coord_t x0, x1, y0, y1, xImg, yImg, xTxt, yTxt, xOffset;
  gui_img_t img;
  rect_st lrec;
  category_st *category;

  /*retreive generic & specific object + pointer to the associated list*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    header = (list_header_st *) _obj;
    list = GetList(header->g_obj_list);

    colBack = GetColor(G_COL_BACKGROUND);
    colLine = GetColor(G_COL_LOWER_REC);
    colText = GetColor(G_COL_TEXT);

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    SetFont(list->font);

    /*draw header background*/
    P2D_SetColor(colBack);
    (void) P2D_RectToCoord(&(g_obj->rec), &x0, &y0, &x1, &y1);
    x0++; y0++; x1--; y1--;
    (void) P2D_CoordToRect(&lrec, x0, y0, x1, y1);
    P2D_SetColor(colBack);
    P2D_FillRect(&lrec);

    /*display categories*/
    category = list->pCategory;
    P2D_SetColors(colText, colBack);
    xTxt = g_obj->rec.x - list->hScroll.offset;
    yTxt = y0 + ((y1 - y0) - list->hItem) / 2;
    xOffset = list->wSpriteMax + 4;

    while(category != NULL) {
      P2D_PutText(xTxt + xOffset, yTxt, category->name);
      xTxt += category->w;
      xOffset = 0;

      /*current category is the selected one? display the up/down sprite*/
      if(category == list->pSelectedCategory) {

        img = (list->bReversedSort == true)? G_IMG_SORT_DOWN: G_IMG_SORT_UP;
        xImg = xTxt - SpriteGetWidth(img) - 2;
        yImg = y0 + ((y1 - y0) - SpriteGetHeight(img)) / 2;

        Sprite(xImg, yImg, img);
      }

      category = category->next;
    }

    /*draw header rect*/
    P2D_SetColor(colLine);
    P2D_Rect(&(g_obj->rec));
  }
}


/**
 * @function HeaderRefresh
 * @brief List header task
 * @param void *_g_obj: pointer to the generic object of the header
 * @param void *_obj: pointer to the specific object of the header
 * @return none
 */
static void HeaderRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  list_header_st *header;
  list_st *list;
  category_st *category;
  coord_t x, xt;
  bool bRefresh = false;

  /*retreive generic & specific object + pointer to the associated list*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    header = (list_header_st *) _obj;
    list = GetList(header->g_obj_list);

    /*touchscreen?*/
    if(GUI_ObjIsPressed(g_obj)) {

      /*previous state == released?*/
      if(header->xt < 0) {

        GUI_ReadTouchScreen(&xt, NULL);
        header->xt = xt;

        /*retrieve the category corresponding to the touchscreen y*/
        category = list->pCategory;
        x = g_obj->rec.x - list->hScroll.offset;
        while(category != NULL) {

          if(xt < x + category->w) break;

          else {
            x += category->w;
            category = category->next;
          }

        }

        if(category != NULL) {

          /*touched category == previous one? reverse the sort*/
          if(list->pSelectedCategory == category) {
            list->bReversedSort = !list->bReversedSort;
            bRefresh = true;
          }
          /*else, use the touched category for sort*/
          else {
            list->pSelectedCategory = category;
            list->bReversedSort = false;
            bRefresh = true;
          }
        }

        /*important, the header shall handle the refresh of its parent list !*/
        if(bRefresh) {
          GUI_ObjSetNeedRefresh(g_obj, true);
          GUI_ObjSetNeedRefresh(header->g_obj_list, true);
        }
      }
    }
    else {
      header->xt = -1;
    }
  }
}
