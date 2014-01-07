/**
 * @file gui_w_rot_button.c
 * @brief rotary button implementation
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-09-15  : initial version
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

#include "gui_w_rot_button.h"


/**
 * rot_btn_st
 */
typedef struct {

  int8_t *pVar;         /*pointer to the output var*/
  int16_t deg;          /*current angle, in degrees*/
  uint8_t step;         /*angle increase, in degree (shall ensure that 90 % step == 0)*/
  coord_t xc, yc, rad;  /*center, radius*/

  /* n-1 state; allow to set the round ticks on the touched point coordinates without
   * modifying pVar (avoid a unwanted increment when pressed for the first time)*/
  bool bWasPressed;
} rot_btn_st;

/**
 * local variables
 */
static const length_t min_w = 30; /*minimal length of a rotary button*/

/**
 * local functions
 */
static void RotBtnDraw(void *g_obj, void *obj);
static void RotBtnRefresh(void *g_obj, void *obj);
static int16_t GetAngle(coord_t xc, coord_t yc, coord_t xt, coord_t yt, uint8_t step);
static int8_t GetInc(int16_t old, int16_t new, uint8_t step);


/**
 * @function GUI_W_RotaryButtonAdd
 * @brief add a rotary button (~rotary encoder)
 * @param const rect_st *rec: object dimension (must be square !)
 * @param int8_t *pVar: pointer to the int8 which will recieve the increment/decrement
 * @param gr_enum_e granularity: rotation steps, in degrees. see gr_enum_e
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_RotaryButtonAdd(const rect_st *rec, int8_t *pVar, gr_enum_e granularity) {

  g_obj_st *g_obj = NULL, *res = NULL;
  rot_btn_st *rbtn = NULL;

  /*check parameters*/
  if(rec != NULL && rec->w == rec->h && rec->w >= min_w && pVar != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the rotary button*/
      rbtn = salloc(sizeof(rot_btn_st));
      if(rbtn != NULL) {

        rbtn->deg = 90;
        rbtn->pVar = pVar;
        rbtn->bWasPressed = false;

        /*set angle step*/
        switch(granularity) {
          case ROTARY_BTN_GR_5_DEG : rbtn->step = 5 ; break;
          case ROTARY_BTN_GR_10_DEG: rbtn->step = 10; break;
          case ROTARY_BTN_GR_15_DEG: rbtn->step = 15; break;
          case ROTARY_BTN_GR_30_DEG:
          default:                   rbtn->step = 30; break;
        }

        /*compute coords*/
        rbtn->rad = rec->w / 2 - 1;
        rbtn->xc = rec->x + rbtn->rad;
        rbtn->yc = rec->y + rbtn->rad;

        /*linkage between generic obj & rotary button*/
        g_obj->rec = *rec;
        g_obj->draw = RotBtnDraw;
        g_obj->task = RotBtnRefresh;
        g_obj->obj = rbtn;
        res = g_obj;
      }
    }
  }
  return res;
}


/**
 * @function RotBtnRefresh
 * @brief rot_btn refresh function
 * @param void *_g_obj: generic object
 * @param void *_obj: rot_btn object
 * @return none
 */
static void RotBtnRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  rot_btn_st *rbtn;
  coord_t xt, yt;
  int16_t deg;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    rbtn = (rot_btn_st*) _obj;

    /*angle & increment shall be updated if object pressed & object enabled*/
    if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {

      /*compute the angle corresponding to the point touched and the granularity*/
      GUI_ReadTouchScreen(&xt, &yt);
      deg = GetAngle(rbtn->xc, rbtn->yc, xt, yt, rbtn->step);

      if(rbtn->deg != deg) {

        /*compute the increment/decrement according to old & new angle*/
        if(rbtn->bWasPressed) *(rbtn->pVar) = GetInc(rbtn->deg, deg, rbtn->step);

        /*save the new angle*/
        rbtn->deg = deg;
        GUI_ObjSetNeedRefresh(g_obj, true);
      }
      else {
        *(rbtn->pVar) = 0;
      }

      rbtn->bWasPressed = true;
    }
    /*no activity? clear the increment*/
    else {
      *(rbtn->pVar) = 0;
      rbtn->bWasPressed = false;
    }
  }
}


/**
 * @function RotBtnDraw
 * @brief rot_btn draw function TODO: another draw function; this widget is ugliest one ><"
 * @param void *_g_obj: generic object
 * @param void *_obj: rot_btn object
 * @return none
 */
