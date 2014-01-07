/**
 * @file r_p2d.c
 * @brief serialized P2D decoder (slave side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-23
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

#include "r_p2d.h"
#include "p2d.h"
#include "gui.h"
#include "serial_common.h"
#include "serial_remote.h"

#ifdef SMART_TFT_SLAVE_MODE

/**
 * Local functions
 */
static int8_t Poly(bool bFill);



/* P2D_Clear
 * ARG: - */
int8_t R_P2D_Clear(void) {
  P2D_Clear();
  return 0;
}

/* P2D_SetColor
 * ARG: front(u16) */
int8_t R_P2D_SetColor(void) {
  int8_t res = -1; color_t front;
  front = RxGetU16();
  if(RxStatus() == 0) {
    P2D_SetColor(front);
    res = 0;
  }
  return res;
}

/* P2D_SetColors
 * ARG: front(u16) back(u16) */
int8_t R_P2D_SetColors(void) {
  int8_t res = -1; color_t front, back;
  front = RxGetU16();
  back = RxGetU16();
  if(RxStatus() == 0) {
    P2D_SetColors(front, back);
    res = 0;
  }
  return res;
}

/* P2D_SetDisplayMode
 * ARG: mode(u8) */
int8_t R_P2D_SetDisplayMode(void) {
  int8_t res = -1; dmode_t mode;
  mode = RxGetU8();
  if(RxStatus() == 0) {
    P2D_SetDisplayMode(mode);
    res = 0;
  }
  return res;
}

/* P2D_SetAlpha
 * ARG: alpha(u8) */
int8_t R_P2D_P2D_SetAlpha(void) {
  int8_t res = -1; uint8_t alpha;
  alpha = RxGetU8();
  if(RxStatus() == 0) {
    P2D_SetAlpha(alpha);
    res = 0;
  }
  return res;
}

/* P2D_SetLineType
 * ARG: lineType(u8) */
int8_t R_P2D_SetLineType(void) {
  int8_t res = -1; line_t lineType;
  lineType = RxGetU8();
  if(RxStatus() == 0) {
    P2D_SetLineType(lineType);
    res = 0;
  }
  return res;
}

/* P2D_SetPixel
 * ARG: x(i16) y(i16) color(u16) */
int8_t R_P2D_SetPixel(void) {
  int8_t res = -1; coord_t x, y; color_t color;
  x = RxGetI16();
  y = RxGetI16();
  color = RxGetU16();
  if(RxStatus() == 0) {
    P2D_SetPixel(x, y, color);
    res = 0;
  }
  return res;
}

/* P2D_Line
 * ARG: x0(i16) y0(i16) x1(i16) y1(i16) */
int8_t R_P2D_Line(void) {
  int8_t res = -1; coord_t x0, y0, x1, y1;
  x0 = RxGetI16();
  y0 = RxGetI16();
  x1 = RxGetI16();
  y1 = RxGetI16();
  if(RxStatus() == 0) {
    P2D_Line(x0, y0, x1, y1);
    res = 0;
  }
  return res;
}

/* P2D_Rect
 * ARG: rec(rect_st) */
int8_t R_P2D_Rect(void) {
  int8_t res = -1; rect_st rec;
  RxGetRec(&rec);
  if(RxStatus() == 0) {
    P2D_Rect(&rec);
    res = 0;
  }
  return res;
}

/* P2D_FillRect
 * ARG: rec(rect_st) */
int8_t R_P2D_FillRect(void) {
  int8_t res = -1; rect_st rec;
  RxGetRec(&rec);
  if(RxStatus() == 0) {
    P2D_FillRect(&rec);
    res = 0;
  }
  return res;
}

/* P2D_SetClip
 * ARG: rec(rect_st) */
int8_t R_P2D_SetClip(void) {
  int8_t res = -1; rect_st rec;
  RxGetRec(&rec);
  if(RxStatus() == 0) {
    P2D_SetClip(&rec);
    res = 0;
  }
  return res;
}

/* P2D_GetLcdWidth
 * ARG: - */
int8_t R_P2D_GetLcdWidth(void) {
  length_t w;
  w = P2D_GetLcdWidth();
  TxMsgPut(w);
  return 0;
}

/* P2D_GetLcdHeight
 * ARG: - */
int8_t R_P2D_GetLcdHeight(void) {
  length_t h;
  h = P2D_GetLcdHeight();
  TxMsgPut(h);
  return 0;
}

/* P2D_SetFont
 * ARG: font(u8) */
int8_t R_P2D_SetFont(void) {
  int8_t res = -1; gui_font_t font;
  font = RxGetU8();
  if(RxStatus() == 0) {
    SetFont(font);
    res = 0;
  }
  return res;
}

/* P2D_GetTextHeight
 * ARG: - */
int8_t R_P2D_GetTextHeight(void) {
  length_t h;
  h = P2D_GetTextHeight();
  TxMsgPut(h);
  return 0;
}

/* P2D_GetTextWidth
 * ARG: str */
