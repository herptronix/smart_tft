/**
 * @file gui_w_tab.c
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

#include "gui_w_tab.h"


/**
 * tab
 */
typedef struct tab_t {

  uint8_t /*@null@*/ *str;   /*string associated to the button*/
  gui_img_t img;  /*image of the button*/
  uint8_t selected;

  /*graphic context; each tab owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} tab_st;


/**
 * parent_tab
 */
typedef struct {
  struct tab_t *tab;
  length_t tabHeight;
  coord_t tabPosX;
} parent_tab_st;


/**
 * local functions
 */
static void ParentTabDraw(void *g_obj, void *obj);
static void TabDraw(void *g_obj, void *obj);


/**
 * @function GUI_W_TabParentAdd
 * @brief add a tab container
 * @param const rect_st *rec: object dimension
 * @param length_t tabHeight: height of the tabs
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_TabParentAdd(const rect_st *rec, length_t tabHeight) {

  g_obj_st *g_obj = NULL, *res = NULL;
  parent_tab_st *parentTab = NULL;

  /*check parameters*/
  if(rec != NULL && rec->h > tabHeight) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the graph*/
      parentTab = salloc(sizeof(parent_tab_st));
      if(parentTab != NULL) {

        parentTab->tab = NULL;
        parentTab->tabHeight = tabHeight;
        parentTab->tabPosX = rec->x;      /*first tab will start at this coord*/

        /*linkage between generic obj & graph*/
        g_obj->rec = *rec;
        g_obj->draw = ParentTabDraw;
        g_obj->task = NULL;
        g_obj->obj = parentTab;
        GUI_ObjSetStatic(g_obj, true); /*parent tab is static: no need to refresh when pressed*/

        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function GUI_W_TabAddToParent
 * @brief add a tab into a tab container
 * @param g_obj_st *obj: pointer to the tab container
 * @param const void *str: tab string
 * @param gui_img_t img: tab image
 * @param uint8_t selected
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_TabAddToParent(g_obj_st /*@null@*/ *obj, const void /*@null@*/ *str, gui_img_t img, uint8_t selected) {

  g_obj_st *res = NULL;
  parent_tab_st *parentTab = NULL;
  tab_st *tab = NULL;
  rect_st tabRec;

  if(obj == NULL) obj = GUI_GetLastAddedObject();

  /*check parameters*/
  if(obj != NULL && obj->obj != NULL && obj->draw == ParentTabDraw) {

    parentTab = (parent_tab_st *) obj->obj;

    /*compute the tab dimension*/
    tabRec.x = parentTab->tabPosX;
    tabRec.y = obj->rec.y;
    tabRec.w = 6 + P2D_GetTextWidth(str) + SpriteGetWidth(img); /*+6: 2px for left, 2px between img & txt, 2px for right*/
    tabRec.h = parentTab->tabHeight + 1;                        /*+1: allow to overlap the upper line of the parent tab*/

    /*update the parent tabPosX, for a next tab creation*/
    parentTab->tabPosX = tabRec.x + tabRec.w + 2;

    /*check if the tab fits (even partially) in its parent; if not, /ragequit*/
    P2D_Clip(&tabRec, &obj->rec);
    if(P2D_GetPixelCnt(&tabRec) > 0) {

      /*something to display? allocate the tab*/
      tab = salloc(sizeof(tab_st));
      if(tab != NULL) {

        tab->str = AllocateAndCopyStr(str);
        tab->img = img;
        tab->selected = selected;
        tab->colorText = GetColor(G_COL_TEXT);
        tab->font = GetCurrentFont();

        /*finally, allocate & link the generic object*/
        res = GUI_AddGenericObject();
        if(res != NULL) {
          res->rec = tabRec;
          res->draw = TabDraw;
          res->task = NULL;
          res->obj = tab;
          GUI_ObjSetFocusable(res, true); /*tab is a focusable object*/
        }
      }
    }
  }

  return res;
}


/**
 * @function ParentTabDraw
 * @brief tab container draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: tab container object
 * @return none
 */
static void ParentTabDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  parent_tab_st *parentTab;
  color_t colUpperRec, colLowerRec;
  rect_st lrec;
  coord_t x0, y0, x1, y1;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    parentTab =  (parent_tab_st*) _obj;

    colUpperRec = GetColor(G_COL_UPPER_REC);
    colLowerRec = GetColor(G_COL_LOWER_REC);

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);

    (void) P2D_RectToCoord(&(g_obj->rec), &x0, &y0, &x1, &y1);
    y0 += parentTab->tabHeight;

    /*lower rect*/
    (void) P2D_CoordToRect(&lrec, x0, y0, x1, y1);
    P2D_SetColor(colLowerRec);
    P2D_Rect(&lrec);

    /*upper rect*/
    (void) P2D_CoordToRect(&lrec, x0, y0, x1 - 1, y1 - 1);
    P2D_SetColor(colUpperRec);
    P2D_Rect(&lrec);
  }
}


/**
 * @function TabDraw
 * @brief tab draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: tab object
 * @return none
 */
static void TabDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  tab_st *tab;
  color_t colBack, colUpperRec, colLowerRec, colText;
  coord_t x0, y0, x1, y1, x, y;
  rect_st lrec;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    tab =  (tab_st*) _obj;

    /*selected / unselected?*/
    colBack = GetColor(G_COL_BACKGROUND);
    lrec = g_obj->rec;
    if(tab->selected == 0) {
      lrec.y += 2;
      lrec.h -= 3;
      colBack = GetColor(G_COL_L_BACKGROUND);
    }

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      SetLut(G_LUT_DISABLED);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = GetColor(G_COL_D_TEXT);
    }
    /*notified object?*/
    else if(GUI_ObjIsBlink(g_obj)) {
      SetLut(G_LUT_NORMAL);
      colBack     = GetColor(G_COL_SPECIAL);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = tab->colorText;
    }
    /*normal*/
    else {
      SetLut(G_LUT_NORMAL);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = tab->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    if(GUI_ObjIsFocused(g_obj)) {
      P2D_SetLineType(LINE_DOT);
    }
    else {
      P2D_SetLineType(LINE_SOLID);
    }
    P2D_SetColors(colBack, colBack);

    /*background*/
    P2D_FillRect(&lrec);

    (void) P2D_RectToCoord(&lrec, &x0, &y0, &x1, &y1);

    /*sprite*/
    x = x0 + 2;
    y = (g_obj->rec.h - SpriteGetHeight(tab->img)) / 2 + y0;
    Sprite(x, y, tab->img);

    /*text*/
    if(tab->str) {
      SetFont(tab->font);
      P2D_SetColor(colText);
      x = x + SpriteGetWidth(tab->img) + 2;
      y = (g_obj->rec.h - P2D_GetTextHeight()) / 2 + y0;
      P2D_PutText(x, y, tab->str);
    }

    /*upper rect*/
    P2D_SetColor(colUpperRec);
    P2D_Line(x0, y0, x1, y0);
    P2D_Line(x0, y0, x0, y1);

    /*lower rect*/
    P2D_SetColor(colLowerRec);
    P2D_Line(x1, y0, x1, y1);
  }
}
