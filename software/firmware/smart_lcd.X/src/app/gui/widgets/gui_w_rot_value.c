/**
 * @file gui_w_rot_value.c
 * @brief rotary value implementation (use with rot button)
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

#include "gui_w_rot_value.h"

#define MAX_VAL_STR 15  /*internal str len, for storing a sprintf(u32)*/


/**
 * rot_val_st
 */
typedef struct {
  int32_t *pVar;                /*in / out value*/
  const int8_t *pStep;          /*pointer to the increase/decrease step; assumed to be clear at the end of GUI_Draw()*/
  uint8_t /*@null@*/ *strUnit;  /*unit of the value box*/

  int32_t oldVal;               /*value of *pVar at n-1 -- for lazy refresh*/
  int32_t min, max;             /*optional min / max for *pVar*/

  uint8_t selectedDigit;        /*current selected digit (0 for the right one, n for the left one)*/
  uint8_t posDot;               /*optional dot (for fake float display)*/
  uint8_t lock;                 /*lock/unlock. If locked (> 0), *pVar will not be incremented by *pStep*/
  length_t wCar, spacing;       /*maximal length of a numeric glyph [0-9], spacing between group of 3 digits*/
  coord_t xUnit;                /*coord x where the str unit is displayed*/

  /*graphic context; each rot value owns a dedicated colorText & font -- but align is always v-center&h-right*/
  color_t colorText;
  gui_font_t font;
} rot_val_st;


/**
 * local functions
 */
static void RotValDraw(void *g_obj, void *obj);
static void RotValRefresh(void *g_obj, void *obj);
static int32_t SafeAdd(int32_t val32, int8_t inc, uint8_t digit, int32_t min, int32_t max);
static length_t GetMaxCarWidth(void);
static uint8_t GetSelectedDigit(const rot_val_st *rval, coord_t xt);
static bool IsValidDigit(const rot_val_st *rval, uint8_t digit);
static coord_t GetDigitCoord(const rot_val_st *rval, uint8_t digitId);


/**
 * @function GUI_W_RotaryValueAdd
 * @brief add a rotary value (use with rot button)
 * @param const rect_st *rec: object dimension
 * @param int32_t *pVar: pointer to the int32_t of the rot button
 * @param const int8_t *pStep: pointer to the counter step of the rot button
 * @param const void *strUnit: unit string; may be null
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_RotaryValueAdd(const rect_st *rec, int32_t *pVar, const int8_t *pStep, const void /*@null@*/ *strUnit) {

  g_obj_st *g_obj = NULL, *res = NULL;
  rot_val_st *rval = NULL;

  /*check parameters*/
  if(rec != NULL && pVar != NULL && pStep != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the rotary value box*/
      rval = salloc(sizeof(rot_val_st));
      if(rval != NULL) {

        /*allocate the string containing the unit*/
        rval->strUnit = AllocateAndCopyStr(strUnit);
        if(strUnit == NULL || rval->strUnit != NULL) {

          /*init rval*/
          rval->pVar = pVar;
          rval->pStep = pStep;
          rval->min = INT32_MIN;
          rval->max = INT32_MAX;
          rval->oldVal = *pVar;
          rval->selectedDigit = 0;
          rval->posDot = 0;
          rval->lock = 0;
          rval->wCar = GetMaxCarWidth();
          rval->spacing = P2D_GetGlyphWidth((uint8_t)'.');

          /*str unit x position*/
          rval->xUnit = rec->x + rec->w - 5;
          rval->xUnit -= P2D_GetTextWidth(rval->strUnit);

          /*context*/
          rval->colorText = GetColor(G_COL_TEXT);
          rval->font = GetCurrentFont();

          /*linkage between generic obj & rotary value box*/
          g_obj->rec = *rec;
          g_obj->draw = RotValDraw;
          g_obj->task = RotValRefresh;
          g_obj->obj = rval;
          res = g_obj;
        }
      }
    }
  }

  return res;
}


