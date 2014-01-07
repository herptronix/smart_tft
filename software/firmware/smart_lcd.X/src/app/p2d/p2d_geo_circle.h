/**
 * @file p2d_geo_circle.h
 * @brief p2d circle, using mid-point algorithm
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
#ifndef _p2d_geo_circle_h_
#define _p2d_geo_circle_h_

#include "p2d.h"

/**
 * @function P2D_Circle
 * @brief draw a circle
 * @param coord_t x0, coord_t y0: center coordinate
 * @param length_t radius: radius
 * @return none
 */
void P2D_Circle(coord_t x0, coord_t y0, length_t radius);

/**
 * @function P2D_FillCircle
 * @brief draw a filled circle
 * @param coord_t x0, coord_t y0: center coordinate
 * @param length_t radius: radius
 * @return none
 */
void P2D_FillCircle(coord_t x0, coord_t y0, length_t radius);

#endif
