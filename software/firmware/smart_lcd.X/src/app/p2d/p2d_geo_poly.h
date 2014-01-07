/**
 * @file p2d_geo_poly.h
 * @brief p2d polygon
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
 *
 * Implementation of filled polygon is inspired from http://alienryderflex.com/polygon_fill/
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

#ifndef _p2d_geo_poly_h_
#define _p2d_geo_poly_h_

#include "p2d.h"

typedef struct {
  coord_t x, y;
} point_st;

/**
 * @function P2D_P_Copy
 * @brief Copy an array of point into another given array
 * @param const point_st *src: source array
 * @param point_st *dst: destination array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_P_Copy(const point_st *src, point_st *dst, uint8_t nbPoint);

/**
 * @function P2D_P_Move
 * @brief Move all points of an array
 * @param point_st *arPoints: array of points; content will be overwritten
 * @param uint8_t nbPoint: number of points
 * @param coord_t mvX, mvY: x & y moves, for each points
 * @return none
 */
void P2D_P_Move(point_st *arPoints, uint8_t nbPoint, coord_t mvX, coord_t mvY);

/**
 * @function P2D_P_Zoom
 * @brief Zoom all points of an array according to a reference point
 * @param point_st *arPoints: array of points; content will be overwritten
 * @param uint8_t nbPoint: number of points
 * @param const point_st *ref: reference point
 * @param uint8_t zoomPercent: zoom, in percent;
 *     1 -> zoom = 0.01
 *   100 -> unchanged points;
 *   255 -> zoom = 2.55
 * @return none
 */
void P2D_P_Zoom(point_st *arPoints, uint8_t nbPoint, const point_st *ref, uint8_t zoomPercent);

/**
 * @function P2D_P_Rotate
 * @brief Rotate all points of an array around a reference point
 * @param point_st *arPoints: array of points; content will be overwritten
 * @param uint8_t nbPoint: number of points
 * @param const point_st *ref: reference point
 * @param uint16_t deg: rotation, in degrees
 * @return none
 */
void P2D_P_Rotate(point_st *arPoints, uint8_t nbPoint, const point_st *ref, uint16_t deg);

/**
 * @function P2D_FindPolyCenter
 * @brief Find the center of a polygon
 * @param const point_st *arPoints: array of points composing the polygon
 * @param uint8_t nbPoint: number of points
 * @param point_st *center: output
 * @return none
 */
void P2D_FindPolyCenter(const point_st *arPoints, uint8_t nbPoint, point_st *center);

/**
 * @function P2D_Poly
 * @brief draw a polygon
 * @param const point_st *arPoints: points array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_Poly(const point_st *arPoints, uint8_t nbPoint);

/**
 * @function P2D_FillPoly
 * @brief draw a filled polygon
 * @param const point_st *arPoints: points array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_FillPoly(const point_st *arPoints, uint8_t nbPoint);

#endif