/**
 * @function GUI_W_RotaryValueLock
 * @brief lock / unlock the rotary value. If locked, increment coming from rot button will have no effect
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param bool bLock: != 0 lock the value, 0 unlock the value
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueLock(g_obj_st /*@null@*/ *obj, bool bLock) {

  int8_t res = -1;
  rot_val_st *rval = NULL;

  /*retrieve objects*/
  if(obj == NULL) obj = GUI_GetLastAddedObject();
  if(obj != NULL && obj->draw == RotValDraw) {
    rval = (rot_val_st *) obj->obj;

    /*lock / unlock*/
    if(bLock) rval->lock = 1;
    else rval->lock = 0;
    GUI_ObjSetNeedRefresh(obj, true);
    res = 0;
  }

  return res;
}


/**
 * @function GUI_W_RotaryValueSetMinMax
 * @brief set the range (min/max) of the rotary value
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param int32_t min, max: new range
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueSetMinMax(g_obj_st /*@null@*/ *obj, int32_t min, int32_t max) {

  int8_t res = -1;
  rot_val_st *rval = NULL;

  /*check parameters*/
  if(min < max) {

    /*retrieve objects*/
    if(obj == NULL) obj = GUI_GetLastAddedObject();
    if(obj != NULL && obj->draw == RotValDraw) {
      rval = (rot_val_st *) obj->obj;

      /*set new range*/
      rval->min = min;
      rval->max = max;
      rval->selectedDigit = 0;  /*always reset to 0 if new range*/
      res = 0;
    }
  }

  return res;
}


/**
 * @function GUI_W_RotaryValueSetDotPos
 * @brief set the dot position
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param uint8_t posDot: dot pos
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueSetDotPos(g_obj_st /*@null@*/ *obj, uint8_t posDot) {

  int8_t res = -1;
  rot_val_st *rval = NULL;

  /*retrieve objects*/
  if(obj == NULL) obj = GUI_GetLastAddedObject();
  if(obj != NULL && obj->draw == RotValDraw) {
    rval = (rot_val_st *) obj->obj;

    /*set new range*/
    if(IsValidDigit(rval, posDot)) {
      rval->posDot = posDot;
      res = 0;
      GUI_ObjSetNeedRefresh(obj, true);
    }
  }

  return res;
}


/**
 * @function RotValDraw
 * @brief rotary value draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: rot val object
 * @return none
 */
static void RotValDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  rot_val_st *rval;
  rect_st lrec;
  color_t colBack, colLine, colText, colSetText;
  uint8_t digitId, len, glyph, str[MAX_VAL_STR];
  bool bNeg;

  /*retrieve generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    rval = (rot_val_st*) _obj;

    /*color selection*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colBack = GetColor(G_COL_BACKGROUND);
      colLine = GetColor(G_COL_LOWER_REC);
      colText = GetColor(G_COL_D_TEXT);
      colSetText = rval->colorText;
    }
    else if(GUI_ObjIsPressed(g_obj)) {
      colBack = GetColor(G_COL_E_BACKGROUND);
      colLine = GetColor(G_COL_LOWER_REC);
      colText = rval->colorText;
      colSetText = GetColor(G_COL_SPECIAL);
    }
    else {
      colBack = GetColor(G_COL_E_BACKGROUND);
      colLine = GetColor(G_COL_LOWER_REC);
      colText = rval->colorText;
      if(rval->lock != 0) colSetText = rval->colorText;
      else colSetText = GetColor(G_COL_SPECIAL);
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    SetFont(rval->font);
    P2D_SetColors(colBack, colBack);

    /*background*/
    lrec = g_obj->rec;
    lrec.x += 1; lrec.y += 1;
    lrec.w -= 2; lrec.h -= 2;
    P2D_FillRect(&lrec);

    /*display the value's unit string*/
    P2D_SetColor(colText);
    lrec.y = g_obj->rec.y + ((coord_t)g_obj->rec.h - P2D_GetTextHeight()) / 2;
    P2D_PutText(rval->xUnit, lrec.y, rval->strUnit);

    /*format value*/
    (void) snprintf( (char *)str, MAX_VAL_STR, "%d", *(rval->pVar));
    len = gstrlen(str);
    bNeg = *(rval->pVar) < 0 ? true : false;

    /*display each digit, one by one, from right to left*/
    for(digitId = 0; IsValidDigit(rval, digitId) == true; digitId++) {

      /*get the x coord of the current digit*/
      lrec.x = GetDigitCoord(rval, digitId);

      /*special color + highlighted if the current digit is the selected one*/
      if(digitId == rval->selectedDigit && rval->lock == false) {
        P2D_SetColor(colSetText);
        lrec.h = P2D_GetTextHeight();
        lrec.w = rval->wCar;
        P2D_FillRect(&lrec);
        P2D_SetColors(colBack, colSetText);
      }
      else {
        P2D_SetColors(colText, colBack);
      }

      /*display the snprintf content, excepting the '-'*/
      if(digitId < len) {
        glyph = str[len - digitId - 1];
        if(glyph == (uint8_t)'-') glyph = (uint8_t)'0'; /*will be displayed at end*/
      }
      /*for small value (i.e. digitId >= strlen), fill with '0'*/
      else {
        glyph = (uint8_t)'0';
      }

      P2D_PutGlyph(lrec.x, lrec.y, glyph);
    }

    /*display the sign, only if negative*/
    if(bNeg) {
      P2D_SetColors(colText, colBack);
      lrec.x = GetDigitCoord(rval, digitId);
      P2D_PutGlyph(lrec.x, lrec.y, (uint8_t)'-');
    }

    /*display the dot, if any*/
    if(rval->posDot > 0) {
      P2D_SetColor(colText);
      lrec.x = GetDigitCoord(rval, rval->posDot - 1) - rval->spacing;
      P2D_SetColors(colText, colBack);
      P2D_PutGlyph(lrec.x, lrec.y, (uint8_t) '.');
    }

    /*rect*/
    P2D_SetColor(colLine);
    P2D_Rect(&(g_obj->rec));
  }
}


