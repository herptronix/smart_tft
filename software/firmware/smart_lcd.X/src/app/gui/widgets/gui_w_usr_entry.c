/**
 * @file gui_w_usr_entry.c
 * @brief user string entry (with text selection capability) implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-09-15 : initial version
 *  0.2b  2014-02-01 : minor bug fix (refresh insert bar ONLY if entry is editable)
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

#include "gui_w_usr_entry.h"

#define CAR_SHIFT   10  /*when insertion reaches the left/right entry corner, shift display of CAR_SHIFT glyphs*/
#define SCROLL_TRIG 12  /*trigger scroll in pixel (scroll if touchscreen @ [xleft to xleft+SCROLL_TRIG] or [xright-SCROLL_TRIG to xright])*/
#define SCROLL_TM   10  /*if scroll, scroll every 10 ms*/

/**
 * usr_entry_st
 */
typedef struct {

  timer_t tBlink;         /*entry bar blinks every tBlink ms*/
  timer_t tScroll;        /*when active, scroll 1 glyph every tScroll ms*/
  uint8_t *buffer;        /*entry string*/
  uint16_t sizeMax;       /*maximum size (in byte, i.e. including the \0) of entry string*/
  uint16_t offsetDisplay; /*start displaying text at buffer[offsetDisplay]*/
  uint16_t len;           /*== strlen(buffer)*/
  uint16_t cursStart;     /*user selection start*/
  uint16_t cursStop;      /*user selection end*/
  bool bBlink;            /*toggle every tBlink ms; display or not the entry bar*/
  bool bPressed;          /*true if pressed; for internal machine state*/
  bool bEditable;         /*editable? will display insert bar & selection, and will allow string modification*/
  color_t colText;        /*text color*/
  gui_font_t font;        /*text font*/
} usr_entry_st;


/**
 * local functions
 */
#define _MIN(a, b) a < b ? a : b;
#define _MAX(a, b) a > b ? a : b;
static void EntryDraw(void *g_obj, void *obj);
static void EntryTask(void *_g_obj, void *_obj);
static uint16_t StrInsert(uint8_t *strDest, uint16_t strDestSize, const uint8_t *strIns, uint16_t insPos);
static void StrDelete(uint8_t *strDest, uint16_t strDestSize, uint16_t from, uint16_t to);
static void GetTextCoords(const rect_st *rec, coord_t /*@out@*//*@null@*/*xMin, coord_t /*@out@*//*@null@*/*yMin, coord_t /*@out@*//*@null@*/*xMax, coord_t /*@out@*//*@null@*/*yMax);
static uint16_t FindSelectedCar(const uint8_t *buffer, uint16_t from, coord_t xStart, coord_t xTouch);
static length_t GetPartialStrWidth(const uint8_t *buffer, uint16_t from, uint16_t to);


/**
 * @function GUI_W_UsrEntryAdd
 * @brief add user entry
 * @param const rect_st *rec: object dimension
 * @param const void *buffer: text of the user entry (may be modified)
 * @param uint16_t sizeMax: size (in bytes) of the buffer, including the \0
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_UsrEntryAdd(const rect_st *rec, void *buffer, uint16_t sizeMax, bool bEditable) {

  g_obj_st *g_obj = NULL, *res = NULL;
  usr_entry_st *entry = NULL;

  /*check parameters*/
  if(rec != NULL && buffer != NULL && sizeMax > 2) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate a entry*/
      entry = salloc(sizeof(usr_entry_st));
      if(entry != NULL) {

        /*entry settings*/
        entry->buffer = (uint8_t *) buffer;
        entry->buffer[sizeMax - 1] = 0;   /*ensure that the user string is \0 terminated*/
        entry->sizeMax = sizeMax;
        entry->len = gstrlen(entry->buffer);
        entry->tBlink = 0;
        entry->tScroll = 0;
        entry->bBlink = false;
        entry->bPressed = false;
        entry->bEditable = bEditable;
        entry->colText = GetColor(G_COL_TEXT);
        entry->font = GetCurrentFont();

        /*start displaying at the very begining of the string*/
        entry->offsetDisplay = 0;

        /*start with the whole string selected*/
        entry->cursStart = 0;
        entry->cursStop = gstrlen(entry->buffer);

        /*linkage between generic obj & usr entry*/
        g_obj->rec = *rec;
        g_obj->draw = EntryDraw;
        g_obj->task = EntryTask;
        g_obj->obj = entry;
        res = g_obj;
      }
    }
  }

  return res;
}


