/**
 * @file p2d_utils.c
 * @brief p2d utils
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
 * @function P2D_GetPixelCnt
 * @brief return the number of pixels contained in a given rect
 * @param const rect_st *rec: input rectangle
 * @return uint32_t: number of pixels
 */
uint32_t P2D_GetPixelCnt(const rect_st /*@null@*/ *rec) {
  uint32_t cnt = 0;
  if(rec != NULL) cnt = rec->w * rec->h;
  return cnt;
}


/**
 * @function P2D_GetLengthBtwnCoord
 * @brief return the number of pixels between 2 points of a same line / row;
 *   example: length between x1=10 and x2=13 is 4 (|x1-x2|+1: there are 4 pixels between 10 & 13)
 * @param coord_t p0, p1: coord to compare
 * @return length_t: number of pixels between the 2 points
 */
length_t P2D_GetLengthBtwnCoord(coord_t p0, coord_t p1) {
  length_t len;
  if      (p0 > p1) len = p0 - p1 + 1;
  else if (p0 < p1) len = p1 - p0 + 1;
  else              len = 1;
  return len;
}


/**
 * @function P2D_CoordGetMin
 * @brief return the lower value between two coord_t
 * @param coord_t p0, p1: coord to compare
 * @return coord_t: the lower coord_t
 */
coord_t P2D_CoordGetMin(coord_t p0, coord_t p1) {
  coord_t min;
  if(p0 < p1) min = p0;
  else min = p1;
  return min;
}


/**
 * @function P2D_CoordGetMax
 * @brief returns the higher value between two coord_t
 * @param coord_t p0, p1: coord to compare
 * @return coord_t: the higher coord_t
 */
coord_t P2D_CoordGetMax(coord_t p0, coord_t p1) {
  coord_t max;
  if(p0 > p1) max = p0;
  else max = p1;
  return max;
}


/**
 * @function P2D_CoordGetDelta
 * @brief returns |p0 - p1|
 * @param coord_t p0, p1: coord to diff
 * @return coord_t: |p0 - p1|
 */
coord_t P2D_CoordGetDelta(coord_t p0, coord_t p1) {
  coord_t delta;
  delta = P2D_CoordGetMax(p0, p1) - P2D_CoordGetMin(p0, p1);
  return delta;
}


/**
 * @function P2D_IsInClip
 * @brief checks if a point is into a given rectangle
 * @param const rect_st *clip: input rectangle
 * @param coord_t x0, y0: point coordinates
 * @return true if the point is in the rectangle, false otherwise
 */
bool P2D_IsInClip(const rect_st /*@null@*/ *clip, coord_t x, coord_t y) {
  bool res = false;
  if(clip != NULL &&
      x >= clip->x && x < clip->w + clip->x &&
       y >= clip->y && y < clip->h + clip->y) res = true;
  return res;
}


/**
 * @function P2D_RectToCoord
 * @brief converts a rect into absolute coordinates
 * @param const rect_st *rec: input rectangle
 * @param coord_t *x0, *y0, *x1, *y1: output coordinates
 * @return 0: ok, -1: error (from NULL input pointer, or rec->w / rec->h == 0)
 */
int8_t P2D_RectToCoord(const rect_st *rec, coord_t /*@out@*/ *x0, coord_t /*@out@*/ *y0, coord_t /*@out@*/ *x1, coord_t /*@out@*/ *y1) {
  int8_t res = -1;
  if(rec != NULL && x0 != NULL && y0 != NULL && x1 != NULL && y1 != NULL &&
      rec->w > 0 && rec->h > 0) {
    *x0 = rec->x;
    *y0 = rec->y;
    *x1 = *x0 + rec->w - 1;
    *y1 = *y0 + rec->h - 1;
    res = 0;
  }
  return res;
}


/**
 * @function P2D_CoordToRect
 * @brief converts absolute coordinates into a rect
 * @param rect_st *rec: output rectangle
 * @param coord_t x0, y0, x1, y1: input coordinates
 * @return 0: ok, -1: error (from NULL input pointer)
 */
int8_t P2D_CoordToRect(rect_st /*@out@*/ *rec, coord_t x0, coord_t y0, coord_t x1, coord_t y1) {
  int8_t res = -1;
  if(rec != NULL) {
    rec->x = P2D_CoordGetMin(x0, x1);
    rec->y = P2D_CoordGetMin(y0, y1);
    rec->w = P2D_GetLengthBtwnCoord(x0, x1);
    rec->h = P2D_GetLengthBtwnCoord(y0, y1);
    res = 0;
  }
  return res;
}
