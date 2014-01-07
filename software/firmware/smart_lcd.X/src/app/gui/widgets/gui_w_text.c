/**
 * @file gui_w_text.c
 * @brief text area implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13 : initial version
 *  0.2b  2013-09-07 : Add alignment & word wrap
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

#include "gui_w_text.h"


/**
 * text line
 */
typedef struct txt_line_t {
  struct txt_line_t *next;         /*next line*/
  uint8_t /*@null@*/ *str;  /*'\0' terminated line*/
  coord_t x, y;             /*absolute x & y*/
} txt_line_st;


/**
 * text area (composed of text lines)
 */
typedef struct {

  /*string associated to the text area*/
  txt_line_st *lines;

  /*graphic context; each frame owns a dedicated colorText & font*/
  color_t colorText;
  gui_font_t font;
} text_st;


/**
 * private variables
 * ar_spacer_list[glyph] == 1? the glyph is considered as a space
 */
static const uint8_t ar_spacer_list[256] = {

1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*000-019*/
1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*020-039*/
1, 1, 1, 1, 1, 1, 1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 1, 1, /*040-059*/
1, 1, 1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*060-079*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 1, 1, 1, 1, 1, 1, 0, 0, 0, /*080-099*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*100-119*/
0, 0, 0, 1, 1, 1, 1, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*120-139*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*140-159*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*160-179*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*180-199*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*200-219*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*220-239*/
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0              /*240-255*/
};


/**
 * local functions
 */
static void TextDraw(void *g_obj, void *obj);
static txt_line_st *AllocateLines(const rect_st *rec, const uint8_t /*@null@*/ *str);
static int8_t ExtractLine(const uint8_t *str, length_t wMax, uint16_t from, uint16_t *to);
static void AlignLines(const rect_st *rec, txt_line_st *pLine);

/**
 * @function GUI_W_TextAdd
 * @brief add a text area
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the text area (will be copied into it)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_TextAdd(const rect_st *rec, const void /*@null@*/ *str) {

  g_obj_st *g_obj = NULL, *res = NULL;
  text_st *text = NULL;

  /*check parameters*/
  if(rec != NULL && str != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate the text area*/
      text = salloc(sizeof(text_st));
      if(text != NULL) {

        /*allocate string*/
        text->lines = AllocateLines(rec, str);
        if(text->lines != NULL) {

          /*finalize text_st init.*/
          text->colorText = GetColor(G_COL_TEXT);
          text->font = GetCurrentFont();
          AlignLines(rec, text->lines);

          /*linkage between generic obj & text*/
          g_obj->rec = *rec;
          g_obj->draw = TextDraw;
          g_obj->task = NULL;
          g_obj->obj = text;
          GUI_ObjSetStatic(g_obj, true); /*text area is static: no need to refresh when pressed*/
          res = g_obj;
        }
      }
    }
  }
  return res;
}


/**
 * @function TextDraw
 * @brief text area draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: text object
 * @return none
 */
static void TextDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  text_st *text;
  txt_line_st *pLine;
  color_t colText;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    text =  (text_st*) _obj;

    /*disabled object?*/
    if(GUI_ObjIsDisabled(g_obj)) {
      colText = GetColor(G_COL_D_TEXT);
    }
    /*normal*/
    else {
      colText = text->colorText;
    }

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colText, GetColor(G_COL_BACKGROUND));
    SetFont(text->font);

    /*display each line composing the text area*/
    pLine = text->lines;
    while(pLine != NULL) {
      P2D_PutText(pLine->x, pLine->y, pLine->str);
      pLine = pLine->next;
    }
  }
}


/**
 * @function AllocateLines
 * @brief allocate string lines composing the text area
 * @param const rect_st *rec: text area dimension
 * @param const uint8_t *str: string
 * @return txt_line_st *: pointer to the head of text lines if success, NULL if error
 */
