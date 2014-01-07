/**
 * @file gui_w_valueBox.c
 * @brief value box implementation
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

#include "gui_w_valueBox.h"

/**
 * specific typed box storage
 */
typedef struct {const int8_t   *pVar; int8_t   val;} box_int8_st;
typedef struct {const int16_t  *pVar; int16_t  val;} box_int16_st;
typedef struct {const int32_t  *pVar; int32_t  val;} box_int32_st;
typedef struct {const uint8_t  *pVar; uint8_t  val;} box_uint8_st;
typedef struct {const uint16_t *pVar; uint16_t val;} box_uint16_st;
typedef struct {const uint32_t *pVar; uint32_t val;} box_uint32_st;
typedef struct {const float    *pVar; float    val;} box_float_st;

/**
 * generic box
 */
typedef struct {

  void *gVal;           /*generic value; can be box_uint8_st, box_int16_st, ...*/
  valueBoxType_e type;  /*type of the generic value*/
  char *format;         /*format string; will be used by snprintf()*/

  /*graphic context; each valueBox owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} valueBox_st;


/**
 * local functions
 */
static void /*@null@*/ *AllocateGenericValue(const void *pValue, valueBoxType_e type);
static bool RefreshGenericValue(void *pGenericValue, const void /*@null@*/ *pValue, valueBoxType_e type);
static void ValueBoxDraw(void *g_obj, void *obj);
static void ValueBoxTask(void *g_obj, void *obj);
static void snprintGenericValue(char /*@out@*/ *str, uint8_t size, const void *gVal, valueBoxType_e type, const char *format);


/**
 * @function GUI_W_ValueBoxAdd
 * @brief add a value box
 * @param const rect_st *rec: object dimension
 * @param const void *pVar: pointer to the variable to associate to the valueBox
 * @param valueBoxType_e type: type (uint8_t, int16_t, ...) of the variable
 * @param const char *format: string format, will be used by snprintf()
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ValueBoxAdd(const rect_st *rec, const void *pVar, valueBoxType_e type, const char *format) {

  g_obj_st *g_obj = NULL, *res = NULL;
  valueBox_st *valueBox = NULL;
  void *gVal = NULL;

  /*check input parameters*/
  if(rec != NULL && pVar != NULL && format != NULL) {

    /*allocate memory for generic value storage; also check <pVar> alignment according to <type>*/
    gVal = AllocateGenericValue(pVar, type);

    /*if alignment OK and allocated memory OK*/
    if(gVal != NULL) {

      /*copy <pVar> into its dedicated struct*/
      (void) RefreshGenericValue(gVal, pVar, type);

      /*then allocate a valueBox*/
      valueBox = salloc(sizeof(valueBox_st));
      if(valueBox != NULL) {
        valueBox->colorText = GetColor(G_COL_TEXT);
        valueBox->font = GetCurrentFont();
        valueBox->type = type;
        valueBox->gVal = gVal;
        valueBox->format = AllocateAndCopyStr(format);

        /*finally, allocate & link the generic object*/
        g_obj = GUI_AddGenericObject();
        if(g_obj != NULL) {
          g_obj->rec = *rec;
          g_obj->draw = ValueBoxDraw;
          g_obj->task = ValueBoxTask;
          g_obj->obj = valueBox;
          GUI_ObjSetStatic(g_obj, true); /*valueBox is static: no need to refresh when pressed*/
          res = g_obj;
        }
      }
    }
  }

  return res;
}


/**
 * @function ValueBoxTask
 * @brief valueBox task; force refresh if the value content has changed
 * @param void *_g_obj: generic object
 * @param void *_obj: valueBox object
 * @return none
 */
