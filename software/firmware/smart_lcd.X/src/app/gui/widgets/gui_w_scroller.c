/**
 * @file gui_w_scroller.c
 * @brief scroller bar implementation
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-08-27  : initial version
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

#include "gui_w.h"

#define BAR_MIN_LENGTH    5                     /*minimum length of the bar*/
#define SCROLL_MIN_LENGTH (3 * BAR_MIN_LENGTH)  /*minimum length of the object*/
#define SCROLL_MIN_WIDTH  7


/**
 * scroller_st
 */
typedef struct {
  scroll_param_st *param;
  scroll_param_st prevParam;
  g_obj_st *refreshObj;
} scroller_st;


/**
 * local functions
 */
static void ScrollerDraw(void *g_obj, void *obj);
static void ScrollerRefresh(void *g_obj, void *obj);
static bool IsVertical(const rect_st *rec);
static length_t GetTotLen(const rect_st *rec);
static length_t GetBarLen(const rect_st *rec, const scroll_param_st *s);
static length_t GetBarPos(length_t totLen, const scroll_param_st *s);


/**
 * @function GUI_W_ScrollerAdd
 * @brief add a scroller bar
 * @param const rect_st *rec: object dimension
 * @param g_obj_st *refreshObj: object to refresh when scroll changes
 * @param scroll_param_st *param: already-allocated scroller param
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param) {

  g_obj_st *g_obj = NULL, *res = NULL;
  scroller_st *scroller = NULL;

  /*check parameters*/
  if(rec != NULL && param != NULL) {

    /*check dimension, according to the orientation*/
    if( (IsVertical(rec) && rec->h >= SCROLL_MIN_LENGTH && rec->w >= SCROLL_MIN_WIDTH) ||
        (rec->w >= SCROLL_MIN_LENGTH && rec->h >= SCROLL_MIN_WIDTH) ) {

      /*allocate a generic object*/
      g_obj = GUI_AddGenericObject();
      if(g_obj != NULL) {

        /*allocate & init the scroller*/
        scroller = (scroller_st *) salloc(sizeof(scroller_st));
        if(scroller != NULL) {
          scroller->param = param;
          scroller->prevParam = *param;
          scroller->refreshObj = refreshObj;

          /*linkage between generic obj & scroller*/
          g_obj->rec = *rec;
          g_obj->draw = ScrollerDraw;
          g_obj->task = ScrollerRefresh;
          g_obj->obj = scroller;
          res = g_obj;
        }
      }
    }
  }

  return res;
}


/**
 * @function GUI_W_ScrollerSetOffset
 * @brief set the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @param int32_t offset: new value
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerSetOffset(scroll_param_st *p, int32_t offset) {

  bool bRefresh = false;

  if(p != NULL) {
    /*gap the offset to its totSize*/
    if(offset < 0 || p->wndSize >= p->totSize) {
      offset = 0;
    }
    else {
      if(offset > p->totSize - p->wndSize) {
        offset = p->totSize - p->wndSize;
      }
    }

    /*if offset != of the older one -> refresh*/
    if(p->offset != (uint16_t) offset) {
      p->offset = (uint16_t) offset;
      bRefresh = true;
    }
  }

  return bRefresh;
}


/**
 * @function GUI_W_ScrollerIncOffset
 * @brief increment the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerIncOffset(scroll_param_st *p) {

  bool bRefresh = false;
  int32_t offset;

  if(p != NULL) {
    offset = p->offset + 1;
    bRefresh = GUI_W_ScrollerSetOffset(p, offset);
  }

  return bRefresh;
}


/**
 * @function GUI_W_ScrollerDecOffset
 * @brief decrement the offset value of a scroll_param_st (safe way)
 * @param scroll_param_st *p: input
 * @return bool: true ->  need refresh
 */
bool GUI_W_ScrollerDecOffset(scroll_param_st *p) {

  bool bRefresh = false;
  int32_t offset;

  if(p != NULL) {
    offset = p->offset - 1;
    bRefresh = GUI_W_ScrollerSetOffset(p, offset);
  }

  return bRefresh;
}


/**
 * @function ScrollerDraw
 * @brief scroller bar draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: scroller object
 * @return none
 */
