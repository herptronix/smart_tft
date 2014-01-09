/**
 * @file r_p2d.c
 * @brief P2D serialized commands (maser side)
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
#include "serial_tx.h"

/* P2D_Clear
 * ARG: - */
void R_P2D_Clear(void) {
  TxMsgPutByte(OP_P2D_CLEAR);
}

/* P2D_SetColor
 * ARG: front(u16) */
void R_P2D_SetColor(color_t front) {
  TxMsgPutByte(OP_P2D_SET_COLOR);
  TxMsgPut(front);
}

/* P2D_SetColors
 * ARG: front(u16) back(u16) */
void R_P2D_SetColors(color_t front, color_t back) {
  TxMsgPutByte(OP_P2D_SET_COLORS);
  TxMsgPut(front);
  TxMsgPut(back);
}

/* P2D_SetDisplayMode
 * ARG: mode(u8) */
void R_P2D_SetDisplayMode(dmode_t mode) {
  TxMsgPutByte(OP_P2D_SET_DISPLAY_MODE);
  TxMsgPutByte(mode);
}

/* P2D_SetAlpha
 * ARG: alpha(u8) */
void R_P2D_P2D_SetAlpha(uint8_t alpha) {
  TxMsgPutByte(OP_P2D_SET_ALPHA);
  TxMsgPut(alpha);
}

/* P2D_SetLineType
 * ARG: lineType(u8) */
void R_P2D_SetLineType(line_t lineType) {
  TxMsgPutByte(OP_P2D_SET_LINE_TYPE);
  TxMsgPutByte(lineType);
}

/* P2D_SetPixel
 * ARG: x(i16) y(i16) color(u16) */
void R_P2D_SetPixel(coord_t x, coord_t y, color_t color) {
  TxMsgPutByte(OP_P2D_SET_PIXEL);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPut(color);
}

/* P2D_Line
 * ARG: x0(i16) y0(i16) x1(i16) y1(i16) */
void R_P2D_Line(coord_t x0, coord_t y0, coord_t x1, coord_t y1) {
  TxMsgPutByte(OP_P2D_LINE);
  TxMsgPut(x0);
  TxMsgPut(y0);
  TxMsgPut(x1);
  TxMsgPut(y1);
}

/* P2D_Rect
 * ARG: rec(rect_st) */
void R_P2D_Rect(const rect_st *rec) {
  if(rec != NULL) {
    TxMsgPutByte(OP_P2D_RECT);
    TxMsgPutRect(rec);
  }
}

/* P2D_FillRect
 * ARG: rec(rect_st) */
void R_P2D_FillRect(const rect_st *rec) {
  if(rec != NULL) {
    TxMsgPutByte(OP_P2D_FILL_RECT);
    TxMsgPutRect(rec);
  }
}

/* P2D_SetClip
 * ARG: rec(rect_st) */
void R_P2D_SetClip(const rect_st *rec) {

  rect_st lrec;
  if(rec == NULL) {
    lrec.x = lrec.y = 0;
    lrec.w = 320; lrec.h = 240;
    rec = &lrec;
  }

  TxMsgPutByte(OP_P2D_SET_CLIP);
  TxMsgPutRect(rec);
}

/* P2D_GetLcdWidth TODO: physical read
 * ARG: - */
length_t R_P2D_GetLcdWidth(void) {
  return 320;
}

/* P2D_GetLcdHeight TODO: physical read
 * ARG: - */
length_t R_P2D_GetLcdHeight(void) {
  return 240;
}

/* P2D_SetFont
 * ARG: font(u8) */
void R_P2D_SetFont(gui_font_t font) {
  TxMsgPutByte(OP_P2D_SET_FONT);
  TxMsgPut(font);
}

/* P2D_GetTextHeight TODO
 * ARG: - */
length_t R_P2D_GetTextHeight(void) {
  return 0;
}

/* P2D_GetTextWidth TODO
 * ARG: - */
length_t R_P2D_GetTextWidth(const void *str) {
  return 0;
}

/* P2D_GetGlyphWidth TODO
 * ARG: - */
length_t R_P2D_GetGlyphWidth(void) {
  return 0;
}

/* P2D_PutGlyph
 * ARG: x(i16) y(i16) glyph(u8)*/
void R_P2D_PutGlyph(coord_t x, coord_t y, uint8_t glyph) {
  TxMsgPutByte(OP_P2D_PUT_GLYPH);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPut(glyph);
}

/* P2D_PutText
 * ARG: x(i16) y(i16) text(*txt)*/
void R_P2D_PutText(coord_t x, coord_t y, const void *str) {
  TxMsgPutByte(OP_P2D_PUT_TEXT);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPutStr(str);
}

/* P2D_Circle
 * ARG: x(i16) y(i16) rad(u16)*/
void R_P2D_Circle(coord_t x, coord_t y, length_t rad) {
  TxMsgPutByte(OP_P2D_CIRCLE);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPut(rad);
}

/* P2D_FillCircle
 * ARG: x(i16) y(i16) rad(u16)*/
void R_P2D_FillCircle(coord_t x, coord_t y, length_t rad) {
  TxMsgPutByte(OP_P2D_FILL_CIRCLE);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPut(rad);
}

/* P2D_Poly
 * ARG: nbPoint(u8) point_n.x(i16) point_n.y(i16) ... */
void R_P2D_Poly(uint8_t nbPoint, const point_st *points) {
  if(points != NULL) {
    TxMsgPutByte(OP_P2D_POLY);
    TxMsgPut(nbPoint);
    while(nbPoint != 0) {
      TxMsgPut(points->x);
      TxMsgPut(points->y);
      points++;
      nbPoint--;
    }
  }
}

/* P2D_FillPoly
 * ARG: nbPoint(u8) point_n.x(i16) point_n.y(i16) ... */
void R_P2D_FillPoly(uint8_t nbPoint, const point_st *points) {
  if(points != NULL) {
    TxMsgPutByte(OP_P2D_FILL_POLY);
    TxMsgPut(nbPoint);
    while(nbPoint != 0) {
      TxMsgPut(points->x);
      TxMsgPut(points->y);
      points++;
      nbPoint--;
    }
  }
}

/* P2D_SpriteGetWidth TODO
 * ARG: img(u8)*/
length_t R_P2D_SpriteGetWidth(gui_img_t img) {
  return 0;
}

/* P2D_SpriteGetHeight TODO
 * ARG: img(u8)*/
length_t R_P2D_SpriteGetHeight(gui_img_t img) {
  return 0;
}

/* SetLut
 * ARG: lut(u8)*/
void R_SetLut(uint8_t lut) {
  TxMsgPutByte(OP_P2D_SET_LUT);
  TxMsgPut(lut);
}

/* Sprite
 * ARG: x(i16) y(i16) img(u8)*/
void R_Sprite(coord_t x, coord_t y, gui_img_t img) {
  TxMsgPutByte(OP_P2D_SPRITE);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPut(img);
}
