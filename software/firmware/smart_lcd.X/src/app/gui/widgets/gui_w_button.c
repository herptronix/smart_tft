/**
 * @file gui_w_button.c
 * @brief basic button implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13  : initial version
 *  0.2b  2013-08-27  Add alignment & place order
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

#include "gui_w_button.h"

#define _MAX(a, b) a>b?a:b

/**
 * button
 */
typedef struct {

  uint8_t /*@null@*/ *str;  /*string associated to the button*/
  gui_img_t img;            /*image of the button*/

  /*graphic context*/
  color_t colorText;
  gui_font_t font;
  gui_align_t align;
  btn_placeOrder_e placeOrder;
} button_st;


/**
 * local variables
 */
static const length_t pitch = 2;
static btn_placeOrder_e placeOrder = G_BTN_PLACE_IMG_L_TEXT_R;


/**
 * local functions
 */
static void ButtonDraw(void *g_obj, void *obj);
static void ButtonComputeCoords(const rect_st *rec, const button_st *btn, coord_t *xTxt, coord_t *yTxt, coord_t *xImg, coord_t *yImg);

/**
 * @function GUI_W_ButtonSetPlacementOrder
 * @brief define the position of sprite & text
 * @param btn_placeOrder_e o: place order
 * @return none
 */
void GUI_W_ButtonSetPlacementOrder(btn_placeOrder_e o) {
  switch(o) {
    case G_BTN_PLACE_IMG_R_TEXT_L:
    case G_BTN_PLACE_IMG_T_TEXT_B:
    case G_BTN_PLACE_IMG_B_TEXT_T:
      placeOrder = o;
      break;

    case G_BTN_PLACE_IMG_L_TEXT_R:
    default:
      placeOrder = G_BTN_PLACE_IMG_L_TEXT_R;
      break;
  }
}

/**
 * @function GUI_W_ButtonAdd
 * @brief add a basic button
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the button (will be copied into it)
 * @param gui_img_t img: image of the button
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ButtonAdd(const rect_st *rec, const void /*@null@*/ *str, gui_img_t img) {

  g_obj_st *g_obj = NULL, *res = NULL;
  button_st *button = NULL;

  /*check parameters*/
  if(rec != NULL && rec->h > pitch * 3) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate a button*/
      button = salloc(sizeof(button_st));
      if(button != NULL) {

        /*button settings*/
        button->img = img;
        button->colorText = GetColor(G_COL_TEXT);
        button->font = GetCurrentFont();
        button->str = AllocateAndCopyStr(str);
        button->align = GUI_GetAlign();
        button->placeOrder = placeOrder;

        /*linkage between generic obj & button*/
        g_obj->rec = *rec;
        g_obj->draw = ButtonDraw;
        g_obj->task = NULL;
        g_obj->obj = button;
        GUI_ObjSetFocusable(g_obj, true); /*button is a focusable object*/
        res = g_obj;
      }
    }
  }

  return res;
}


/**
 * @function ButtonDraw
 * @brief button draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: button object
 * @return none
 */
static void ButtonDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  button_st *button;
  color_t colBack, colUpperRec, colLowerRec, colText;
  coord_t x0, y0, x1, y1, xTxt, yTxt, xImg, yImg;
  rect_st frec;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    button =  (button_st*) _obj;

    SetFont(button->font);
    ButtonComputeCoords(&(g_obj->rec), button, &xTxt, &yTxt, &xImg, &yImg);

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      SetLut(G_LUT_DISABLED);
      colBack     = GetColor(G_COL_BACKGROUND);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = GetColor(G_COL_D_TEXT);;
    }
    /*pressed object?*/
    else if(GUI_ObjIsPressed(g_obj)) {
      SetLut(G_LUT_NORMAL);
      colBack     = GetColor(G_COL_BACKGROUND);
      colUpperRec = GetColor(G_COL_LOWER_REC);
      colLowerRec = GetColor(G_COL_UPPER_REC);
      colText     = button->colorText;
      xTxt++; yTxt++; xImg++; yImg++;
    }
    /*notified object?*/
    else if(GUI_ObjIsBlink(g_obj)) {
      SetLut(G_LUT_NORMAL);
      colBack     = GetColor(G_COL_SPECIAL);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = button->colorText;
    }
    /*normal*/
    else {
      SetLut(G_LUT_NORMAL);
      colBack     = GetColor(G_COL_BACKGROUND);
      colUpperRec = GetColor(G_COL_UPPER_REC);
      colLowerRec = GetColor(G_COL_LOWER_REC);
      colText     = button->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*background*/
    P2D_FillRect(&(g_obj->rec));

    /*text*/
    if(button->str) {
      P2D_SetColor(colText);
      P2D_PutText(xTxt, yTxt, button->str);
    }

    /*sprite*/
    Sprite(xImg, yImg, button->img);

    /*upper rect*/
    (void) P2D_RectToCoord(&(g_obj->rec), &x0, &y0, &x1, &y1);
    P2D_SetColor(colUpperRec);
    P2D_Line(x0, y0, x1, y0);
    P2D_Line(x0, y0, x0, y1);

    /*lower rect*/
    P2D_SetColor(colLowerRec);
    P2D_Line(x0, y1, x1, y1);
    P2D_Line(x1, y0, x1, y1);

    /*focus*/
    if(GUI_ObjIsFocused(g_obj)) {
      x0 += 2;
      y0 += 2;
      x1 -= 2;
      y1 -= 2;
      P2D_SetColor(button->colorText);
      (void) P2D_CoordToRect(&frec, x0, y0, x1, y1);
      P2D_SetLineType(LINE_DOT);
      P2D_Rect(&frec);
    }
  }
}