static void ValueBoxTask(void *_g_obj, void *_obj) {

  g_obj_st *g_obj = NULL;
  valueBox_st *valueBox = NULL;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    valueBox =  (valueBox_st*) _obj;

    /*compare the current value to the old one; if different, need to refresh the valueBox*/
    if(RefreshGenericValue(valueBox->gVal, NULL, valueBox->type) == true) {
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * @function ValueBoxDraw
 * @brief valueBox draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: valueBox object
 * @return none
 */
static void ValueBoxDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  valueBox_st *box;
  color_t colBack, colRec, colText;
  rect_st lrec;
  coord_t x, y;
  #define MAX_STR_VALUE 30
  char str[MAX_STR_VALUE];

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    box =  (valueBox_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colBack = GetColor(G_COL_BACKGROUND);
      colRec  = GetColor(G_COL_LOWER_REC);
      colText = GetColor(G_COL_D_TEXT);
    }
    /*notified object?*/
    else if(GUI_ObjIsBlink(g_obj)) {
      colBack = GetColor(G_COL_SPECIAL);
      colRec  = GetColor(G_COL_LOWER_REC);
      colText = box->colorText;
    }
    /*normal*/
    else {
      colBack = GetColor(G_COL_E_BACKGROUND);
      colRec  = GetColor(G_COL_LOWER_REC);
      colText = box->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*background*/
    lrec = g_obj->rec;
    lrec.x++; lrec.y++; lrec.w -= 2; lrec.h -= 2;
    P2D_FillRect(&lrec);

    /*text*/
    SetFont(box->font);
    P2D_SetColor(colText);
    snprintGenericValue(str, MAX_STR_VALUE, box->gVal, box->type, box->format);
    x = g_obj->rec.x + (g_obj->rec.w - P2D_GetTextWidth(str)) / 2;
    y = g_obj->rec.y + (g_obj->rec.h - P2D_GetTextHeight()) / 2;
    P2D_PutText(x, y, str);

    /*rect*/
    P2D_SetColor(colRec);
    P2D_Rect(&(g_obj->rec));
  }
}


/**
 * @function AllocateGenericValue
 * @brief allocate memory for a specific typed storage and initialize it
 * @param void *pVar: pointer to the physical value to associate with the valueBox
 * @param valueBoxType_e type: storage type
 * @return void *: address of the allocated storage if success, null otherwise (lack of memory or type/alignement issue)
 */
static void /*@null@*/ *AllocateGenericValue(const void *pVar, valueBoxType_e type) {

  uint8_t size, align;
  uint32_t address;
  void *res = NULL;

  /*compute the bytes needed to store the matching gVal struct*/
  switch(type) {
    case BOX_T_INT8  : size = sizeof(box_int8_st  ); align = 1; break;
    case BOX_T_UINT8 : size = sizeof(box_uint8_st ); align = 1; break;
    case BOX_T_INT16 : size = sizeof(box_int16_st ); align = 2; break;
    case BOX_T_UINT16: size = sizeof(box_uint16_st); align = 2; break;
    case BOX_T_INT32 : size = sizeof(box_int32_st ); align = 4; break;
    case BOX_T_UINT32: size = sizeof(box_uint32_st); align = 4; break;
    case BOX_T_FLOAT : size = sizeof(box_float_st ); align = 4; break;
    default: size = 0; align = 1; break;
  }

  /*if there is something to allocate (i.e. a correct valueBoxType_e) */
  if(size > 0) {

    /*check if the user pointer is compatible with the desired type*/
    address = (uint32_t) pVar;
    if(address % align == 0) {

      /*then, allocate & clear*/
      res = salloc(size);
      if(res != NULL) {
        gmemset(res, 0, size);
      }
    }
  }

  return res;
}


/**
 * @function Refresh xxx
 * @brief check if the value associated to the valueBox has changed
 * @param box_xxx_st *gVal: pointer to a typed value storage
 * @param const xxx *pVar: if non null, will be written in the typed value storage
 * @return bool: false if no change, true if changed; if true, the valueBox has to be refreshed
 *
 * Duplicated code to ensure correct type consideration (unlike the 'void* everywhere' method, which makes gcc/splint yelling)
 */
static bool RefreshInt8(box_int8_st *gVal, const int8_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshUint8(box_uint8_st *gVal, const uint8_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshInt16(box_int16_st *gVal, const int16_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshUint16(box_uint16_st *gVal, const uint16_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshInt32(box_int32_st *gVal, const int32_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshUint32(box_uint32_st *gVal, const uint32_t /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && *(gVal->pVar) != gVal->val) {
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}
static bool RefreshFloat(box_float_st *gVal, const float /*@null@*/ *pVar) {
  bool bRefresh = false;
  if(pVar != NULL) gVal->pVar = pVar;
  if(gVal->pVar != NULL && ismemdiff(gVal->pVar, &(gVal->val), sizeof(float)) ) { /*pls never use != or == with float*/
    gVal->val = *(gVal->pVar);
    bRefresh = true;
  }
  return bRefresh;
}


/**
 * @function RefreshGenericValue
 * @brief check if the value associated to the valueBox has changed (dispatch to the above functions)
 * @param void *gVal: pointer to a typed value storage
 * @param void *pVar: if non null, will be written in the typed value storage
 * @param valueBoxType_e type: type of the storage
 * @return bool: false if no change, true if changed; if true, the valueBox has to be refreshed
 */
static bool RefreshGenericValue(void *gVal, const void /*@null@*/ *pVar, valueBoxType_e type) {

  bool bRefresh = false;

  if(gVal != NULL) {
    switch(type) {
      case BOX_T_INT8:   bRefresh = RefreshInt8  ((box_int8_st   *)gVal, (const int8_t   *)pVar); break;
      case BOX_T_UINT8:  bRefresh = RefreshUint8 ((box_uint8_st  *)gVal, (const uint8_t  *)pVar); break;
      case BOX_T_INT16:  bRefresh = RefreshInt16 ((box_int16_st  *)gVal, (const int16_t  *)pVar); break;
      case BOX_T_UINT16: bRefresh = RefreshUint16((box_uint16_st *)gVal, (const uint16_t *)pVar); break;
      case BOX_T_INT32:  bRefresh = RefreshInt32 ((box_int32_st  *)gVal, (const int32_t  *)pVar); break;
      case BOX_T_UINT32: bRefresh = RefreshUint32((box_uint32_st *)gVal, (const uint32_t *)pVar); break;
      case BOX_T_FLOAT : bRefresh = RefreshFloat ((box_float_st  *)gVal, (const float    *)pVar); break;
      default: break;
    }
  }

  return bRefresh;
}


/**
 * @function Str xxx
 * @brief generate the string corresponding to a value & its format string
 * @param char *str: output buffer
 * @param uint8_t size: lenght of the output buffer
 * @param const box_xxx_st *p: pointer to a typed storage
 * @param const char *format: string format (snprint compatible)
 * @return none
 *
 * Duplicated code to ensure correct type consideration (unlike the 'void* everywhere' method, which makes gcc/splint yelling)
 */
static void StrInt8  (char /*@out@*/ *str, uint8_t size, const box_int8_st   *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrUint8 (char /*@out@*/ *str, uint8_t size, const box_uint8_st  *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrInt16 (char /*@out@*/ *str, uint8_t size, const box_int16_st  *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrUint16(char /*@out@*/ *str, uint8_t size, const box_uint16_st *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrInt32 (char /*@out@*/ *str, uint8_t size, const box_int32_st  *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrUint32(char /*@out@*/ *str, uint8_t size, const box_uint32_st *p, const char *format) {(void) snprintf(str, size, format, p->val);}
static void StrFloat (char /*@out@*/ *str, uint8_t size, const box_float_st  *p, const char *format) {(void) snprintf(str, size, format, p->val);}


/**
 * @function snprintGenericValue
 * @brief generate the string corresponding to a value & its format string (dispatch to the above functions)
 * @param const void *gVal: pointer to a untyped value storage
 * @param valueBoxType_e type: type of the storage
 * @param const char *format: string format (snprint compatible)
 * @return none
 */
static void snprintGenericValue(char /*@out@*/ *str, uint8_t size, const void *gVal, valueBoxType_e type, const char *format) {
  switch(type) {
    case BOX_T_INT8:    StrInt8  (str, size, (const box_int8_st   *)gVal, format); break;
    case BOX_T_UINT8:   StrUint8 (str, size, (const box_uint8_st  *)gVal, format); break;
    case BOX_T_INT16:   StrInt16 (str, size, (const box_int16_st  *)gVal, format); break;
    case BOX_T_UINT16:  StrUint16(str, size, (const box_uint16_st *)gVal, format); break;
    case BOX_T_INT32:   StrInt32 (str, size, (const box_int32_st  *)gVal, format); break;
    case BOX_T_UINT32:  StrUint32(str, size, (const box_uint32_st *)gVal, format); break;
    case BOX_T_FLOAT:   StrFloat (str, size, (const box_float_st  *)gVal, format); break;
    default: str[0] = '\0'; break;
  }
}
