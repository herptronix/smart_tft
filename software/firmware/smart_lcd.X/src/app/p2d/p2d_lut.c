/**
 * @file p2d_lut.c
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

#include "p2d_internal.h"


/**
 * Local functions prototypes
 */
static int8_t InitLut(lut_info_st *info, color_t *arColors, uint16_t maxLutSize);
static void UpdateLut(lut_info_st *info, color_t *arColors);
static int8_t LutFill(const lut_info_st *info, color_t *arColors);
static int8_t LutGradient(const lut_info_st *info, color_t *arColors);
static int8_t LutCopy(lut_info_st *info, color_t *arColors);
static void LutAlpha(const lut_info_st *info, color_t *arColors);
static void LutBlackAndWhite(const lut_info_st *info, color_t *arColors);
static void LutColorkey(const lut_info_st *info, color_t *arColors);


/**
 * @function P2D_InitLut4BPP
 * @brief initialize a 4BPP color lut (4BPP = 16 different colors)
 * @param lut4bpp_st *lut: pointer of the lut
 * @param const uint8_t *pFile: optional lut file
 * @param lutmode_t mode: lut mode, see possible flags association (lutmode_t)
 * @return 0: success, -1 error
 */
int8_t P2D_InitLut4BPP(lut4bpp_st *lut, const uint8_t *pFile, lutmode_t mode) {

  int8_t res = -1;
  if(lut != NULL) {
    lut->info.pFile = pFile;
    lut->info.mode = mode;
    res = InitLut(&(lut->info), lut->lut, 16);
  }
  return res;
}


/**
 * @function P2D_UpdateLut4BPP
 * @brief Update (if needed -- depending of lut type, current color context...) a 4BPP lut
 * @param lut4bpp_st *lut: lut to update
 * @return none
 */
void P2D_UpdateLut4BPP(lut4bpp_st *lut) {
  if(lut != NULL) {
    UpdateLut(&(lut->info), lut->lut);
  }
}


/**
 * @function P2D_InitLut8BPP
 * @brief initialize a 8BPP color lut (8BPP = 256 different colors)
 * @param lut8bpp_st *lut: pointer of the lut
 * @param const uint8_t *pFile: optional lut file
 * @param lutmode_t mode: lut mode, see possible flags association (lutmode_t)
 * @return 0: success, -1 error
 */
int8_t P2D_InitLut8BPP(lut8bpp_st *lut, const uint8_t *pFile, lutmode_t mode) {

  int8_t res = -1;
  if(lut != NULL) {
    lut->info.pFile = pFile;
    lut->info.mode = mode;
    res = InitLut(&lut->info, lut->lut, 256);
  }
  return res;
}


/**
 * @function P2D_UpdateLut8BPP
 * @brief Update (if needed -- depending of lut type, current color context...) a 8BPP lut
 * @param lut8bpp_st *lut: lut to update
 * @return none
 */
void P2D_UpdateLut8BPP(lut8bpp_st *lut) {
  if(lut != NULL) {
    UpdateLut(&(lut->info), lut->lut);
  }
}


/**
 * @function InitLut
 * @brief initialize a lut
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @param uint16_t maxLutSize: maximum allowed colors (depends on BPP)
 * @return 0: success, -1 error
 */
static int8_t InitLut(lut_info_st *info, color_t *arColors, uint16_t maxLutSize) {

  int8_t res = -1;
  info->colorCount = maxLutSize;

  /* 1- Manage exclusive flags*/
  if     (info->mode & LUT_E_FILLED)   res = LutFill(info, arColors);     /*fill lut with colFront*/
  else if(info->mode & LUT_E_GRADIENT) res = LutGradient(info, arColors); /*fill lut with alpha gradient*/
  else if(info->mode & LUT_E_COPY)     res = LutCopy(info, arColors);     /*fill lut with file content*/

  /* 2- Manage optional flags
   * shall be in the following order:
   * first, save color context (it is used for color computing)
   * then apply LUT_O_BLACK_AND_WHITE
   * then apply LUT_O_ALPHA
   * finally, apply LUT_COLOR_KEY */
  if(res == 0) {

    /*save the color context which has been used for creating the lut*/
    info->front = context.colFront;
    info->backgrnd = context.colBackgrnd;
    info->alpha = context.alpha;

    if(info->mode & LUT_O_BLACK_AND_WHITE)  LutBlackAndWhite(info, arColors);
    if(info->mode & LUT_O_ALPHA)            LutAlpha(info, arColors);
    if(info->mode & LUT_O_COLOR_KEY)        LutColorkey(info, arColors);
  }

  return res;
}


