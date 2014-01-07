/**
 * @file gui_w_slider.c
 * @brief slider implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13  : initial version
 *  0.2b  2013-08-27  : Add orientation (vertical / horizontal)
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

#include "gui_w_slider.h"


/**
 * slider
 */
typedef struct {
  uint8_t *pValue;        /*pointer to the slider value*/
  uint8_t value;          /*previous slider value*/
} slider_st;


/**
 * local functions
 */
static void SliderDraw(void *g_obj, void *obj);
static void SliderRefresh(void *g_obj, void *obj);
static bool IsVertical(const rect_st *rec);


/**
 * @function GUI_W_SliderAdd
 * @brief add a slider
 * @param const rect_st *rec: object dimension
 * @param uint8_t *pValue: pointer to the value of the slider (range[0-255])
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_SliderAdd(const rect_st *rec, uint8_t *pValue) {

  g_obj_st *g_obj = NULL, *res = NULL;
  slider_st *slider = NULL;

  /*check parameters*/
  if(rec != NULL && pValue != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the slider*/
      slider = salloc(sizeof(slider_st));
      if(slider != NULL) {
        slider->pValue = pValue;
        slider->value = *pValue;

        /*linkage between generic obj & slider*/
        g_obj->rec = *rec;
        g_obj->draw = SliderDraw;
        g_obj->task = SliderRefresh;
        g_obj->obj = slider;
        GUI_ObjSetFocusable(g_obj, true); /*slider is a focusable object*/
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function SliderRefresh
 * @brief slider task; force refresh if *pValue has changed
 * @param void *_g_obj: generic object
 * @param void *_obj: slider object
 * @return none
 */
static void SliderRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  slider_st *slider;
  coord_t xt, yt;
  int32_t i32;

  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    slider = (slider_st*) _obj;

    if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {

      /*at this point, xt is included in the object clip*/
      GUI_ReadTouchScreen(&xt, &yt);

      if(IsVertical(&g_obj->rec) == false) {
        i32 = ((int32_t)xt - (g_obj->rec.x + 1)) * 255;
        i32 = i32 / (g_obj->rec.w - 2);
      }
      else {
        i32 = ((int32_t)g_obj->rec.h - (yt - g_obj->rec.y)) * 255;
        i32 = i32 / (g_obj->rec.h - 2);
      }


      if(i32 > 255) i32 = 255;
      else if(i32 < 0) i32 = 0;

      *(slider->pValue) = (uint8_t) i32;
    }

    /*content of pState changed? redraw slider*/
    if(slider->value != *(slider->pValue)) {
      slider->value = *(slider->pValue);
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * @function SliderDraw
 * @brief slider draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: slider object
 * @return none
 */
static void SliderDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  slider_st *slider;
  color_t colLine, colFill, colEmpty;
  int32_t i32;
  rect_st lrec;
  coord_t x0, x1, y0, y1, yL, xL;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    slider =  (slider_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colLine   = GetColor(G_COL_LOWER_REC);
      colEmpty  = GetColor(G_COL_E_BACKGROUND);
      colFill   = GetColor(G_COL_LOWER_REC);
    }
    /*normal*/
    else {
      colLine   = GetColor(G_COL_LOWER_REC);
      colEmpty  = GetColor(G_COL_E_BACKGROUND);
      colFill   = GetColor(G_COL_SPECIAL);
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    if(GUI_ObjIsFocused(g_obj)) {
      P2D_SetLineType(LINE_DOT);
      P2D_SetColors(GetColor(G_COL_BACKGROUND), GetColor(G_COL_BACKGROUND));
    }
    else {
      P2D_SetLineType(LINE_SOLID);
    }

    (void) P2D_RectToCoord(&(g_obj->rec), &x0, &y0, &x1, &y1);
    x0++;
    x1--;
    y0++;
    y1--;

    if(IsVertical(&g_obj->rec) == false) {

      i32 = (((uint32_t)g_obj->rec.w - 2) * slider->value) / 255 + x0;
      xL = (coord_t) i32;

      /*filled rect*/
      (void) P2D_CoordToRect(&lrec, x0, y0, xL, y1);
      P2D_SetColor(colFill);
      P2D_FillRect(&lrec);

      /*filled rect*/
      if(xL < x1) {
        (void) P2D_CoordToRect(&lrec, xL, y0, x1, y1);
        P2D_SetColor(colEmpty);
        P2D_FillRect(&lrec);
      }
    }
    else {

      i32 = (((uint32_t)g_obj->rec.h - 2) * slider->value) / 255;
      yL = y1 - (coord_t) i32;

      /*filled rect*/
      (void) P2D_CoordToRect(&lrec, x0, yL, x1, y1);
      P2D_SetColor(colFill);
      P2D_FillRect(&lrec);

      /*filled rect*/
      if(yL > y0) {
        (void) P2D_CoordToRect(&lrec, x0, y0, x1, yL);
        P2D_SetColor(colEmpty);
        P2D_FillRect(&lrec);
      }
    }

    /*rec*/
    P2D_SetColor(colLine);
    P2D_Rect(&(g_obj->rec));
  }
}


/**
 * @function IsVertical
 * @brief return true if the slider is a vertical one
 * @param const rect_st *rec: slider's rect
 * @return bool true: vertical, horizontal otherwise
 */
static bool IsVertical(const rect_st *rec) {
  bool res = false;
  if(rec->w < rec->h) res = true;
  return res;
}