/**
 * @function RotValRefresh
 * @brief rotary value task
 * @param void *_g_obj: generic object
 * @param void *_obj: rot val object
 * @return none
 */
static void RotValRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  rot_val_st *rval;
  bool bRefresh = false;
  coord_t xt;
  uint8_t selectedDigit;

  /*retrieve generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    rval = (rot_val_st*) _obj;

    /*handle user interaction, only if the value is  unlocked*/
    if(rval->lock == 0) {

      /*object pressed?*/
      if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {

        /*get the digit #id corresponding to the touchscreen*/
        GUI_ReadTouchScreen(&xt, NULL);
        selectedDigit = GetSelectedDigit(rval, xt);

        /*different than the last one? -> refresh*/
        if(selectedDigit != rval->selectedDigit) {
          rval->selectedDigit = selectedDigit;
          bRefresh = true;
        }
      }
      else {
        /*add the increment/decrement to the pVar, if any*/
        *(rval->pVar) = SafeAdd( *(rval->pVar), *(rval->pStep), rval->selectedDigit, rval->min, rval->max);
      }
    }

    /*overall check (avoid UB if the user manually changes *pVar)*/
    if( *(rval->pVar) < rval->min) *(rval->pVar) = rval->min;
    else if( *(rval->pVar) > rval->max) *(rval->pVar) = rval->max;

    /*changed pVar? -> refresh*/
    if( *(rval->pVar) != rval->oldVal) {
      rval->oldVal = *(rval->pVar);
      bRefresh = true;
    }

    if(bRefresh) GUI_ObjSetNeedRefresh(g_obj, true);
  }
}


/**
 * @function SafeAdd
 * @brief safe addition (& subs), handling overflow issues
 * @param int32_t val32: initial value
 * @param int8_t inc: increment/decrement steps, coming from the rotary button
 * @param uint8_t digit: selected digit of the rot value
 * @param int32_t min, max: range of val32
 * @return int32_t: safe val32 + inc*(10^digit)
 */
static int32_t SafeAdd(int32_t val32, int8_t inc, uint8_t digit, int32_t min, int32_t max) {

  int32_t mul, res;
  int64_t val64;

  /*if there is something to add*/
  if(inc != 0) {

    /*compute the x10 multiplier, according to the selected digit*/
    mul = 1;
    while(digit > 0) {
      mul = mul * 10;
      digit--;
    }

    /*compute the v32 + mul, on 64 bits*/
    val64 = (int64_t) mul * inc;
    val64 = val64 + val32;

    /*check if the resulting value is in range*/
    if(val64 < min) res = min;
    else if(val64 > max) res = max;
    else res = (int32_t) val64;

  }
  else {
    res = val32;
  }

  return res;
}