/**
 * @function UpdateLut
 * @brief Update (if needed -- depending of lut type, current color context...) a lut
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return 0: success, -1 error
 */
static void UpdateLut(lut_info_st *info, color_t *arColors) {

  bool bColFront = false;
  bool bColBack = false;
  bool bUpdate = false;
  bool bAlpha = false;
  uint8_t mode = info->mode;

  /*check if context have changed*/
  if(info->front != context.colFront) bColFront = true;
  if(info->backgrnd != context.colBackgrnd) bColBack = true;
  if(info->alpha != context.alpha) bAlpha = true;

  /*check if the lut has to be updated, according changed values*/
  /*small exception for the colorkey: not considered for lut updating*/
  if(bColFront) {
    if(mode & LUT_E_FILLED) bUpdate = true;
    if(mode & LUT_E_GRADIENT) bUpdate = true;
  }
  if(bColBack) {
    if(mode & LUT_E_GRADIENT) bUpdate = true;
    if(mode & LUT_O_ALPHA) bUpdate = true;
  }
  if(bAlpha) {
    if(mode & LUT_O_ALPHA) bUpdate = true;
  }

  /*lut update*/
  if(bUpdate) {
    (void) InitLut(info, arColors, info->colorCount);
  }
  else {
    /*it costs less to always call it instead of perform test above*/
    if(mode & LUT_O_COLOR_KEY) LutColorkey(info, arColors);
  }
}


/**
 * @function LutFill
 * @brief fill the lut with colFront
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return 0
 */
static int8_t LutFill(const lut_info_st *info, color_t *arColors) {
  uint16_t cnt;
  for(cnt = 0; cnt < info->colorCount; cnt++) {
    arColors[cnt] = context.colFront;
  }
  return 0;
}


/**
 * @function LutGradient
 * @brief fill the lut with a gradiant from lut[0]=colBackgrnd to lut[n]=colFront
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return 0
 */
static int8_t LutGradient(const lut_info_st *info, color_t *arColors) {
  uint16_t cnt;
  for(cnt = 0; cnt < info->colorCount; cnt++) {
    arColors[cnt] = P2D_Alpha_a_on_b(context.colFront, context.colBackgrnd, cnt * 255 / (info->colorCount - 1));
  }
  return 0;
}


/**
 * @function LutCopy
 * @brief copy a lut file into a lut
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return 0: success, -1 error
 */
static int8_t LutCopy(lut_info_st *info, color_t *arColors) {

  uint16_t cnt, realLutSize;
  uint8_t r, g, b;
  const uint8_t *pFile;
  int8_t res = -1;

  pFile = info->pFile;
  if(pFile != NULL) {

    /*retrieve the real number of entries*/
    realLutSize = *pFile++;
    realLutSize <<= 8;
    realLutSize |= *pFile++;
    if(info->colorCount > realLutSize) info->colorCount = realLutSize;

    /*copy file content*/
    for(cnt = 0; cnt < info->colorCount; cnt++) {
      b = *pFile++;
      g = *pFile++;
      r = *pFile++;
      arColors[cnt] = P2D_Color(r, g, b);
    }
    res = 0;
  }

  return res;
}


/**
 * @function LutAlpha
 * @brief perform alpha(lut[n] on colBackgrnd) for each color
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return none
 */
static void LutAlpha(const lut_info_st *info, color_t *arColors) {
  uint16_t cnt;
  for(cnt = 0; cnt < info->colorCount; cnt++) {
    arColors[cnt] = P2D_Alpha_a_on_b(arColors[cnt], context.colBackgrnd, context.alpha);
  }
}


/**
 * @function LutBlackAndWhite
 * @brief perform B&W(lut[n]) for each color
 * @param lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return none
 */
static void LutBlackAndWhite(const lut_info_st *info, color_t *arColors) {
  uint16_t cnt;
  for(cnt = 0; cnt < info->colorCount; cnt++) {
    arColors[cnt] = P2D_ColorBlackAndWhite(arColors[cnt]);
  }
}


/**
 * @function LutColorkey
 * @brief set lut[0] to colBackgrnd
 * @param @unused@lut_info_st *info: lut info
 * @param color_t *arColors: pointer to color table
 * @return none
 */
static void LutColorkey(/*@unused@*/const lut_info_st *info, color_t *arColors) {
  arColors[0] = context.colBackgrnd;
}
