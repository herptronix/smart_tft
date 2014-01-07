/**
 * @file gui_w_led.c
 * @brief led implementation
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

#include "gui_w_led.h"


/**
 * led
 */
typedef struct {

  uint8_t /*@null@*/ *str;           /*string associated to the led*/
  const uint8_t *pState;  /*pointer to the led state*/
  uint8_t state;          /*previous led state*/

  /*graphic context; each led owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} led_st;


/**
 * local functions
 */
static void LedDraw(void *g_obj, void *obj);
static void LedRefresh(void *g_obj, void *obj);
static coord_t DrawLed(const rect_st *rec, color_t colLed, color_t colLine);


/**
 * @function GUI_W_LedAdd
 * @brief add a led
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the led (will be copied into it)
 * @param const uint8_t *pState: pointer to the state of the led (*p == 0: red, green otherwise)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_LedAdd(const rect_st *rec, const void /*@null@*/ *str, const uint8_t *pState) {

  g_obj_st *g_obj = NULL, *res = NULL;
  led_st *led = NULL;

  /*check parameters*/
  if(rec != NULL && pState != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the led*/
      led = salloc(sizeof(led_st));
      if(led != NULL) {

        led->colorText = GetColor(G_COL_TEXT);
        led->font = GetCurrentFont();
        led->str = AllocateAndCopyStr(str);
        led->pState = pState;
        led->state = *pState;

        /*linkage between generic obj & led*/
        g_obj->rec = *rec;
        g_obj->draw = LedDraw;
        g_obj->task = LedRefresh;
        g_obj->obj = led;
        GUI_ObjSetStatic(g_obj, true); /*led is static: no need to refresh when pressed*/
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function LedRefresh
 * @brief led task; force refresh if *pState has changed
 * @param void *_g_obj: generic object
 * @param void *_obj: led object
 * @return none
 */
static void LedRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  led_st *led;

  if(_g_obj != NULL && _obj != NULL) {
    led = (led_st*) _obj;

    /*content of pState changed? redraw led*/
    if(led->state != *(led->pState)) {
      led->state = *(led->pState);
      g_obj = (g_obj_st *) _g_obj;
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * @function LedDraw
 * @brief led draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: led object
 * @return none
 */
static void LedDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  led_st *led;
  color_t colBack, colLed, colLine, colText;
  uint8_t alpha;
  coord_t x, y;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    led =  (led_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colBack    = GetColor(G_COL_BACKGROUND);
      alpha      = 128;
      colLine    = GetColor(G_COL_LOWER_REC);
      colText    = GetColor(G_COL_D_TEXT);
    }
    /*normal*/
    else {
      colBack    = GetColor(G_COL_BACKGROUND);
      alpha      = 255;
      colLine    = GetColor(G_COL_LOWER_REC);
      colText    = led->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*clear led surface*/
    P2D_FillRect(&(g_obj->rec));

    /*draw the led (red or green)*/
    if(led->state != 0) colLed = P2D_Alpha_a_on_b(GetColor(G_COL_LED_ON) , colBack, alpha);
    else                colLed = P2D_Alpha_a_on_b(GetColor(G_COL_LED_OFF), colBack, alpha);
    x = DrawLed(&(g_obj->rec), colLed, colLine);

    /*draw text*/
    if(led->str != NULL) {
      P2D_SetColor(colText);
      SetFont(led->font);
      y = g_obj->rec.y + (g_obj->rec.h - P2D_GetTextHeight()) / 2;
      P2D_PutText(x, y, led->str);
    }
  }
}


/**
 * @function DrawLed
 * @brief draw a led
 * @param const rect_st *rec: generic object dimension
 * @param color_t colLed: color of the led
 * @param color_t colLine: color of the led's extern circle
 * @return coord_t: x value which should be used to output text
 */
static coord_t DrawLed(const rect_st *rec, color_t colLed, color_t colLine) {

  coord_t x0, y0;
  const coord_t radius = 6;

  /*led content*/
  x0 = rec->x + radius + 2;
  y0 = rec->y + rec->h / 2;
  P2D_SetColor(colLed);
  P2D_FillCircle(x0, y0, radius);

  /*led circle*/
  P2D_SetColor(colLine);
  P2D_Circle(x0, y0, radius);

  /*return the x which should be used to output text*/
  return x0 + radius + 3;
}