static void ScrollerDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  scroller_st *s;
  length_t barLen, totLen, offset;
  rect_st lrec;
  color_t colLine, colBack, colBar;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    s =  (scroller_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colLine = GetColor(G_COL_LOWER_REC);
      colBack = GetColor(G_COL_BACKGROUND);
      colBar  = GetColor(G_COL_LOWER_REC);
    }
    /*pressed?*/
    else if(GUI_ObjIsPressed(g_obj)) {
      colLine = GetColor(G_COL_LOWER_REC);
      colBack = GetColor(G_COL_E_BACKGROUND);
      colBar  = GetColor(G_COL_SPECIAL);
    }
    /*default*/
    else {
      colLine = GetColor(G_COL_LOWER_REC);
      colBack = GetColor(G_COL_E_BACKGROUND);
      colBar  = GetColor(G_COL_LOWER_REC);
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);

    /*draw rec*/
    lrec = g_obj->rec;
    P2D_SetColor(colLine);
    P2D_Rect(&lrec);

    /*draw background*/
    lrec = g_obj->rec;
    lrec.x += 1; lrec.y += 1;
    lrec.w -= 2; lrec.h -= 2;
    P2D_SetColor(colBack);
    P2D_FillRect(&lrec);

    /*draw bar*/
    lrec = g_obj->rec;
    lrec.x += 2; lrec.y += 2;
    lrec.w -= 4; lrec.h -= 4;
    barLen = GetBarLen(&lrec, s->param);
    totLen = GetTotLen(&lrec);
    offset = GetBarPos(totLen, s->param);

    if(IsVertical(&(g_obj->rec))) {
      lrec.y += offset;
      lrec.h = barLen;
    }
    else {
      lrec.x += offset;
      lrec.w = barLen;
    }

    P2D_SetColor(colBar);
    P2D_FillRect(&lrec);
  }
}


/**
 * @function ScrollerRefresh
 * @brief scroller task
 * @param void *_g_obj: generic object
 * @param void *_obj: scroller object
 * @return none
 */
static void ScrollerRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  scroller_st *s;
  scroll_param_st *param;
  coord_t tc;
  length_t barLen, totLen;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    s =  (scroller_st*) _obj;
    param = s->param;


    if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {

      barLen = GetBarLen(&(g_obj->rec), param);
      totLen = GetTotLen(&(g_obj->rec));

      /*gets the relative coord (between 0 and totLen), according to orientation*/
      if(IsVertical(&(g_obj->rec))) {
        GUI_ReadTouchScreen(NULL, &tc);
        tc -= g_obj->rec.y;
      }
      else {
        GUI_ReadTouchScreen(&tc, NULL);
        tc -= g_obj->rec.x;
      }

      /*substract half of the barLen for getting the 'graphical' offset*/
      tc -= barLen / 2;

      /*ensure that the bar fits into totLen*/
      if(tc < 0) tc = 0;
      else if(tc > totLen - barLen) tc = totLen - barLen;

      /*convert & set the 'graphical' offset into the real offset*/
      if(GUI_W_ScrollerSetOffset(param, (int32_t) tc * param->totSize / totLen)) {
        if(s->refreshObj != NULL) GUI_ObjSetNeedRefresh(s->refreshObj, true);
      }
    }

    /* param modified (by the user or from touchscreen)? -> refresh the scroller*/
    if(param->wndSize != s->prevParam.wndSize ||
       param->totSize != s->prevParam.totSize ||
       param->offset != s->prevParam.offset) {
      s->prevParam = *param;
      GUI_ObjSetNeedRefresh(g_obj, true);
    }
  }
}


/**
 * some utils
 */
static bool IsVertical(const rect_st *rec) {
  return rec->h > rec->w? true: false;
}

static length_t GetTotLen(const rect_st *rec) {
  return IsVertical(rec)? rec->h: rec->w;
}

static length_t GetBarLen(const rect_st *rec, const scroll_param_st *s) {

  length_t res, totLen;
  totLen = GetTotLen(rec);

  if(s->totSize > s->wndSize) {
    res = (length_t) ((int32_t)totLen * s->wndSize / s->totSize);
    if(res < BAR_MIN_LENGTH) res = BAR_MIN_LENGTH;
    else if(res > totLen) res = totLen;
  }
  else {
    res = totLen;
  }

  return res;
}

static length_t GetBarPos(length_t totLen, const scroll_param_st *s) {

  length_t res = 0;

  if(s->totSize > s->wndSize) {
    res = (length_t) ((int32_t)totLen * s->offset / s->totSize);
  }

  return res;
}