/**
 * @function ButtonComputeCoords
 * @brief deduce sprite & text coords, according to placeOrder & alignment
 * @param const rect_st *rec: object dimension
 * @param const button_st *btn: button object
 * @param coord_t *xTxt, *yTxt: text coords (output)
 * @param coord_t *xImg, *yImg: sprite coords (output)
 * @return none
 */
static void ButtonComputeCoords(const rect_st *rec, const button_st *btn, coord_t *xTxt, coord_t *yTxt, coord_t *xImg, coord_t *yImg) {

  int32_t wImg, hImg, wTxt, hTxt, wTot, hTot, wObj, hObj;
  coord_t x0, y0, x1, y1;

  /*get width & length of sprite & text*/
  wImg = SpriteGetWidth(btn->img);
  hImg = SpriteGetHeight(btn->img);
  wTxt = P2D_GetTextWidth(btn->str);
  hTxt = P2D_GetTextHeight();

  /*convert obj rec into absolute coords*/
  (void) P2D_RectToCoord(rec, &x0, &y0, &x1, &y1);
  x0 += pitch;
  y0 += pitch;
  x1 -= pitch;
  y1 -= pitch;
  wObj = x1 - x0;
  hObj = y1 - y0;

  /** ----------------
   *  -     TEXT     -
   *  -     IMG      -
   *  ---------------- */
  if(btn->placeOrder == G_BTN_PLACE_IMG_B_TEXT_T) {
    wTot = _MAX(wTxt, wImg);
    hTot = hTxt + pitch + hImg;
    *xTxt = (wTot - wTxt) / 2;
    *xImg = (wTot - wImg) / 2;
    *yTxt = 0;
    *yImg = hTxt + pitch;
  }
  /** ----------------
   *  -     IMG      -
   *  -     TEXT     -
   *  ---------------- */
  else if(btn->placeOrder == G_BTN_PLACE_IMG_T_TEXT_B) {
    wTot = _MAX(wTxt, wImg);
    hTot = hTxt + pitch + hImg;
    *xTxt = (wTot - wTxt) / 2;
    *xImg = (wTot - wImg) / 2;
    *yTxt = hImg + pitch;
    *yImg = 0;

  }
  /** ----------------
   *  -  TEXT  IMG   -
   *  ---------------- */
  else if(btn->placeOrder == G_BTN_PLACE_IMG_R_TEXT_L) {
    wTot = wImg + pitch + wTxt;
    hTot = _MAX(hTxt, hImg);
    *xTxt = 0;
    *xImg = wTxt + pitch;
    *yTxt = 0;
    *yImg = 0;
  }
  /** ----------------
   *  -  IMG  TEXT   -  default
   *  ---------------- */
  else {
    wTot = wImg + pitch + wTxt;
    hTot = _MAX(hTxt, hImg);
    *xImg = 0;
    *xTxt = wImg + pitch;
    *yImg = 0;
    *yTxt = 0;
  }

  /**
   * horizontal align
   */
  if(btn->align & G_ALIGN_H_LEFT) {
    /*nothing to do*/
  }
  else if(btn->align & G_ALIGN_H_RIGHT) {
    *xTxt = *xTxt + (coord_t) (wObj - wTot);
    *xImg = *xImg + (coord_t) (wObj - wTot);
  }
  else {  /*G_ALIGN_H_CENTER or G_ALIGN_H_JUSTIFY, default*/
    *xTxt = *xTxt + (coord_t) ((wObj - wTot) / 2);
    *xImg = *xImg + (coord_t) ((wObj - wTot) / 2);
  }
  *xTxt += x0;
  *xImg += x0;

  /**
   * vertical align
   */
  if(btn->align & G_ALIGN_V_TOP) {
    /*nothing to do*/
  }
  else if(btn->align & G_ALIGN_V_BOTTOM) {
    *yTxt = *yTxt + (coord_t) (hObj - hTot);
    *yImg = *yImg + (coord_t) (hObj - hTot);
  }
  else {  /*G_ALIGN_V_CENTER, default*/
    *yTxt = *yTxt + (coord_t) ((hObj - hTot) / 2);
    *yImg = *yImg + (coord_t) ((hObj - hTot) / 2);
  }
  *yTxt += y0;
  *yImg += y0;
}
