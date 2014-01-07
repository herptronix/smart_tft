/**
 * @file gui_w_checkBox.c
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

#include "gui_w_checkBox.h"


/**
 * checkBox
 */
typedef struct {

  uint8_t /*@null@*/ *str;  /*string associated to the check box*/
  const uint8_t *pState;    /*pointer to the checkbox state*/
  uint8_t state;            /*previous checkbox state*/

  /*graphic context; each button owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} checkBox_st;


/**
 * local functions
 */
static void CheckBoxDraw(void *g_obj, void *obj);
static void CheckBoxRefresh(void *g_obj, void *obj);
static coord_t DrawBoxTicked(const rect_st *rec, uint8_t state, color_t colBoxBack, color_t colRec, color_t colText);


/**
 * @function GUI_W_CheckBoxAdd
 * @brief add a basic check box
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the checkbox (will be copied into it)
 * @param const uint8_t *pState: pointer to the state of the checkbox (*p == 0: untick, tick otherwise)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_CheckBoxAdd(const rect_st *rec, const void /*@null@*/ *str, const uint8_t *pState) {

  g_obj_st *g_obj = NULL, *res = NULL;
  checkBox_st *checkBox = NULL;

  /*check parameters*/
  if(rec != NULL && pState != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the checkBox*/
      checkBox = salloc(sizeof(checkBox_st));
      if(checkBox != NULL) {

        checkBox->colorText = GetColor(G_COL_TEXT);
        checkBox->font = GetCurrentFont();
        checkBox->str = AllocateAndCopyStr(str);
        checkBox->pState = pState;
        checkBox->state = *pState;

        /*linkage between generic obj & checkBox*/
        g_obj->rec = *rec;
        g_obj->draw = CheckBoxDraw;
        g_obj->task = CheckBoxRefresh;
        g_obj->obj = checkBox;
        GUI_ObjSetFocusable(g_obj, true); /*checkBox is a focusable object*/
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function CheckBoxRefresh
 * @brief checkBox task; force refresh if *pState has changed
 * @param void *_g_obj: generic object
 * @param void *_obj: valueBox object
 * @return none
 */
static void CheckBoxRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  checkBox_st *checkBox;

  if(_g_obj != NULL && _obj != NULL) {
    checkBox = (checkBox_st*) _obj;

    /*content of pState changed? redraw checkBox*/
    if(checkBox->state != *(checkBox->pState)) {
      checkBox->state = *(checkBox->pState);
      g_obj = (g_obj_st *) _g_obj;
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * @function CheckBoxDraw
 * @brief check box draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: valueBox object
 * @return none
 */
static void CheckBoxDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  checkBox_st *checkBox;
  color_t colBack, colBoxBack, colRec, colText;
  coord_t x, y;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    checkBox =  (checkBox_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colBack    = GetColor(G_COL_BACKGROUND);
      colBoxBack = GetColor(G_COL_BACKGROUND);
      colRec     = GetColor(G_COL_LOWER_REC);
      colText    = GetColor(G_COL_D_TEXT);
    }
    /*notified object or pressed?*/
    else if(GUI_ObjIsBlink(g_obj) || GUI_ObjIsPressed(g_obj)) {
      colBack    = GetColor(G_COL_SPECIAL);
      colBoxBack = GetColor(G_COL_E_BACKGROUND);
      colRec     = GetColor(G_COL_LOWER_REC);
      colText    = checkBox->colorText;
    }
    /*normal*/
    else {
      colBack    = GetColor(G_COL_BACKGROUND);
      colBoxBack = GetColor(G_COL_E_BACKGROUND);
      colRec     = GetColor(G_COL_LOWER_REC);
      colText    = checkBox->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*clear checkBox surface*/
    P2D_FillRect(&(g_obj->rec));

    /*draw the box (tick or untick)*/
    x = DrawBoxTicked(&(g_obj->rec), checkBox->state, colBoxBack, colRec, colText);

    /*draw text*/
    if(checkBox->str != NULL) {
      P2D_SetColor(colText);
      SetFont(checkBox->font);
      y = g_obj->rec.y + (g_obj->rec.h - P2D_GetTextHeight()) / 2;
      P2D_PutText(x, y, checkBox->str);
    }

    /*draw focus*/
    if(GUI_ObjIsFocused(g_obj)) {
      P2D_SetColor(colText);
      P2D_SetLineType(LINE_DOT);
      P2D_Rect(&(g_obj->rec));
    }
  }
}


/**
 * @function DrawBoxTicked
 * @brief draw a tick/untick box
 * @param const rect_st *rec: generic object dimension
 * @param uint8_t state: == 0: untick, tick otherwise
 * @param color_t *: colors to use
 * @return coord_t: x value which should be used to output text
 */
static coord_t DrawBoxTicked(const rect_st *rec, uint8_t state, color_t colBoxBack, color_t colRec, color_t colText) {

  coord_t x0, y0, x1, y1;
  rect_st lrec;
  const coord_t size = 11;

  /*box background*/
  lrec.x = rec->x + 2;
  lrec.y = rec->y + (rec->h - size) / 2;
  lrec.w = size;
  lrec.h = size;
  P2D_SetColor(colBoxBack);
  P2D_FillRect(&lrec);

  /*box rect*/
  P2D_SetColor(colRec);
  P2D_Rect(&lrec);

  /*box tick, if any*/
  if(state != 0) {
    (void) P2D_RectToCoord(&lrec, &x0, &y0, &x1, &y1);
    P2D_SetColor(colText);

    P2D_Line(x0 + 2, y0 + 3, x1 - 3, y1 - 2);
    P2D_Line(x0 + 2, y0 + 2, x1 - 2, y1 - 2);
    P2D_Line(x0 + 3, y0 + 2, x1 - 2, y1 - 3);

    P2D_Line(x0 + 2, y1 - 3, x1 - 3, y0 + 2);
    P2D_Line(x0 + 2, y1 - 2, x1 - 2, y0 + 2);
    P2D_Line(x0 + 3, y1 - 2, x1 - 2, y0 + 3);
  }

  /*return the x which should be used to output text*/
  return lrec.x + size + 3;
}
