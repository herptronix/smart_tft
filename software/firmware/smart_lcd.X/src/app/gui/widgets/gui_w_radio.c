/**
 * @file gui_w_radio.c
 * @brief radio implementation
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

#include "gui_w_radio.h"


/**
 * radio
 */
typedef struct {

  uint8_t /*@null@*/ *str;    /*string associated to the check box*/
  const uint8_t *pCurrentId;  /*pointer to the radio id*/
  uint8_t id;                 /*radio id*/
  uint8_t state;              /*tick / untick*/

  /*graphic context; each led owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} radio_st;


/**
 * local functions
 */
static void RadioDraw(void *g_obj, void *obj);
static void RadioRefresh(void *g_obj, void *obj);
static coord_t DrawRadioImg(const rect_st *rec, uint8_t state, color_t colRadioBack, color_t colLine, color_t colText);


/**
 * @function GUI_W_RadioAdd
 * @brief add a radio
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the checkbox (will be copied into it)
 * @param const uint8_t *pCurrentId: pointer to current id of the selected radio
 * @param uint8_t id: id of the radio
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_RadioAdd(const rect_st *rec, const void /*@null@*/ *str, const uint8_t *pCurrentId, uint8_t id) {

  g_obj_st *g_obj = NULL, *res = NULL;
  radio_st *radio = NULL;

  /*check parameters*/
  if(rec != NULL && pCurrentId != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the radio*/
      radio = salloc(sizeof(radio_st));
      if(radio != NULL) {

        radio->colorText = GetColor(G_COL_TEXT);
        radio->font = GetCurrentFont();
        radio->str = AllocateAndCopyStr(str);
        radio->pCurrentId = pCurrentId;
        radio->id = id;
        radio->state = *pCurrentId == id? 1: 0;

        /*linkage between generic obj & radio*/
        g_obj->rec = *rec;
        g_obj->draw = RadioDraw;
        g_obj->task = RadioRefresh;
        g_obj->obj = radio;
        GUI_ObjSetFocusable(g_obj, true); /*radio is a focusable object*/
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function RadioRefresh
 * @brief radio task; force refresh if radio state is not coherent with the current selected id
 * @param void *_g_obj: generic object
 * @param void *_obj: radio object
 * @return none
 */
static void RadioRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  radio_st *radio;
  bool bRefresh = false;

  if(_g_obj != NULL && _obj != NULL) {
    radio = (radio_st*) _obj;

    /*radio id == selected id && state == untick: -> state = tick, force refresh*/
    if(radio->state == 0 && radio->id == *(radio->pCurrentId)) {
      radio->state = 1;
      bRefresh = true;
    }
    /*radio id != selected id && state == tick: -> state = untick, force refresh*/
    else if(radio->state != 0 && radio->id != *(radio->pCurrentId)) {
      radio->state = 0;
      bRefresh = true;
    }

    if(bRefresh) {
      g_obj = (g_obj_st *) _g_obj;
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * @function RadioDraw
 * @brief radio draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: radio object
 * @return none
 */
static void RadioDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  radio_st *radio;
  color_t colBack, colRadioBack, colLine, colText;
  coord_t x, y;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    radio =  (radio_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colBack      = GetColor(G_COL_BACKGROUND);
      colRadioBack = GetColor(G_COL_BACKGROUND);
      colLine      = GetColor(G_COL_LOWER_REC);
      colText      = GetColor(G_COL_D_TEXT);
    }
    /*notified object or pressed?*/
    else if(GUI_ObjIsBlink(g_obj) || GUI_ObjIsPressed(g_obj)) {
      colBack      = GetColor(G_COL_SPECIAL);
      colRadioBack = GetColor(G_COL_E_BACKGROUND);
      colLine      = GetColor(G_COL_LOWER_REC);
      colText      = radio->colorText;
    }
    /*normal*/
    else {
      colBack      = GetColor(G_COL_BACKGROUND);
      colRadioBack = GetColor(G_COL_E_BACKGROUND);
      colLine      = GetColor(G_COL_LOWER_REC);
      colText      = radio->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*clear radio surface*/
    P2D_FillRect(&(g_obj->rec));

    /*draw the radio (tick or untick)*/
    x = DrawRadioImg(&(g_obj->rec), radio->state, colRadioBack, colLine, colText);

    /*draw text*/
    if(radio->str != NULL) {
      P2D_SetColor(colText);
      SetFont(radio->font);
      y = g_obj->rec.y + (g_obj->rec.h - P2D_GetTextHeight()) / 2;
      P2D_PutText(x, y, radio->str);
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
 * @function DrawRadioImg
 * @brief draw a tick/untick radio
 * @param const rect_st *rec: generic object dimension
 * @param uint8_t state: == 0: untick, tick otherwise
 * @param color_t *: colors to use
 * @return coord_t: x value which should be used to output text
 */
static coord_t DrawRadioImg(const rect_st *rec, uint8_t state, color_t colRadioBack, color_t colLine, color_t colText) {

  coord_t x0, y0;
  color_t caa;
  const coord_t radius = 6;

  /*radio background*/
  x0 = rec->x + radius + 2;
  y0 = rec->y + rec->h / 2;
  P2D_SetColor(colRadioBack);
  P2D_FillCircle(x0, y0, radius);

  /*radio circle*/
  P2D_SetColor(colLine);
  P2D_Circle(x0, y0, radius);

  /*radio tick, if any*/
  if(state != 0) {

    caa = P2D_Alpha_a_on_b(colText, colRadioBack, 128);
    P2D_SetColor(caa);
    P2D_FillCircle(x0, y0, radius - 3);

    P2D_SetColor(colText);
    P2D_FillCircle(x0, y0, radius - 4);
  }

  /*return the x which should be used to output text*/
  return x0 + radius + 3;
}
