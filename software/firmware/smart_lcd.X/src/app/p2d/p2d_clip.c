/**
 * @file p2d_clip.c
 * @brief p2d clip managemet
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
 * @function P2D_ClipFit
 * @brief modify a given clip in order to fit it in the global clip
 * @param rect_st *toClip
 * @return none
 */
void P2D_ClipFit(rect_st *toClip) {
  P2D_Clip(toClip, &context.clip);
}


/**
 * @function P2D_IsCoordInClip
 * @brief check if a given point is within the global clip
 * @param coord_t x, coord_t y: point coordinate
 * @return bool: true -> the point is within the global clip, false otherwise
 */
bool P2D_IsCoordInClip(coord_t x, coord_t y) {
  return P2D_IsInClip(&context.clip, x, y);
}


/**
 * @function P2D_SetClip
 * @brief define the global clip
 * @param const rect_st *rec: new global clip; clip is checked to ensure that it fits in the physical surface dimension
 * @return none
 */
void P2D_SetClip(const rect_st *rec) {

  rect_st dimRect;
  dimRect.x = 0;
  dimRect.y = 0;
  dimRect.w = GetWidth();
  dimRect.h = GetHeight();

  if(rec == NULL || rec->w == 0 || rec->h == 0) { /*if invalid clip, expand it to the surface dimension*/
    context.clip = dimRect;
  }
  else {
    context.clip = *rec;
    P2D_Clip(&context.clip, &dimRect); /*always clip to the REAL surface dimensions*/
  }
}


/**
 * @function P2D_Clip
 * @brief modify a given clip (src) in order to fit it in another given clip (dst)
 * @param rect_st *src: clip to fit
 * @param const rect_st *dst: reference
 * @return none
 */
void P2D_Clip(rect_st *src, const rect_st *dst) {

  coord_t sx0, sx1, sy0, sy1;
  coord_t dx0, dx1, dy0, dy1;
  bool bValidRect;

  if(src != NULL && dst != NULL) {

    bValidRect = false;

    do {

      /*transform the source rect into absolute coordinates*/
      if(P2D_RectToCoord(src, &sx0, &sy0, &sx1, &sy1) < 0) break;

      /*transform the destination rect into absolute coordinates*/
      if(P2D_RectToCoord(dst, &dx0, &dy0, &dx1, &dy1) < 0) break;

      /*clip adjustment*/
      if      (sx0 < dx0) sx0 = dx0;
      else if (sx0 > dx1) break;
      if      (sy0 < dy0) sy0 = dy0;
      else if (sy0 > dy1) break;
      if      (sx1 > dx1) sx1 = dx1;
      else if (sx1 < dx0) break;
      if      (sy1 > dy1) sy1 = dy1;
      else if (sy1 < dy0) break;

      /*at this point, the clip represented by sx0, sx1, sy0, sy1 is valid*/
      bValidRect = true;

    } while(0);

    if(bValidRect == false) {
      src->x = 0;
      src->y = 0;
      src->w = 0;
      src->h = 0;
    }
    else {
      src->x = sx0;
      src->y = sy0;
      src->w = P2D_GetLengthBtwnCoord(sx0, sx1);
      src->h = P2D_GetLengthBtwnCoord(sy0, sy1);
    }
  }
}


/**
 * @function P2D_ClipBitBlt
 * @brief compute a bitblt clip on 2 given clip (*src & *dst), save results into *lsrc & *ldst
 * @param const rect_st *srcDim: source dimension (absolute)
 * @param const rect_st *src: desired source clip
 * @param const rect_st *dst: desired destination clip
 * @param rect_st *lsrc: output source clip
 * @param rect_st *ldst: output destination clip
 * @return uint32_t: number of pixel composing clipped destination
 */
uint32_t P2D_ClipBitBlt(const rect_st *srcDim, const rect_st *src, const rect_st *dst, rect_st *lsrc, rect_st *ldst) {

  uint32_t pxCnt = 0;
  coord_t delta;

  /* 1 - handle source rect*/

  /*if scr NULL, just display the whole src surface*/
  if(src == NULL) {
    *lsrc = *srcDim;
  }
  /*else, ensure that source rect fits in src surface dimensions*/
  else {
    *lsrc = *src;
    P2D_Clip(lsrc, srcDim);
  }

  /* 2 - continue, only if there is something to display*/
  if(P2D_GetPixelCnt(lsrc) > 0) {

    /*handle destination rect; only x & y are used from *dst; w & h are copied from source rect*/
    ldst->x = dst->x;
    ldst->y = dst->y;
    ldst->w = lsrc->w;
    ldst->h = lsrc->h;

    /*ensure that the destination rect fits in global clip*/
    P2D_ClipFit(ldst);

    /*if the dest rect changed, we have to reconsider the src rect*/
    if(ldst->x > dst->x) {
      delta = ldst->x - dst->x;
      if(delta < lsrc->w) {
        lsrc->w -= delta;
        lsrc->x += delta;
      }
      else {
        ldst->w = 0;
      }
    }
    if(ldst->y > dst->y) {
      delta = ldst->y - dst->y;
      if(delta < lsrc->h) {
        lsrc->h -= delta;
        lsrc->y += delta;
      }
      else {
        ldst->h = 0;
      }
    }

    pxCnt = P2D_GetPixelCnt(ldst);
  }

  return pxCnt;
}
