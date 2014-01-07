/**
 * @file p2d_base.c
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


#include "p2d_internal.h"


/**
 * @function P2D_Init
 * @brief initializes the 2D primitives library; Shall be called first.
 * @param none
 * @return none
 */
void P2D_Init(void) {

  /*set LCD as current surface*/
  P2D_SurfaceInit();

  /*set context*/
  P2D_SetDisplayMode(DISPLAY_SOLID);
  P2D_SetColors(COLOR_BLACK, COLOR_BLACK);
  P2D_SetAlpha(255);
  P2D_SetLineType(LINE_SOLID);
  P2D_SetFont(NULL);

  /*clear screen*/
  P2D_SetClip(NULL);
  P2D_Clear();
}


/**
 * @function P2D_GetLcdWidth
 * @brief return the width of the physical screen
 * @param none
 * @return length_t: total width (in pixel) of the screen
 */
length_t P2D_GetLcdWidth(void) {
  return LCD_GetWidth();
}


/**
 * @function P2D_GetLcdHeight
 * @brief return the height of the physical screen
 * @param none
 * @return length_t: total height (in pixel) of the screen
 */
length_t P2D_GetLcdHeight(void) {
  return LCD_GetHeight();
}


/**
 * @function P2D_SetColor
 * @brief set the front color for next operations
 * @param color_t front: new color
 * @return none
 */
void P2D_SetColor(color_t front) {
  context.colFront = front;
}


/**
 * @function P2D_SetColors
 * @brief set the front & background colors for next operations
 * @param color_t front, back: new front & background colors
 * @return none
 */
void P2D_SetColors(color_t front, color_t back) {
  context.colFront = front;
  context.colBackgrnd = back;
}


/**
 * @function P2D_SetDisplayMode
 * @brief set the display mode for next operations
 * @param m: new mode (DISPLAY_SOLID / DISPLAY_TRANSPARENT)
 * @return none
 */
void P2D_SetDisplayMode(dmode_t m) {
  context.mode = m;
}


/**
 * @function P2D_SetAlpha
 * @brief set the alpha level for next operations
 * @param a: new alpha (from 0 to 255; 0 = fully transparent, 255 = fully opaque)
 * @return none
 */
void P2D_SetAlpha(uint8_t a) {
  context.alpha = a;
}


/**
 * @function P2D_SetLineType
 * @brief sets the line type (solid line, dotted line)
 * @param line_t: line type
 * @return none
 */
void P2D_SetLineType(line_t type) {
  context.lineType = type;
}


/**
 * @function P2D_SetPixel
 * @brief Put a pixel on current surface
 * @param coord_t x: position x, in pixels
 * @param coord_t y: position y; in pixels
 * @param color_t col: color
 * @return none
 */
void P2D_SetPixel(coord_t x, coord_t y, color_t col) {
  if(P2D_IsCoordInClip(x, y) == true) {
    SetPos(x, y);
    Put(col);
  }
}


/**
 * @function P2D_Clear
 * @brief clears the current surface within the current clip
 * @param none
 * @return none
 */
void P2D_Clear(void) {
  rect_st lrect;
  lrect.x = 0;
  lrect.y = 0;
  lrect.w = GetWidth();
  lrect.h = GetHeight();
  P2D_FillRect(&lrect);
}


/**
 * @function P2D_Line
 * @brief draw a 2D line
 * @param x0, y0: start point
 * @param x1, y1: end point
 * @return none
 */
void P2D_Line(coord_t x0, coord_t y0, coord_t x1, coord_t y1) {

  rect_st lrect;

  /*optimized procedure for horizontal line*/
  if(context.lineType == LINE_SOLID && y0 == y1) {
    lrect.x = P2D_CoordGetMin(x0, x1);
    lrect.y = P2D_CoordGetMin(y0, y1);
    lrect.w = P2D_GetLengthBtwnCoord(x0, x1);
    lrect.h = 1;
    P2D_FillRect(&lrect);
  }
  /*optimized procedure for vertical line*/
  else if(context.lineType == LINE_SOLID && x0 == x1) {
    lrect.x = P2D_CoordGetMin(x0, x1);
    lrect.y = P2D_CoordGetMin(y0, y1);
    lrect.w = 1;
    lrect.h = P2D_GetLengthBtwnCoord(y0, y1);
    P2D_FillRect(&lrect);
  }
  /*else (dashed vertical line, random line, ...), put pixel per pixel -> slower*/
  else {
    P2D_Gline(x0, y0, x1, y1);
  }
}


/**
 * @function P2D_Rect
 * @brief draw a rectangle
 * @param const rect_st *rec: rectangle parameters
 * @return none
 */
void P2D_Rect(const rect_st *rec) {
  coord_t x0, y0, x1, y1;
  if(P2D_RectToCoord(rec, &x0, &y0, &x1, &y1) == 0) {
    P2D_Line(x0, y0, x1, y0);
    P2D_Line(x0, y0, x0, y1);
    P2D_Line(x0, y1, x1, y1);
    P2D_Line(x1, y0, x1, y1);
  }
}


/**
 * @function P2D_FillRect
 * @brief draw a filled rectangle
 * @param const rect_st *rec: rectangle parameters
 * @return none
 */
void P2D_FillRect(const rect_st *rec) {
  rect_st lrect;
  uint32_t pxCnt;

  if(rec != NULL) {
    lrect = *rec;
    P2D_ClipFit(&lrect);
    pxCnt = P2D_GetPixelCnt(&lrect);

    if(pxCnt > 0) {
      SetWnd(&lrect);
      while(pxCnt-- > 0) Put(context.colFront);
      SetWnd(NULL); /*always restore full screen window*/
    }
  }
}