/**
 * @function GUI_W_UsrEntryInsert
 * @brief insert a string into the string of the entry key, at current user insert position
 * @param void *_g_obj: generic object
 * @param const uint8_t *strIns: string to insert
 * @return none
 */
void GUI_W_UsrEntryInsert(g_obj_st *obj, const uint8_t *strIns) {

  usr_entry_st *entry;

  if(obj != NULL && obj->draw == EntryDraw && strIns != NULL) {

    entry = (usr_entry_st *) obj->obj;

    if(entry->bEditable) {
      /*if some text is selected, delete it first; after GUI_UsrEntryDelKey() execution, entry->cursStart == entry->cursStop*/
      if(entry->cursStart != entry->cursStop) GUI_W_UsrEntryDelete(obj);

      /*insert string at insertion pos & update selection cursors*/
      entry->cursStop = entry->cursStart = StrInsert(entry->buffer, entry->sizeMax, strIns, entry->cursStart);

      /*update str len*/
      entry->len = gstrlen(entry->buffer);

      /*force refresh*/
      GUI_ObjSetNeedRefresh(obj, true);
    }
  }
}


/**
 * @function GUI_W_UsrEntrySelectAll
 * @brief select the whole string of the entry key
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntrySelectAll(g_obj_st *obj) {

  usr_entry_st *entry;

  if(obj != NULL && obj->draw == EntryDraw) {

    entry = (usr_entry_st *) obj->obj;

    /*update selection cursors*/
    entry->cursStart = 0;
    entry->cursStop = gstrlen(entry->buffer);

    /*force refresh*/
    GUI_ObjSetNeedRefresh(obj, true);
  }
}


/**
 * @function GUI_W_UsrEntryGetSelection
 * @brief copy the selected string part into a given buffer
 * @param void *_g_obj: generic object
 * @param uint8_t *buffer: user buffer; will be \0 terminated
 * @param uint16_t bufSize: size of the user buffer
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntryGetSelection(g_obj_st *obj, uint8_t *buffer, uint16_t bufSize) {

  usr_entry_st *entry;
  uint16_t pos, end;

  if(obj != NULL && obj->draw == EntryDraw && buffer != NULL && bufSize > 0) {

    entry = (usr_entry_st *) obj->obj;

    /*copy the highlighted text of the entry in the user buffer*/
    pos = _MIN(entry->cursStart, entry->cursStop);
    end = _MAX(entry->cursStart, entry->cursStop);

    while(bufSize > 1 && pos < end) {
      *buffer = entry->buffer[pos];
      pos++;
      buffer++;
      bufSize--;
    }

    /*always be sure that str is '\0' terminated*/
    *buffer = 0;
  }
}


/**
 * @function GUI_W_UsrEntryDelete
 * @brief Delete the selected string part (if any), or the car corresponding to insert line position
 * @param void *_g_obj: generic object
 * @return none
 */
void GUI_W_UsrEntryDelete(g_obj_st *obj) {

  uint16_t from, to;
  usr_entry_st *entry;

  if(obj != NULL && obj->draw == EntryDraw) {

    entry = (usr_entry_st *) obj->obj;

    if(entry->bEditable) {
      from = _MIN(entry->cursStart, entry->cursStop);
      to = _MAX(entry->cursStart, entry->cursStop);

      /*delecte the selection, or car located before the insert line*/
      StrDelete(entry->buffer, entry->sizeMax, from, to);

      /*if there was no user selection, decrease the position of the insert bar*/
      if(from == to && from > 0) {
        entry->cursStart--;
        entry->cursStop--;
      }

      /*always ensure that the resulting insert line is bounded into the string size*/
      entry->len = gstrlen(entry->buffer);
      if(entry->len < entry->cursStart) entry->cursStart = entry->len;

      /*after a deletion, set insert line to the lower cursor; since insert line -> entry->cursStop = entry->cursStart*/
      entry->cursStart = _MIN(entry->cursStart, entry->cursStop);
      entry->cursStop = entry->cursStart;

      /*force refresh*/
      GUI_ObjSetNeedRefresh(obj, true);
    }
  }
}


