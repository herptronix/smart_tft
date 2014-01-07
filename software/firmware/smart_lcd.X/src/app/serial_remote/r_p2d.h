/**
 * @file r_p2d.h
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

#ifndef _r_p2d_h_
#define _r_p2d_h_

#include "main.h"

int8_t R_P2D_Clear(void);
int8_t R_P2D_SetColor(void);
int8_t R_P2D_SetColors(void);
int8_t R_P2D_SetDisplayMode(void);
int8_t R_P2D_P2D_SetAlpha(void);
int8_t R_P2D_SetLineType(void);
int8_t R_P2D_SetPixel(void);
int8_t R_P2D_Line(void);
int8_t R_P2D_Rect(void);
int8_t R_P2D_FillRect(void);
int8_t R_P2D_SetClip(void);
int8_t R_P2D_GetLcdWidth(void);
int8_t R_P2D_GetLcdHeight(void);
int8_t R_P2D_SetFont(void);
int8_t R_P2D_GetTextHeight(void);
int8_t R_P2D_GetTextWidth(void);
int8_t R_P2D_GetGlyphWidth(void);
int8_t R_P2D_PutGlyph(void);
int8_t R_P2D_PutText(void);
int8_t R_P2D_Circle(void);
int8_t R_P2D_FillCircle(void);
int8_t R_P2D_Poly(void);
int8_t R_P2D_FillPoly(void);
int8_t R_P2D_SpriteGetWidth(void);
int8_t R_P2D_SpriteGetHeight(void);
int8_t R_SetLut(void);
int8_t R_Sprite(void);

#endif
