/**
 * @file p2d_geo_poly.c
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

#include "p2d_internal.h"

#define INTER_LIST_SIZE 16	/*maximum number of intersection per scanned line*/

/*
 * Local functions
 */
static void FindPolyLimits(const point_st *pts, uint8_t nbPoint, coord_t *yMin, coord_t *yMax);
static uint8_t FindIntersection(const point_st *pts, uint8_t nbPoint, coord_t y, coord_t *xList, uint8_t listSize);
static void SortIntersection(coord_t *xList, uint8_t listSize);



/**
 * @function P2D_P_Copy
 * @brief Copy an array of point into another given array
 * @param const point_st *src: source array
 * @param point_st *dst: destination array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_P_Copy(const point_st *src, point_st *dst, uint8_t nbPoint) {
  if(src != NULL && dst != NULL) {
    while(nbPoint) {
      *dst = *src;
      dst++;
      src++;
      nbPoint--;
    }
  }
}


/**
 * @function P2D_P_Move
 * @brief Move all points of an array
 * @param point_st *arPoints: array of points; content will be overwritten
 * @param uint8_t nbPoint: number of points
 * @param coord_t mvX, mvY: x & y moves, for each points
 * @return none
 */
void P2D_P_Move(point_st *arPoints, uint8_t nbPoint, coord_t mvX, coord_t mvY) {
  if(arPoints != NULL) {
    while(nbPoint) {
      arPoints->x += mvX;
      arPoints->y += mvY;
      arPoints++;
      nbPoint--;
    }
  }
}


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
void P2D_P_Zoom(point_st *arPoints, uint8_t nbPoint, const point_st *ref, uint8_t zoomPercent) {

  int32_t dist;
  if(arPoints != NULL && ref != NULL && zoomPercent > 0) {

    while(nbPoint) {

      dist = arPoints->x - ref->x;
      dist = (dist * zoomPercent) / 100;
      arPoints->x = (coord_t) (dist + ref->x);

      dist = arPoints->y - ref->y;
      dist = (dist * zoomPercent) / 100;
      arPoints->y = (coord_t) (dist + ref->y);

      arPoints++;
      nbPoint--;
    }
  }
}


/**
 * @function P2D_P_Rotate
 * @brief Rotate all points of an array around a reference point
 * @param point_st *arPoints: array of points; content will be overwritten
 * @param uint8_t nbPoint: number of points
 * @param const point_st *ref: reference point
 * @param uint16_t deg: rotation, in degrees
 * @return none
 */
void P2D_P_Rotate(point_st *arPoints, uint8_t nbPoint, const point_st *ref, uint16_t deg) {

  int32_t rx, ry, dx, dy, cos, sin;
  if(arPoints != NULL && ref != NULL) {

    cos = P2D_Cos(deg);
    sin = P2D_Sin(deg);

    while(nbPoint) {

      dx = arPoints->x - ref->x;
      dy = arPoints->y - ref->y;
      rx = (cos * dx - sin * dy) / P2D_G_DIV;
      ry = (sin * dx + cos * dy) / P2D_G_DIV;

      arPoints->x = ref->x + (coord_t) rx;
      arPoints->y = ref->y + (coord_t) ry;

      arPoints++;
      nbPoint--;
    }
  }
}


/**
 * @function P2D_FindPolyCenter
 * @brief Find the center of a polygon
 * @param const point_st *arPoints: array of points composing the polygon
 * @param uint8_t nbPoint: number of points
 * @param point_st *center: output
 * @return none
 */
void P2D_FindPolyCenter(const point_st *arPoints, uint8_t nbPoint, point_st *center) {

  uint8_t p1, p2;
  int32_t a, x0, y0, x1, y1, area, cx, cy;

  if(arPoints != NULL && center != NULL && nbPoint >= 3) {

    area = 0;
    cx = 0;
    cy = 0;

    p2 = nbPoint - 1;
    for(p1 = 0; p1 < nbPoint; p1++) {
      x0 = arPoints[p2].x;
      y0 = arPoints[p2].y;
      x1 = arPoints[p1].x;
      y1 = arPoints[p1].y;
      a = x0 * y1 - x1 * y0;
      area += a;
      cx += (x0 + x1) * a;
      cy += (y0 + y1) * a;
      p2 = p1;
    }

    area = 3 * area;
    cx = cx / area;
    cy = cy / area;

    center->x = (coord_t) cx;
    center->y = (coord_t) cy;
  }
}