/**
 * @function GetMaxCarWidth
 * @brief return the maximal width of glyphs in ['0'-'9'], according to the current font
 * @param none
 * @return length_t: maximal width, in pixels
 */
static length_t GetMaxCarWidth(void) {
  length_t w = 0;
  uint8_t cnt;

  for(cnt = (uint8_t)'0'; cnt <= (uint8_t)'9'; cnt++) {
    if(w < P2D_GetGlyphWidth(cnt)) w = P2D_GetGlyphWidth(cnt);
  }

  return w;
}


/**
 * @function GetSelectedDigit
 * @brief return the selected digit corresponding to the x coord coming from the touchscreen
 * @param const rot_val_st *rval: pointer to rot value object
 * @param coord_t xt: x coord coming from touchscreen
 * @return uint8_t: corresponding #id of the selected digit (ensured to be a 'valid' digit).
 */
static uint8_t GetSelectedDigit(const rot_val_st *rval, coord_t xt) {

  bool done = false;
  coord_t xDigit;
  uint8_t digit = 0;

  /*loop until the current digit coord matches with xt*/
  while(done == false) {

    xDigit = GetDigitCoord(rval, digit);

    if(xt > xDigit || IsValidDigit(rval, digit + 1) == false) done = true;
    else digit++;
  }

  return digit;
}


/**
 * @function IsValidDigit
 * @brief determine if a digit is valid according the min & max value of *pVar
 * @param const rot_val_st *rval: pointer to rot value object
 * @param uint8_t digit: between 0 & n; 0 for the right digit, n for left digit
 * @return bool: true = the given digit is contained in min/max; false otherwise
 */
static bool IsValidDigit(const rot_val_st *rval, uint8_t digit) {

  int32_t val, absMin, absMax;
  bool res = false;

  /*get abs(rval->min) & abs(rval->max)*/
  absMin = rval->min;
  if(absMin < 0) absMin = -absMin;
  absMax = rval->max;
  if(absMax < 0) absMax = -absMax;

  /*get the maximal abs which can be displayed*/
  if(absMin > absMax) val = absMin;
  else val = absMax;

  /*check if the digit #id is valid according to the maximal abs*/
  switch(digit) {
    case 0: res = true; break;
    case 1: if(val > 9ul) res = true; break;
    case 2: if(val > 99ul) res = true; break;
    case 3: if(val > 999ul) res = true; break;
    case 4: if(val > 9999ul) res = true; break;
    case 5: if(val > 99999ul) res = true; break;
    case 6: if(val > 999999ul) res = true; break;
    case 7: if(val > 9999999ul) res = true; break;
    case 8: if(val > 99999999ul) res = true; break;
    case 9: if(val > 999999999ul) res = true; break;
    /*>10, the value cannot be coded on 32 bits...*/
    default: res = false; break;
  }

  return res;
}


/**
 * @function GetDigitCoord
 * @brief compute the X coord of a given digit #id
 * @param const rot_val_st *rval: pointer to rot value object
 * @param uint8_t digitId: 0 for right digit, n for left digit
 * @return coord_t: X coord of the given digit #id
 */
static coord_t GetDigitCoord(const rot_val_st *rval, uint8_t digitId) {

  coord_t x;
  uint8_t ii;

  /*start with the #id=0 digit*/
  x = rval->xUnit - rval->wCar;
  ii = 0;

  /*loop until reaching the given digit #id*/
  while(ii < digitId) {

    ii++;
    x -= rval->wCar;

    /*extra spacing, decimal part*/
    if(ii < rval->posDot) {
      if( (rval->posDot - ii) % 3 == 0) x -= rval->spacing;
    }
    /*extra spacing, integer part*/
    else if(ii > rval->posDot){
      if( (ii - rval->posDot) % 3 == 0) x -= rval->spacing;
    }
    /*extra spacing between integer & decimal*/
    else {
      x -= rval->spacing;
    }
  }

  return x;
}