/**
 * @function EntryTask
 * @brief user entry task; handles user interaction, ensures correct display (according to insert line position)
 *   TODO: rewrite it, quite complex ><", even if it seems to work properly
 * @param void *_g_obj: generic object
 * @param void *_obj: frame object
 * @return none
 */
static void EntryTask(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  usr_entry_st *entry;
  uint16_t selectedGlyph, len;
  coord_t xt, xMin, xMax;

  /*retrieve the entry object & its absolute coord, then deduce text coordinates*/
  g_obj = (g_obj_st *) _g_obj;
  entry =  (usr_entry_st*) _obj;
  SetFont(entry->font);   /*ensure that the correct font is used for text coordinates calulus*/
  GetTextCoords(&(g_obj->rec), &xMin, NULL, &xMax, NULL);   /*gets text area coords*/

  /**
   * 1) overall protection
   * may trig if the user modifies the buffer without using dedicated functions
   * in case, just reset display, & ensure the \0 terminaison
   */
  len = gstrlen(entry->buffer);
  if(entry->len != len) {
    if(len > entry->sizeMax - 1) len = entry->sizeMax - 1;
    entry->len = len;
    entry->buffer[entry->len] = 0;
    entry->offsetDisplay = 0;
    entry->cursStart = 0;
    entry->cursStop = 0;
    entry->bPressed = false;
    GUI_ObjSetNeedRefresh(g_obj, true);
  }

  /**
   * 2) For insert mode only (no text selected, i.e. entry->cursStart == entry->cursStop)
   * always check if the insert line is not outside the current displayed text area.
   * may happen after an insertion / deletion (n.b. these functions always set NeedRefresh to true).
   * If outside, modify the offsetDisplay to make the insert line visible
   */
  if(GUI_ObjIsNeedRefresh(g_obj) == true && entry->cursStart == entry->cursStop) {

    /**
     * the insert bar is out (left side); may happen if:
     *  - <delete key> when the insert bar is at the left of the entry
     *  - <replace / delete selection> when the text selection starts before the displayed text
     */
    if(entry->cursStart < entry->offsetDisplay) {
      if(entry->cursStart > CAR_SHIFT) entry->offsetDisplay = entry->cursStart - CAR_SHIFT;
      else entry->offsetDisplay = 0;
    }

    /**
     * the insert bar "may" be out (right side); may happen if:
     *  - <insert> when the insert bar is close to the right of the entry
     *  - <insert buffer> inserting a big copy/paste text
     */
    else {
      if(xMax < xMin + GetPartialStrWidth(entry->buffer, entry->offsetDisplay, entry->cursStart)) {
        if(entry->cursStart > CAR_SHIFT) entry->offsetDisplay = entry->cursStart - CAR_SHIFT;
        else entry->offsetDisplay = 0;
      }
    }
  }

  /**
   * 3) For text selection (i.e. entry->cursStart != entry->cursStop)
   * handle scroll & update the user selection
   */
  else {

    if(GUI_ObjIsPressed(g_obj)) {

      /*finds the selectedGlyph #id which correspond to the x touchcreen*/
      GUI_ReadTouchScreen(&xt, NULL);
      selectedGlyph = FindSelectedCar(entry->buffer, entry->offsetDisplay, xMin, xt);

      /*scroll text?*/
      if(IsTimerElapsed(entry->tScroll)) {
        /*scroll to left?*/
        if(xt < (xMin + SCROLL_TRIG) && entry->offsetDisplay > 0) {
          entry->offsetDisplay--;
          selectedGlyph--;
        }
        /*scroll to right*/
        else if(xt > (xMax - SCROLL_TRIG) && entry->buffer[selectedGlyph] != 0) {
          entry->offsetDisplay++;
          selectedGlyph++;
        }
        entry->tScroll = GetPeriodicTimeout(SCROLL_TM);
      }

      /*if the entry wasn't previously pressed, start a new selection (i.e. cursStart = cursStop = selectedGlyph)*/
      if(entry->bPressed == false) {
        entry->bPressed = true;
        entry->cursStart = selectedGlyph;
        entry->cursStop = selectedGlyph;
        GUI_ObjSetNeedRefresh(g_obj, true);
      }
      /*otherwise, update the current selection (i.e. update only cursStop)*/
      else {
        if(entry->cursStop != selectedGlyph) {
          entry->cursStop = selectedGlyph;
          GUI_ObjSetNeedRefresh(g_obj, true);
        }
      }
    }
    else {
      entry->bPressed = false;
    }
  }

  /*check timer blink (for blinking the insert line)*/
  if(IsTimerElapsed(entry->tBlink) && entry->bEditable == true) {
    entry->bBlink = !entry->bBlink;
    entry->tBlink = GetPeriodicTimeout(500);
    GUI_ObjSetNeedRefresh(g_obj, true);
  }
}


