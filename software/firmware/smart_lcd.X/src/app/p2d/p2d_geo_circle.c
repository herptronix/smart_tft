/**
 * @file p2d_geo_circle.c
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

#include "p2d_internal.h"


/**
 * @function P2D_Circle
 * @brief draw a circle
 * @param coord_t x0, coord_t y0: center coordinate
 * @param length_t radius: radius
 * @return none
 */
void P2D_Circle(coord_t x0, coord_t y0, length_t radius) {

  coord_t x, y, err, r;

  r = radius;
  x = -r;
  y = 0;
  err = 2 - 2 * r;

  /*classic mid-point algorithm*/
  do {

    P2D_SetPixel(x0-x, y0+y, context.colFront);
    P2D_SetPixel(x0-y, y0-x, context.colFront);
    P2D_SetPixel(x0+x, y0-y, context.colFront);
    P2D_SetPixel(x0+y, y0+x, context.colFront);

    r = err;
    if (r <= y) {
      y++;
      err += y * 2 + 1;
    }
    if (r > x || err > y) {
      x++;
      err += x * 2 + 1;
    }
  } while (x < 0);
}


/**
 * @function P2D_FillCircle
 * @brief draw a filled circle
 * @param coord_t x0, coord_t y0: center coordinate
 * @param length_t radius: radius
 * @return none
 */
void P2D_FillCircle(coord_t x0, coord_t y0, length_t radius) {

  coord_t x, y, err, r;
  line_t lineType;

  /*save line context*/
  lineType = context.lineType;
  context.lineType = LINE_SOLID;

  r = radius;
  x = -r;
  y = 0;
  err = 2 - 2 * r;

  /*classic mid-point algorithm, but using line() between quadrant of instead pixel()*/
  do {
    P2D_Line(x0-x, y0+y, x0+x, y0+y);
    P2D_Line(x0-x, y0-y, x0+x, y0-y);

    r = err;
    if (r <= y) {
      y++;
      err += y * 2 + 1;
    }
    if (r > x || err > y) {
      x++;
      err += x * 2 + 1;
    }
  } while (x < 0);

  /*restore line context*/
  context.lineType = lineType;
}
