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

#ifndef _p2d_sprite_h_
#define _p2d_sprite_h_

#include "p2d.h"

/**
 * @function P2D_SpriteGetWidth
 * @brief return the width of a sprite
 * @param const uint8_t *pFile: pointer to the sprite file
 * @return length_t: width of the sprite
 */
length_t P2D_SpriteGetWidth(const uint8_t *pFile);

/**
 * @function P2D_SpriteGetHeight
 * @brief return the height of a sprite
 * @param const uint8_t *pFile: pointer to the sprite file
 * @return length_t: height of the sprite
 */
length_t P2D_SpriteGetHeight(const uint8_t *pFile);

/**
 * @function P2D_SpriteSetLut8BPP
 * @brief define a lut to use for 8BPP sprites
 * @param const lut8bpp_st *lut: lut to use
 * @return none
 */
void P2D_SpriteSetLut8BPP(const lut8bpp_st *lut);

/**
 * @function P2D_Sprite
 * @brief put a given sprite part on current surface, at given coordinates
 * @param const rect_st *src: selected part of the sprite to display; if NULL, select the whole sprite
 * @param const rect_st *dst: destination; only x & y are used
 * @param const uint8_t *pFile: sprite file
 * @return none
 */
void P2D_Sprite(const rect_st *src, const rect_st *dst, const uint8_t *pFile);

#endif