/**
 * @function EntryDraw
 * @brief user entry draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: frame object
 * @return none
 */
static void EntryDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  usr_entry_st *entry;

  uint8_t glyph;
  uint16_t ii, selStart, selStop;
  coord_t x, xInsertLine, xMin, yMin, xMax, yMax;
  rect_st rec;
  color_t colBack, colText;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    entry =  (usr_entry_st*) _obj;

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    SetFont(entry->font);

    if(GUI_ObjIsDisabled(g_obj)) {
      colBack = GetColor(G_COL_BACKGROUND);
      colText = GetColor(G_COL_D_TEXT);
    }
    else {
      colBack = GetColor(G_COL_E_BACKGROUND);
      colText = entry->colText;
    }

    /*retrieve text coord*/
    GetTextCoords(&(g_obj->rec), &xMin, &yMin, &xMax, &yMax);

    /*display usr_entry glyphs, one by one*/
    selStart = _MIN(entry->cursStart, entry->cursStop);
    selStop = _MAX(entry->cursStart, entry->cursStop);
    x = xMin;
    xInsertLine = x;
    ii = entry->offsetDisplay;

    while(x < xMax && entry->buffer[ii] != 0) {

      /*select the color of the text, according to the user selection (i.e. reverse colors if the current glyph is a part of the user selection)*/
      if(entry->bEditable == false || selStart == selStop || ii < selStart || ii >= selStop) {
        P2D_SetColors(colText, colBack);
      }
      else {
        P2D_SetColors(colBack, GetColor(G_COL_SPECIAL));
      }

      /*display the glyph*/
      glyph = entry->buffer[ii];
      P2D_PutGlyph(x, yMin, glyph);
      x += P2D_GetGlyphWidth(glyph);

      /*if the car corresponds to the user selection bar, store its coord*/
      if(ii == entry->cursStop - 1) xInsertLine = x;

      /*next car*/
      ii++;
    }

    /*clear from last car to the end of the entry*/
    P2D_SetColors(colBack, colBack);
    (void) P2D_CoordToRect(&rec, x, yMin, xMax, yMax);
    P2D_FillRect(&rec);

    /*clear between text and object rect (1 px width)*/
    (void) P2D_CoordToRect(&rec, xMin-1, yMin-1, xMax+1, yMax+1);
    P2D_Rect(&rec);

    /*display the insert line*/
    if(entry->bEditable && entry->bBlink) {
      P2D_SetColor(colText);
      P2D_Line(xInsertLine, yMin, xInsertLine, yMax);
    }

    /*object rect*/
    P2D_SetColor(GetColor(G_COL_LOWER_REC));
    P2D_Rect(&(g_obj->rec));
  }
}


/**
 * @function StrInsert
 * @brief insert a string in another one
 * @param uint8_t *strDest: string destination
 * @param uint16_t strDestSize: size (in byte) of the string destination
 * @param const uint8_t *strIns: string to insert
 * @param uint16_t insPos: position in 'string destination' where to insert the strIns
 * @return uint16_t: return the new value of the insertion position
 */
