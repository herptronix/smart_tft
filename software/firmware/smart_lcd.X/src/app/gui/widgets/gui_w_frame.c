/**
 * @file gui_w_frame.c
 * @brief frame implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13  : initial version
 *  0.2b  2013-08-27  : Add alignment
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

#include "gui_w_frame.h"


/**
 * frame
 */
typedef struct {

  uint8_t /*@null@*/ *str;           /*string associated to the frame*/

  /*graphic context; each frame owns a dedicated colorText & font*/
  gui_align_t align;
  color_t colorText;
  gui_font_t font;
} frame_st;


/**
 * local functions
 */
static void FrameDraw(void *g_obj, void *obj);


/**
 * @function GUI_W_FrameAdd
 * @brief add a frame
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the frame (will be copied into it)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_FrameAdd(const rect_st *rec, const void /*@null@*/ *str) {

  g_obj_st *g_obj = NULL, *res = NULL;
  frame_st *frame = NULL;

  /*check parameters*/
  if(rec != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the frame*/
      frame = salloc(sizeof(frame_st));
      if(frame != NULL) {

        frame->colorText = GetColor(G_COL_TEXT);
        frame->font = GetCurrentFont();
        frame->str = AllocateAndCopyStr(str);
        frame->align = GUI_GetAlign();

        /*linkage between generic obj & frame*/
        g_obj->rec = *rec;
        g_obj->draw = FrameDraw;
        g_obj->task = NULL;
        g_obj->obj = frame;
        GUI_ObjSetStatic(g_obj, true); /*frame is static: no need to refresh when pressed*/
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function FrameDraw
 * @brief frame draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: frame object
 * @return none
 */
static void FrameDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  frame_st *frame;
  color_t colBack, colUpperRec, colLowerRec, colText;
  rect_st lrec;
  coord_t x0, y0, x1, y1, x;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    frame =  (frame_st*) _obj;

    colBack     = GetColor(G_COL_BACKGROUND);
    colUpperRec = GetColor(G_COL_UPPER_REC);
    colLowerRec = GetColor(G_COL_LOWER_REC);

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colText    = GetColor(G_COL_D_TEXT);
    }
    /*normal*/
    else {
      colText    = frame->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    SetFont(frame->font);

    /*upper rect*/
    (void) P2D_RectToCoord(&(g_obj->rec), &x0, &y0, &x1, &y1);
    y0 += (P2D_GetTextHeight() / 2);
    (void) P2D_CoordToRect(&lrec, x0, y0, x1 - 1, y1 - 1);
    P2D_SetColor(colUpperRec);
    P2D_Rect(&lrec);

    /*lower rect*/
    (void) P2D_CoordToRect(&lrec, x0 + 1, y0 + 1, x1, y1);
    P2D_SetColor(colLowerRec);
    P2D_Rect(&lrec);

    /*text*/
    if(frame->str != NULL) {

      if(frame->align & G_ALIGN_H_RIGHT) {
        x = g_obj->rec.x + ( (coord_t)g_obj->rec.w - P2D_GetTextWidth(frame->str)) - 5;
      }
      else if(frame->align & G_ALIGN_H_CENTER) {
        x = g_obj->rec.x + ( (coord_t)g_obj->rec.w - P2D_GetTextWidth(frame->str)) / 2;
      }
      else {
        x = g_obj->rec.x + 5;
      }

      P2D_SetColors(colText, colBack);
      P2D_PutText(x, g_obj->rec.y, frame->str);
    }
  }
}