/**
 * @function P2D_Poly
 * @brief draw a polygon
 * @param const point_st *arPoints: points array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_Poly(const point_st *arPoints, uint8_t nbPoint) {

  uint8_t p1, p2;

  if(arPoints != NULL && nbPoint >= 3) {

    p2 = nbPoint - 1;
    for(p1 = 0; p1 < nbPoint; p1++) {

      P2D_Line(arPoints[p1].x, arPoints[p1].y, arPoints[p2].x, arPoints[p2].y);
      p2 = p1;
    }
  }
}


/**
 * @function P2D_FillPoly
 * @brief draw a filled polygon
 * @param const point_st *arPoints: points array
 * @param uint8_t nbPoint: number of points
 * @return none
 */
void P2D_FillPoly(const point_st *arPoints, uint8_t nbPoint) {

  coord_t y, yMin, yMax;
  coord_t xList[INTER_LIST_SIZE];
  uint8_t ii, nbIntersection;
  line_t lineType;

  if(arPoints != NULL && nbPoint >= 3) {

    /*force SOLID line*/
    lineType = context.lineType;
    context.lineType = LINE_SOLID;

    /*retrieve Y min & max coord of the polygon*/
    FindPolyLimits(arPoints, nbPoint, &yMin, &yMax);

    //TODO: reduce yMin/yMax to the current Clip (optional, for faster processing with Clip)

    /*scan each line*/
    for(y = yMin; y <= yMax; y++) {

      /*find all intersections of the current line*/
      nbIntersection = FindIntersection(arPoints, nbPoint, y, xList, INTER_LIST_SIZE);

      if(nbIntersection >= 2) {

        /*sort intersection list, from lower to higher*/
        SortIntersection(xList, nbIntersection);

        /*drawing lines between each intersection pairs*/
        for(ii = 0; ii < nbIntersection; ii += 2) {
          P2D_Line(xList[ii], y, xList[ii+1], y);
        }
      }
    }

    P2D_Poly(arPoints, nbPoint);

    context.lineType = lineType;
  }
}


/**
 * @function FindPolyLimits
 * @brief find minimal & maximal y value of the polygon
 * @param const point_st *pts: points array
 * @param uint8_t nbPoint: number of points
 * @param coord_t *yMin, coord_t *yMax: output
 * @return none
 */
static void FindPolyLimits(const point_st *pts, uint8_t nbPoint, coord_t *yMin, coord_t *yMax) {
  uint8_t ii;
  *yMin = pts[0].y;
  *yMax = pts[0].y;
  for(ii = 1; ii < nbPoint; ii++) {
    if(pts[ii].y < *yMin) *yMin = pts[ii].y;
    if(pts[ii].y > *yMax) *yMax = pts[ii].y;
  }
}


/**
 * @function FindIntersection
 * @brief build the intersection list of the current line
 * @param const point_st *pts: points array
 * @param uint8_t nbPoint: number of points
 * @param coord_t y: current scanned line
 * @param coord_t *xList: output list
 * @param uint8_t listSize: maximum list size
 * @return none
 */
static uint8_t FindIntersection(const point_st *pts, uint8_t nbPoint, coord_t y, coord_t *xList, uint8_t listSize) {

  uint8_t p1, p2;
  uint8_t nbInter;
  coord_t x1, y1, x2, y2, x;

  /*looks for intersection between 2 consecutive points only*/
  nbInter = 0;
  p2 = nbPoint - 1;
  for(p1 = 0; p1 < nbPoint && nbInter < listSize; p1++) {

    y1 = pts[p1].y;
    y2 = pts[p2].y;

    /*intersection if: current y line is between 2 points*/
    if((y1 < y && y2 >= y) || (y2 < y && y1 >= y)) {

      x1 = pts[p1].x;
      x2 = pts[p2].x;

      x = (y - y1) * (x2 - x1) / (y2 - y1); /*relative x*/
      xList[nbInter] = x1 + x; /*absolute x*/

      nbInter++;
    }

    p2 = p1;
  }

  return nbInter;
}


/**
 * @function SortIntersection
 * @brief sort the list (increasing order)
 * @param coord_t *xList: list to sort (in & out)
 * @param uint8_t listSize: list size
 * @return none
 */
static void SortIntersection(coord_t *xList, uint8_t listSize) {

  uint8_t ii = 0;
  coord_t tmp;

  if(listSize >= 2) {
    while(ii < listSize - 1) {
      if(xList[ii] > xList[ii + 1]) {
        tmp = xList[ii];
        xList[ii] = xList[ii + 1];
        xList[ii + 1] = tmp;
        if(ii > 0) ii--;
      }
      else {
        ii++;
      }
    }
  }
}