static void RotBtnDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  rot_btn_st *rbtn;
  color_t colBack, colLine, colTick;
  int32_t x, y;
  coord_t tPos, tRadius;

  const uint16_t divider = 32767;  /* P2D_Cos / P2D_Sin return a value between -32767 & 32767*/
  const uint16_t rTot = 20;
  const uint16_t rPos = 14;
  const uint16_t rRad = 3;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    rbtn =  (rot_btn_st*) _obj;

    colBack = P2D_Color(180, 180, 180); //GetColor(G_COL_BACKGROUND);
    colLine = GetColor(G_COL_LOWER_REC);
    if(GUI_ObjIsDisabled(g_obj)) {
      colTick = GetColor(G_COL_BACKGROUND);
    }
    else if(GUI_ObjIsPressed(g_obj)) {
      colTick = GetColor(G_COL_SPECIAL);
    }
    else {
      colTick = GetColor(G_COL_E_BACKGROUND);
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);

    /*draw the button*/
    P2D_SetColor(colBack);
    P2D_FillCircle(rbtn->xc, rbtn->yc, rbtn->rad);
    P2D_SetColor(colLine);
    P2D_Circle(rbtn->xc, rbtn->yc, rbtn->rad);
    P2D_Circle(rbtn->xc, rbtn->yc, rbtn->rad-1);


    /*compute the round tick position*/
    tPos = rbtn->rad * rPos / rTot;
    tRadius = rbtn->rad * rRad / rTot;
    y = tPos * P2D_Sin(rbtn->deg);
    y /= divider;
    y = rbtn->yc - y;
    x = tPos * P2D_Cos(rbtn->deg);
    x /= divider;
    x += rbtn->xc;

    /*draw the round tick*/
    P2D_SetColor(colTick);
    P2D_FillCircle(x, y, tRadius);
    P2D_SetColor(colLine);
    P2D_Circle(x, y, tRadius);
  }
}


/**
 * @function GetAngle
 * @brief return the angle corresponding to the touched point
 * @param coord_t xc, coord_t yc: center of rot_btn
 * @param coord_t xt, coord_t yt: touched point
 * @param uint8_t step: angle will be %step
 * @return int16_t: angle in degrees E[0-360]
 */
static int16_t GetAngle(coord_t xc, coord_t yc, coord_t xt, coord_t yt, uint8_t step) {

  int16_t angle = 0;
  int32_t o, a, h, tmp;
  const uint16_t multiplier = 32767;  /* P2D_Cos / P2D_Sin return a value between -32767 & 32767*/

  /*compute adjacent, opposite & hypotenuse*/
  a = xt - xc;
  o = yc - yt;
  h = (int32_t) a * a + (int32_t) o * o;
  h = P2D_sqrt(h);

  if(h > 0) {

    if(P2D_Abs(o) <= P2D_Abs(a)) {
      tmp = (int32_t)P2D_Abs(o) * multiplier / h;
      for(angle = 0; angle <= 90; angle += step) {
        if(tmp <= P2D_Sin(angle) || tmp < P2D_Sin(angle + step/2)) break;
      }
    }
    else {
      tmp = (int32_t)P2D_Abs(a) * multiplier / h;
      for(angle = 90; angle >= 0; angle -= step) {
        if(tmp <= P2D_Cos(angle) || tmp < P2D_Cos(angle - step/2)) break;
      }
    }

    /*update angle, according quadrant location*/
    if(a <= 0) {
      if(o >= 0) angle = 90 + (90 - angle); /*top left quadrant*/
      else if(o < 0) angle = angle + 180;   /*bottom left quadrant*/
    }
    else if(a > 0) {
      if(o < 0) angle = 270 + (90 - angle); /*bottom right quadrant*/
      else {/*nothing*/}                    /*top right quadrant*/
    }
    if(angle == 360) angle = 0;
  }

  return angle;
}


/**
 * @function GetInc
 * @brief return number of step corresponding between the old angle & the new one
 * @param int16_t oldAngle: old angle, in degrees
 * @param int16_t newAngle: new angle, in degrees
 * @param uint8_t step: degrees between steps
 * @return int8_t: steps count (0 if unchanged, positive or negative otherwise)
 */
static int8_t GetInc(int16_t oldAngle, int16_t newAngle, uint8_t step) {

  bool done;
  int8_t res, inc, dec;
  int16_t angleInc, angleDec;

  angleInc = angleDec = oldAngle;
  res = inc = dec = 0;
  done = false;

  /*find the shortest way to reach the new angle*/
  while(done == false) {

    /*shortest way is by incrementation? return inc value*/
    if(angleInc == newAngle) {
      done = true;
      res = inc;
    }
    /*shortest way is by decrementation? return dec value*/
    else if(angleDec == newAngle) {
      done = true;
      res = dec;
    }
    /*else, new angle is not yet reached*/
    else {

      inc++;
      angleInc -= step;
      if(angleInc < 0) angleInc = 360 - step;

      dec--;
      angleDec += step;
      if(angleDec >= 360) angleDec = 0;
    }
  }

  return res;
}