int8_t R_P2D_GetTextWidth(void) {
  const uint8_t *pTxt; length_t w = 0; int8_t res = -1;
  RxGetTxt(&pTxt);
  if(RxStatus() == 0) {
    w = P2D_GetTextWidth(pTxt);
    res = 0;
  }
  TxMsgPut(w);
  return res;
}

/* P2D_GetGlyphWidth
 * ARG: - */
int8_t R_P2D_GetGlyphWidth(void) {
  uint8_t glyph; length_t w = 0; int8_t res = -1;
  glyph = RxGetU8();
  if(RxStatus() == 0) {
    w = P2D_GetGlyphWidth(glyph);
    res = 0;
  }
  TxMsgPut(w);
  return res;
}

/* P2D_PutGlyph
 * ARG: x(i16) y(i16) glyph(u8)*/
int8_t R_P2D_PutGlyph(void) {
  int8_t res = -1; coord_t x, y; uint8_t glyph;
  x = RxGetI16();
  y = RxGetI16();
  glyph = RxGetU8();
  if(RxStatus() == 0) {
    P2D_PutGlyph(x, y, glyph);
    res = 0;
  }
  return res;
}

/* P2D_PutText
 * ARG: x(i16) y(i16) text(*txt)*/
int8_t R_P2D_PutText(void) {
  int8_t res = -1; coord_t x, y; const uint8_t *pTxt;
  x = RxGetI16();
  y = RxGetI16();
  RxGetTxt(&pTxt);
  if(RxStatus() == 0) {
    P2D_PutText(x, y, pTxt);
    res = 0;
  }
  return res;
}

/* P2D_Circle
 * ARG: x(i16) y(i16) rad(u16)*/
int8_t R_P2D_Circle(void) {
  int8_t res = -1; coord_t x, y; uint16_t rad;
  x = RxGetI16();
  y = RxGetI16();
  rad = RxGetU16();
  if(RxStatus() == 0) {
    P2D_Circle(x, y, rad);
    res = 0;
  }
  return res;
}

/* P2D_FillCircle
 * ARG: x(i16) y(i16) rad(u16)*/
int8_t R_P2D_FillCircle(void) {
  int8_t res = -1; coord_t x, y; uint16_t rad;
  x = RxGetI16();
  y = RxGetI16();
  rad = RxGetU16();
  if(RxStatus() == 0) {
    P2D_FillCircle(x, y, rad);
    res = 0;
  }
  return res;
}

/* P2D_Poly
 * ARG: nbPoint(u8) point_n.x(i16) point_n.y(i16) ... */
int8_t R_P2D_Poly(void) {
  return Poly(false);
}

/* P2D_FillPoly
 * ARG: nbPoint(u8) point_n.x(i16) point_n.y(i16) ... */
int8_t R_P2D_FillPoly(void) {
  return Poly(true);
}

/* P2D_SpriteGetWidth
 * ARG: img(u8)*/
int8_t R_P2D_SpriteGetWidth(void) {
  int8_t res = -1; length_t w; uint8_t img;
  img = RxGetU8();
  if(RxStatus() == 0) {
    w = SpriteGetWidth(img);
    res = 0;
  }
  TxMsgPut(w);
  return res;
}

/* P2D_SpriteGetHeight
 * ARG: img(u8)*/
int8_t R_P2D_SpriteGetHeight(void) {
  int8_t res = -1; length_t h; uint8_t img;
  img = RxGetU8();
  if(RxStatus() == 0) {
    h = SpriteGetHeight(img);
    res = 0;
  }
  TxMsgPut(h);
  return res;
}

/* SetLut
 * ARG: lut(u8)*/
int8_t R_SetLut(void) {
  int8_t res = -1; uint8_t lut;
  lut = RxGetU8();
  if(RxStatus() == 0) {
    SetLut(lut);
    res = 0;
  }
  return res;
}

/* Sprite
 * ARG: x(i16) y(i16) img(u8)*/
int8_t R_Sprite(void) {
  int8_t res = -1; uint8_t img; coord_t x, y;
  x = RxGetI16();
  y = RxGetI16();
  img = RxGetU8();
  if(RxStatus() == 0) {
    Sprite(x, y, img);
    res = 0;
  }
  return res;
}


static int8_t Poly(bool bFill) {
  int8_t res = -1;
  uint8_t nbPoint;
  uint16_t ii;
  point_st *p;

  nbPoint = RxGetU8();
  if(RxStatus() == 0) {

    /*get some memory to store polygon' points*/
    p = salloc((uint16_t) nbPoint * sizeof(point_st));
    if(p != NULL) {

      /*get points from the RX msg*/
      for(ii = 0; ii < nbPoint; ii++) {
        p[ii].x = RxGetI16();
        p[ii].y = RxGetI16();
      }

      /*RX still OK? display the polygon*/
      if(RxStatus() == 0) {
        if(bFill) P2D_FillPoly(p, nbPoint);
        else P2D_Poly(p, nbPoint);
        res = 0;
      }

      /*free the memory*/
      sfreeFrom(p);
    }
  }
  return res;
}

#endif
