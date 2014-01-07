/**
 * @file p2d_utils.h
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

#ifndef _p2d_utils_h_
#define _p2d_utils_h_

#include "p2d.h"

/**
 * @function P2D_GetPixelCnt
 * @brief return the number of pixels contained in a given rect
 * @param const rect_st *rec: input rectangle
 * @return uint32_t: number of pixels
 */
uint32_t P2D_GetPixelCnt(const rect_st /*@null@*/ *rec);

/**
 * @function P2D_GetLengthBtwnCoord
 * @brief return the number of pixels between 2 points of a same line / row;
 *   example: length between x1=10 and x2=13 is 4 (|x1-x2|+1: there are 4 pixels between 10 & 13)
 * @param coord_t p0, p1: coord to compare
 * @return length_t: number of pixels between the 2 points
 */
length_t P2D_GetLengthBtwnCoord(coord_t p0, coord_t p1);

/**
 * @function P2D_CoordGetMin
 * @brief return the lower value between two coord_t
 * @param coord_t p0, p1: coord to compare
 * @return coord_t: the lower coord_t
 */
coord_t P2D_CoordGetMin(coord_t p0, coord_t p1);

/**
 * @function P2D_CoordGetMax
 * @brief returns the higher value between two coord_t
 * @param coord_t p0, p1: coord to compare
 * @return coord_t: the higher coord_t
 */
coord_t P2D_CoordGetMax(coord_t p0, coord_t p1);

/**
 * @function P2D_CoordGetDelta
 * @brief returns |p0 - p1|
 * @param coord_t p0, p1: coord to diff
 * @return coord_t: |p0 - p1|
 */
coord_t P2D_CoordGetDelta(coord_t p0, coord_t p1);

/**
 * @function P2D_IsInClip
 * @brief checks if a point is into a given rectangle
 * @param const rect_st *clip: input rectangle
 * @param coord_t x0, y0: point coordinates
 * @return true if the point is in the rectangle, false otherwise
 */
bool P2D_IsInClip(const rect_st /*@null@*/ *clip, coord_t x, coord_t y);

/**
 * @function P2D_RectToCoord
 * @brief converts a rect into absolute coordinates
 * @param const rect_st *rec: input rectangle
 * @param coord_t *x0, *y0, *x1, *y1: output coordinates
 * @return 0: ok, -1: error (from NULL input pointer, or rec->w / rec->h == 0)
 */
int8_t P2D_RectToCoord(const rect_st *rec, coord_t /*@out@*/ *x0, coord_t /*@out@*/ *y0, coord_t /*@out@*/ *x1, coord_t /*@out@*/ *y1);

/**
 * @function P2D_CoordToRect
 * @brief converts absolute coordinates into a rect
 * @param rect_st *rec: output rectangle
 * @param coord_t x0, y0, x1, y1: input coordinates
 * @return 0: ok, -1: error (from NULL input pointer)
 */
int8_t P2D_CoordToRect(rect_st /*@out@*/ *rec, coord_t x0, coord_t y0, coord_t x1, coord_t y1);

#endif
