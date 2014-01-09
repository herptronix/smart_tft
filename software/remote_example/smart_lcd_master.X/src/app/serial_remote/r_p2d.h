/**
 * @file r_p2d.h
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

#ifndef _r_p2d_h_
#define _r_p2d_h_

#include "tft_defines.h"
#include "opList.h"


void      R_P2D_Clear(void);
void      R_P2D_SetColor(color_t front);
void      R_P2D_SetColors(color_t front, color_t back);
void      R_P2D_SetDisplayMode(dmode_t mode);
void      R_P2D_P2D_SetAlpha(uint8_t alpha);
void      R_P2D_SetLineType(line_t lineType);
void      R_P2D_SetPixel(coord_t x, coord_t y, color_t color);
void      R_P2D_Line(coord_t x0, coord_t y0, coord_t x1, coord_t y1);
void      R_P2D_Rect(const rect_st *rec);
void      R_P2D_FillRect(const rect_st *rec);
void      R_P2D_SetClip(const rect_st *rec);
length_t  R_P2D_GetLcdWidth(void);
length_t  R_P2D_GetLcdHeight(void);
void      R_P2D_SetFont(gui_font_t font);
length_t  R_P2D_GetTextHeight(void);
length_t  R_P2D_GetTextWidth(const void *str);
length_t  R_P2D_GetGlyphWidth(void);
void      R_P2D_PutGlyph(coord_t x, coord_t y, uint8_t glyph);
void      R_P2D_PutText(coord_t x, coord_t y, const void *str);
void      R_P2D_Circle(coord_t x, coord_t y, length_t rad);
void      R_P2D_FillCircle(coord_t x, coord_t y, length_t rad);
void      R_P2D_Poly(uint8_t nbPoint, const point_st *points);
void      R_P2D_FillPoly(uint8_t nbPoint, const point_st *points);
length_t  R_P2D_SpriteGetWidth(gui_img_t img);
length_t  R_P2D_SpriteGetHeight(gui_img_t img);
void      R_SetLut(uint8_t lut);
void      R_Sprite(coord_t x, coord_t y, gui_img_t img);

#endif
