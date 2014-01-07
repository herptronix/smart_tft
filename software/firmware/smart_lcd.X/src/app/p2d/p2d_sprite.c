/**
 * @file p2d_sprite.c
 * @brief p2d sprite functions (limited to 8BPP)
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd) 2013-04-07 creation
 *                    2013-08-13 small modification; no impact on functionality
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
 * Private defines
 */
typedef struct {
  const uint8_t *raw;
  rect_st dim;
  uint8_t bpp;
} sprite_st;

enum {
  SP_OFFSET_BPP,
  SP_OFFSET_W_MSB,
  SP_OFFSET_W_LSB,
  SP_OFFSET_H_MSB,
  SP_OFFSET_H_LSB,
  SP_OFFSET_RAW
};


/**
 * private variables
 */
static /*@null@*/ const lut8bpp_st *pLut8 = NULL;


/**
 * Local functions prototypes
 */
static int8_t SpriteOpen(/*@out@*/sprite_st *ptr, const uint8_t *pFile);
static void PutFast_8BPP(const rect_st *dst, const color_t *lut, const uint8_t *raw, uint32_t pxCnt);
static void PutSlow_8BPP(const rect_st *dst, const rect_st *src, const color_t *lut, const sprite_st *sprite);


/**
 * @function P2D_SpriteGetWidth
 * @brief return the width of a sprite
 * @param const uint8_t *pFile: pointer to the sprite file
 * @return length_t: width of the sprite
 */
length_t P2D_SpriteGetWidth(const uint8_t *pFile) {
  length_t res = 0;
  if(pFile != NULL) res = (((length_t) pFile[SP_OFFSET_W_MSB]) << 8) + pFile[SP_OFFSET_W_LSB];
  return res;
}


/**
 * @function P2D_SpriteGetHeight
 * @brief return the height of a sprite
 * @param const uint8_t *pFile: pointer to the sprite file
 * @return length_t: height of the sprite
 */
length_t P2D_SpriteGetHeight(const uint8_t *pFile) {
  length_t res = 0;
  if(pFile != NULL) res = (((uint16_t) pFile[SP_OFFSET_H_MSB]) << 8) + pFile[SP_OFFSET_H_LSB];
  return res;
}


/**
 * @function P2D_SpriteSetLut8BPP
 * @brief define a lut to use for 8BPP sprites
 * @param const lut8bpp_st *lut: lut to use
 * @return none
 */
void P2D_SpriteSetLut8BPP(const lut8bpp_st *lut) {
  pLut8 = lut;
}


/**
 * @function P2D_Sprite
 * @brief put a given sprite part on current surface, at given coordinates
 * @param const rect_st *src: selected part of the sprite to display; if NULL, select the whole sprite
 * @param const rect_st *dst: destination; only x & y are used
 * @param const uint8_t *pFile: sprite file
 * @return none
 */
void P2D_Sprite(const rect_st *src, const rect_st *dst, const uint8_t *pFile) {

  rect_st lsrc, ldst;
  sprite_st sprite;
  const uint8_t *raw;
  uint32_t px;

  if(pFile != NULL && dst != NULL && SpriteOpen(&sprite, pFile) == 0) {

    /*apply clipping*/
    px = P2D_ClipBitBlt(&sprite.dim, src, dst, &lsrc, &ldst);

    /*if some pixels remain after clipping*/
    if(px > 0) {

      /*if source & destination have the same width & DISPLAY_SOLID -> optimized procedure*/
      if(ldst.w == sprite.dim.w && context.mode == DISPLAY_SOLID) {
        if(sprite.bpp == 8 && pLut8 != NULL) {
          raw = &(sprite.raw[lsrc.x + lsrc.y * sprite.dim.w]);
          PutFast_8BPP(&ldst, pLut8->lut, raw, px);
        }
      }
      /*else, pixel per pixel... much slower!*/
      else {
        if(sprite.bpp == 8 && pLut8 != NULL) {
          PutSlow_8BPP(&ldst, &lsrc, pLut8->lut, &sprite);
        }
      }
    }
  }
}


/**
 * @function SpriteOpen
 * @brief retrieve sprite info from a file
 * @param sprite_st *ptr: pointer to the struct to fill
 * @param const uint8_t *pFile: sprite file
 * @return 0 success, -1 error
 */
static int8_t SpriteOpen(sprite_st *ptr, const uint8_t *pFile) {

  int8_t res = -1;

  /*retrieve sprite info*/
  ptr->dim.x = 0;
  ptr->dim.y = 0;
  ptr->dim.w = P2D_SpriteGetWidth(pFile);
  ptr->dim.h = P2D_SpriteGetHeight(pFile);
  ptr->bpp   = pFile[SP_OFFSET_BPP];
  ptr->raw   = &pFile[SP_OFFSET_RAW];

  /*check coherence: known bpp and valid dimension*/
  if(P2D_GetPixelCnt(&ptr->dim) > 0 && ptr->bpp == 8) {
    res = 0;
  }

  return res;
}


/**
 * @function PutFast_8BPP
 * @brief sprite copy, optimized procedure
 * @param const rect_st *dst: destination window
 * @param const color_t *lut: lut to use
 * @param const uint8_t *raw: sprite raw address
 * @param uint32_t pxCnt: number of pixel composing the destination window
 * @return none
 */
static void PutFast_8BPP(const rect_st *dst, const color_t *lut, const uint8_t *raw, uint32_t pxCnt) {

  /*set a hardware window & just put the sprite stream*/
  SetWnd(dst);
  while(pxCnt-- > 0) Put(lut[*raw++]);

  /*restore full screen window*/
  SetWnd(NULL);
}


/**
 * @function PutSlow_8BPP
 * @brief sprite copy, slow procedure
 * @param const rect_st *dst: destination window
 * @param const rect_st *src: source window
 * @param const color_t *lut: lut to use
 * @param const const sprite_st *sprite: pointer to sprite structure
 * @return none
 */
static void PutSlow_8BPP(const rect_st *dst, const rect_st *src, const color_t *lut, const sprite_st *sprite) {

  coord_t sx, sy, dx, dy;
  const uint8_t *raw;

  dx = dst->x;
  dy = dst->y;

  for(sy = src->y; sy < src->y + dst->h; sy++) {

    raw = &(sprite->raw[src->x + sy * sprite->dim.w]);
    SetPos(dx, dy);

    for(sx = 0; sx < dst->w; sx++) {
      Put(lut[*raw]);
      raw++;
      //dx++; /*removed: statement with no effect*/
    }

    dy++;
    dx = dst->x;
  }
}