static txt_line_st *AllocateLines(const rect_st *rec, const uint8_t /*@null@*/ *str) {

  bool bError;
  uint16_t from, to, size;
  txt_line_st *pLine = NULL, *pHead = NULL, **ppLastLine = NULL;

  bError = false;
  from = to = 0;
  ppLastLine = &pHead;

  /*extract lines until end of string*/
  while(bError == false && ExtractLine(str, rec->w, from, &to) == 0) {

    /*allocate a text line*/
    pLine = (txt_line_st *) salloc(sizeof(txt_line_st));

    /*init. the text line*/
    if(pLine != NULL) {
      gmemset(pLine, 0, sizeof(txt_line_st));

      /*allocate the string contained in the text line*/
      size = to - from + 2; /*+1 because if to==from, there is one glyph, and +1 for the '\0'*/
      pLine->str = (uint8_t *) salloc(size);
      if(pLine->str != NULL) {

        /*copy the string contained in the text line*/
        gstrncpy(pLine->str, &str[from], size);

        /*next object*/
        *ppLastLine = pLine;
        ppLastLine = &((*ppLastLine)->next);
      }
      else {
        bError = true;
      }
    }
    else {
      bError = true;
    }

    from = to + 1;
  }

  /*return pointer to first text_line if success, NULL if error*/
  if(bError != false) pHead = NULL;

  return pHead;
}


/**
 * @function ExtractLine
 * @brief extract a part of the string; this part will fit in a given width
 * @param const uint8_t *str: eq. &string[0].
 * @param const length_t wMax: width
 * @param uint16_t from: eq. start str extraction at &string[from]
 * @param uint16_t *to: last car position before overlaping wMax
 * @return int8_t: 0 success && string not EOF, -1: string EOF
 */
static int8_t ExtractLine(const uint8_t *str, length_t wMax, uint16_t from, uint16_t *to) {

  int8_t res;
  uint16_t ii, lastSpace;
  length_t wGlyph, w;
  bool bDone;

  res = -1;
  *to = lastSpace = ii = from;
  w = 0;
  bDone = false;

  while(bDone == false) {

    /*end of string?*/
    if(str[ii] == 0) {
      bDone = true;
      lastSpace = ii - 1; /*end of string is also considered as a space*/
    }
    else {

      /*get the current glyph' width*/
      wGlyph = P2D_GetGlyphWidth(str[ii]);

      /*does this gliph fits into the current line? yes*/
      if(w + wGlyph <= wMax) {
        w += wGlyph;
        if(ar_spacer_list[str[ii]] != 0) lastSpace = ii; /*store the position of last ' ' which still fits within wMax*/
        ii++;
      }
      /*the current glyph does not fit; quit*/
      else {
        bDone = true;
      }
    }
  }

  /*is there something to allocate?*/
  if(from != ii) {

    /*word longer than the whole rec->w ? set the destination to the last glyph which fitted in rec->w*/
    if(from == lastSpace) *to = ii - 1;

    /*otherwise, save string from <from> to <last detected ' '>; the word after ' ' does not fit & will be inserted in the next line*/
    else *to = lastSpace;

    res = 0;
  }

  return res;
}


/**
 * @function AlignLines
 * @brief modify each text line coordinates according to the current alignment
 * @param const rect_st *rec: text area dimension
 * @param txt_line_st *pHead: pointer to the first text line
 * @return none
 */
static void AlignLines(const rect_st *rec, txt_line_st *pHead) {

  txt_line_st *pLine;
  length_t hFont, hTot;
  gui_align_t align;
  coord_t y;

  hFont = P2D_GetTextHeight();
  hTot = 0;
  align = GUI_GetAlign();

  pLine = pHead;
  while(pLine != NULL) {

    /*x align*/
    if( (align & G_ALIGN_H_CENTER) != 0) {
      pLine->x = rec->x + ((coord_t) rec->w - P2D_GetTextWidth(pLine->str)) / 2;
    }
    else if( (align & G_ALIGN_H_RIGHT) != 0) {
      pLine->x = rec->x + ((coord_t) rec->w - P2D_GetTextWidth(pLine->str));
    }
    else {
      pLine->x = rec->x;
    }

    /*increase the total height, go to next line*/
    hTot += hFont;
    pLine = pLine->next;
  }

  /*y align: compute y of the first line; y will be increased of hFont every lines*/
  if( (align & G_ALIGN_V_CENTER) != 0) {
    y = rec->y + ((coord_t) rec->h - hTot) / 2;
  }
  else if( (align & G_ALIGN_V_BOTTOM) != 0) {
    y = rec->y + ((coord_t) rec->h - hTot);
  }
  else {
    y = rec->y;
  }

  pLine = pHead;
  while(pLine != NULL) {
    pLine->y = y;
    y += hFont;
    pLine = pLine->next;
  }
}
