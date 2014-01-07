/**
 * @file p2d_lut.h
 * @brief p2d LUT (colors look up table)
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

#ifndef _p2d_lut_h_
#define _p2d_lut_h_

#include "p2d.h"

typedef uint8_t lutmode_t;

/**
 * @typedef lut_info_st
 */
typedef struct {
  const uint8_t *pFile;
  color_t front, backgrnd;
  uint16_t colorCount;
  uint8_t alpha;
  lutmode_t mode;
} lut_info_st;

/**
 * @typedef lut4bpp_st
 */
typedef struct {
  color_t lut[16];
  lut_info_st info;
} lut4bpp_st;

/**
 * @typedef lut8bpp_st
 */
typedef struct {
  color_t lut[256];
  lut_info_st info;
} lut8bpp_st;


/**
 *
 * -EXCLUSIVE_FLAGS-------OPERATION-------------------------
 * LUT_E_COPY             copy the file content into lut
 * LUT_E_FILLED           fill the whole lut with <colFront>
 * LUT_E_GRADIENT         fill the lut with a gradient from <colBackgrnd> to <colFront>
 *
 * -OPTIONAL_FLAGS--------OPERATION-------------------------
 * LUT_O_ALPHA            perform a alpha to all lut colors with <colBackgrnd>
 * LUT_O_BLACK_AND_WHITE  set all lut colors to black & white levels
 * LUT_O_COLOR_KEY        force the color <lut[0]> to <colBackgrnd>
 *
 * lut flags shall be composed of only one EXCLUSIVE_FLAGS, which can be or'd with several OPTIONAL_FLAGS
 * e.g. (LUT_COPY | LUT_BLACK_AND_WHITE | LUT_O_COLOR_KEY)
 */
#define LUT_E_COPY              (lutmode_t) 0x01
#define LUT_E_FILLED            (lutmode_t) 0x02
#define LUT_E_GRADIENT          (lutmode_t) 0x04
#define LUT_O_ALPHA             (lutmode_t) 0x20
#define LUT_O_BLACK_AND_WHITE   (lutmode_t) 0x40
#define LUT_O_COLOR_KEY         (lutmode_t) 0x80


/**
 * @function P2D_InitLut4BPP
 * @brief initialize a 4BPP color lut (4BPP = 16 different colors)
 * @param lut4bpp_st *lut: pointer of the lut
 * @param const uint8_t *pFile: optional lut file
 * @param lutmode_t mode: lut mode, see possible flags association (lutmode_t)
 * @return 0: success, -1 error
 */
int8_t P2D_InitLut4BPP(lut4bpp_st *lut, const uint8_t *pFile, lutmode_t mode);

/**
 * @function P2D_UpdateLut4BPP
 * @brief Update (if needed -- depending of lut type, current color context...) a 4BPP lut
 * @param lut4bpp_st *lut: lut to update
 * @return none
 */
void P2D_UpdateLut4BPP(lut4bpp_st *lut);

/**
 * @function P2D_InitLut8BPP
 * @brief initialize a 8BPP color lut (8BPP = 256 different colors)
 * @param lut8bpp_st *lut: pointer of the lut
 * @param const uint8_t *pFile: optional lut file
 * @param lutmode_t mode: lut mode, see possible flags association (lutmode_t)
 * @return 0: success, -1 error
 */
int8_t P2D_InitLut8BPP(lut8bpp_st *lut, const uint8_t *pFile, lutmode_t mode);

/**
 * @function P2D_UpdateLut8BPP
 * @brief Update (if needed -- depending of lut type, current color context...) a 8BPP lut
 * @param lut8bpp_st *lut: lut to update
 * @return none
 */
void P2D_UpdateLut8BPP(lut8bpp_st *lut);

#endif