static uint16_t StrInsert(uint8_t *strDest, uint16_t strDestSize, const uint8_t *strIns, uint16_t insPos) {

  int32_t pos;
  int32_t shiftCnt = gstrlen(strIns);

  /*shift the right part of the string*/
  for(pos = strDestSize - 1; pos - shiftCnt >= insPos; pos--) {
    strDest[pos] = strDest[pos - shiftCnt];
  }

  /*then copy the new content*/
  while(insPos < strDestSize && *strIns != 0) {
    strDest[insPos] = *strIns;
    strIns++;
    insPos++;
  }

  /*always be sure that str is '\0' terminated*/
  strDest[strDestSize - 1] = 0;

  /*always be sure that the insertion line is bounded into the string size*/
  if(insPos > strDestSize - 1) insPos = strDestSize - 1;

  return insPos;
}


/**
 * @function StrDelete
 * @brief insert a part of a string
 * @param uint8_t *strDest: string to modify
 * @param uint16_t strDestSize: size (in byte) of the string
 * @param uint16_t from: deletion from...
 * @param uint16_t to: deletion to... If no selection (i.e. from==to), the car corresponding to from-1 will be deleted
 * @return none
 */
static void StrDelete(uint8_t *strDest, uint16_t strDestSize, uint16_t from, uint16_t to) {

  /*delete acts only after the first car*/
  if(to > 0) {

    /*if no highlighted text, virtually select the car between to and to-1*/
    if(to == from) from = to - 1;

    /*delete (i.e. buffer shift)*/
    while(to < strDestSize && from < strDestSize) {
      strDest[from] = strDest[to];
      from++;
      to++;
    }

    /*always ensure that str is '\0' terminated*/
    strDest[strDestSize - 1] = 0;
  }
}


/**
 * @function GetTextCoords
 * @brief returns the coords defining the text area of the user_entry
 * @param const rect_st *rec: generic object dimension
 * @param coord_t *xMin, *yMin, *xMax, *yMax: output coords
 * @return none
 */
static void GetTextCoords(const rect_st *rec, coord_t *xMin, coord_t *yMin, coord_t *xMax, coord_t *yMax) {
  coord_t x0, y0, x1, y1;
  (void) P2D_RectToCoord(rec, &x0, &y0, &x1, &y1);
  if(xMin != NULL) *xMin = x0 + 2;
  if(yMin != NULL) *yMin = y0 + 2;
  if(xMax != NULL) *xMax = x1 - 2;
  if(yMax != NULL) *yMax = y1 - 2;
}


/**
 * @function FindSelectedCar
 * @brief return the #id of the selected car, according to touchscreen & string display offset
 * @param const uint8_t *buffer: pointer to the string (addr #0) of the entry bar
 * @param uint16_t from: string display offset
 * @param coord_t xStart: x coord, (start of string display)
 * @param coord_t xTouch: touchscreen x (absolute)
 * @return uint16_t: #id (i.e. position in *buffer) of the selected car
 */
static uint16_t FindSelectedCar(const uint8_t *buffer, uint16_t from, coord_t xStart, coord_t xTouch) {

  coord_t x;
  uint16_t ii;
  uint8_t glyph;

  ii = from;
  x = xStart;

  while(x < xTouch && buffer[ii] != 0) {
    glyph = buffer[ii];
    x += P2D_GetGlyphWidth(glyph);
    ii++;
  }

  return ii;
}


/**
 * @function GetPartialStrWidth
 * @brief returns the width of a part of a string, bounded by 'from' & 'to'
 * @param const uint8_t *buffer: pointer to the string (addr #0) of the entry bar
 * @param uint16_t from, to: bound
 * @return length_t: width of the string part
 */
static length_t GetPartialStrWidth(const uint8_t *buffer, uint16_t from, uint16_t to) {

  length_t w;
  uint16_t ii;

  w = 0;
  ii = from;

  while(ii < to && buffer[ii] != 0) {
    w += P2D_GetGlyphWidth(buffer[ii]);
    ii++;
  }

  return w;
}
