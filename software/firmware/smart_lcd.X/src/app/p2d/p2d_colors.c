/**
 * @file p2d_colors.c
 * @brief p2d 16bits colors managemet
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd) 2013-04-07
 *                    2013-08-20: modification according to RGB swap in ILI9320.c
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
 * @function P2D_Color
 * @brief converts a standart RGB 8:8:8 into a RGB 5:6:5 (which is the format of the LCD)
 * @param uint8_t r, g, b: red, green, blue range[0-255]
 * @return color_t: corresponding RGB 5:6:5 color
 */
color_t P2D_Color(uint8_t r, uint8_t g, uint8_t b) {
  color_t col;
  col =  ((color_t) r >> 3) << 11;
  col |= ((color_t) g >> 2) << 5;
  col |=  (color_t) b >> 3;
  return col;
}


/**
 * @function P2D_ColorToRGB
 * @brief converts a RGB 5:6:5 into a RGB 8:8:8; -> introduces extrapolation errors
 * @param color_t color: input color
 * @param uint8_t *r, *g, *b: red, green, blue output
 * @return none
 */
void P2D_ColorToRGB(color_t color, uint8_t *r, uint8_t *g, uint8_t *b) {
  if(r != NULL && g != NULL && b != NULL) {
    *r = (uint8_t) ((color & 0xF800) >> 8) + 4; /*+4: EE / 2, where EE (extrapolation error) is 2^3*/
    *b = (uint8_t) ((color & 0x001F) << 3) + 4; /*+4: EE / 2, where EE (extrapolation error) is 2^3*/
    *g = (uint8_t) ((color & 0x07E0) >> 3) + 2; /*+2: EE / 2, where EE (extrapolation error) is 2^2*/
  }
}


/**
 * @function P2D_ColorBlackAndWhite
 * @brief turn a color into a back and white level
 * @param color_t a: input color
 * @return color_t: black & white'd color
 */
color_t P2D_ColorBlackAndWhite(color_t a) {
  uint8_t ar, ag, ab;
  uint16_t lvl;
  P2D_ColorToRGB(a, &ar, &ag, &ab);
  lvl = ar + ag + ab;
  lvl = lvl / 3;
  ar = (uint8_t) lvl;
  return P2D_Color(ar, ar, ar);
}


/**
 * @function P2D_Alpha_a_on_b
 * @brief compute the color value corresponding to alpha(color A on color B)
 * @param color_t a, b: input colors
 * @param alpha: range[0-255]
 * @return color_t: corresponding alpha(color A on color B)
 */
color_t P2D_Alpha_a_on_b(color_t a, color_t b, uint8_t alpha) {
  uint8_t ar, ag, ab, br, bg, bb, or, og, ob;
  uint16_t aComp;

  P2D_ColorToRGB(a, &ar, &ag, &ab);
  P2D_ColorToRGB(b, &br, &bg, &bb);

  aComp = 255 - alpha;

  or = (aComp * br + (uint16_t) alpha * ar) >> 8;
  og = (aComp * bg + (uint16_t) alpha * ag) >> 8;
  ob = (aComp * bb + (uint16_t) alpha * ab) >> 8;

  return P2D_Color(or, og, ob);
}
