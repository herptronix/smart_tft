/**
 * @file p2d_base.h
 * @brief p2d minimalist functions
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
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

#ifndef _p2d_base_h_
#define _p2d_base_h_

#include "p2d.h"

/**
 * @enum line_t LINE_SOLID: continuous line
 * @enum line_t LINE_DOT: one pixel on, one pixel off
 */
typedef enum {
  LINE_SOLID,
  LINE_DOT
} line_t;

/**
 * @enum dmode_t DISPLAY_SOLID: put all pixels
 * @enum dmode_t DISPLAY_TRANSPARENT: do not put colorkey'd pixels
 */
typedef enum {
  DISPLAY_SOLID = 0x00,
  DISPLAY_TRANSPARENT = 0x01
} dmode_t;


/**
 * @function P2D_Init
 * @brief initializes the 2D primitives library; Shall be called first.
 * @param none
 * @return none
 */
void P2D_Init(void);

/**
 * @function P2D_GetLcdWidth
 * @brief return the width of the physical screen
 * @param none
 * @return length_t: total width (in pixel) of the screen
 */
length_t P2D_GetLcdWidth(void);

/**
 * @function P2D_GetLcdHeight
 * @brief return the height of the physical screen
 * @param none
 * @return length_t: total height (in pixel) of the screen
 */
length_t P2D_GetLcdHeight(void);

/**
 * @function P2D_SetColor
 * @brief set the front color for next operations
 * @param color_t front: new color
 * @return none
 */
void P2D_SetColor(color_t front);

/**
 * @function P2D_SetColors
 * @brief set the front & background colors for next operations
 * @param color_t front, back: new front & background colors
 * @return none
 */
void P2D_SetColors(color_t front, color_t back);

/**
 * @function P2D_SetDisplayMode
 * @brief set the display mode for next operations
 * @param m: new mode (DISPLAY_SOLID / DISPLAY_TRANSPARENT)
 * @return none
 */
void P2D_SetDisplayMode(dmode_t m);

/**
 * @function P2D_SetAlpha
 * @brief set the alpha level for next operations
 * @param a: new alpha (from 0 to 255; 0 = fully transparent, 255 = fully opaque)
 * @return none
 */
void P2D_SetAlpha(uint8_t a);

/**
 * @function P2D_SetLineType
 * @brief sets the line type (solid line, dotted line)
 * @param line_t: line type
 * @return none
 */
void P2D_SetLineType(line_t type);

/**
 * @function P2D_SetPixel
 * @brief Put a pixel on current surface
 * @param coord_t x: position x, in pixels
 * @param coord_t y: position y; in pixels
 * @param color_t col: color
 * @return none
 */
void P2D_SetPixel(coord_t x, coord_t y, color_t col);

/**
 * @function P2D_Clear
 * @brief clears the current surface within the current clip
 * @param none
 * @return none
 */
void P2D_Clear(void);

/**
 * @function P2D_Line
 * @brief draw a 2D line
 * @param x0, y0: start point
 * @param x1, y1: end point
 * @return none
 */
void P2D_Line(coord_t x0, coord_t y0, coord_t x1, coord_t y1);

/**
 * @function P2D_Rect
 * @brief draw a rectangle
 * @param const rect_st *rec: rectangle parameters
 * @return none
 */
void P2D_Rect(const rect_st *rec);

/**
 * @function P2D_FillRect
 * @brief draw a filled rectangle
 * @param const rect_st *rec: rectangle parameters
 * @return none
 */
void P2D_FillRect(const rect_st *rec);

#endif
