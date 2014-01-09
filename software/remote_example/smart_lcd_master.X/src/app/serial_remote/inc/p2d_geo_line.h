/**
 * @file p2d_geo_line.h
 * @brief p2d line (continuous & dashed), using Bresenham's line algorithm
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

#ifndef _p2d_geo_line_h_
#define _p2d_geo_line_h_

#include "p2d.h"

/**
 * @function P2D_Gline
 * @brief draw a line
 * @param coord_t x0, coord_t y0: point 0
 * @param coord_t x1, coord_t y1: point 1
 * @return none
 */
void P2D_Gline(coord_t x0, coord_t y0, coord_t x1, coord_t y1);

#endif
