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

#ifndef _p2d_colors_h_
#define _p2d_colors_h_

#include "p2d.h"


/**
 * @function P2D_Color
 * @brief converts a standart RGB 8:8:8 into a RGB 5:6:5 (which is the format of the LCD)
 * @param uint8_t r, g, b: red, green, blue range[0-255]
 * @return color_t: corresponding RGB 5:6:5 color
 */
color_t P2D_Color(uint8_t r, uint8_t g, uint8_t b);

/**
 * @function P2D_ColorToRGB
 * @brief converts a RGB 5:6:5 into a RGB 8:8:8; introduces extrapolation errors
 * @param color_t color: input color
 * @param uint8_t *r, *g, *b: red, green, blue output
 * @return none
 */
void P2D_ColorToRGB(color_t color, /*@out@*/uint8_t *r, /*@out@*/uint8_t *g, /*@out@*/uint8_t *b);

/**
 * @function P2D_ColorBlackAndWhite
 * @brief turn a color into a back and white level
 * @param color_t a: input color
 * @return color_t: black & white'd color
 */
color_t P2D_ColorBlackAndWhite(color_t a);

/**
 * @function P2D_Alpha_a_on_b
 * @brief compute the color value corresponding to alpha(color A on color B)
 * @param color_t a, b: input colors
 * @param alpha: range[0-255]
 * @return color_t: corresponding alpha(color A on color B)
 */
color_t P2D_Alpha_a_on_b(color_t a, color_t b, uint8_t alpha);

#define COLOR_BLACK         0x0000  /*P2D_Color(0  , 0  , 0  )*/
#define COLOR_DARK_GREY     P2D_Color(64 , 64 , 64 )
#define COLOR_GREY          P2D_Color(128, 128, 128)
#define COLOR_LIGHT_GREY    P2D_Color(196, 196, 196)
#define COLOR_WHITE         0xFFFF  /*P2D_Color(255, 255, 255)*/
#define COLOR_RED           P2D_Color(255, 0  , 0  )
#define COLOR_ORANGE        P2D_Color(255, 128, 0  )
#define COLOR_YELLOW        P2D_Color(255, 255, 0  )
#define COLOR_GREEN         P2D_Color(0  , 255, 0  )
#define COLOR_CYAN          P2D_Color(0  , 255, 255)
#define COLOR_BLUE          P2D_Color(0  , 0  , 255)
#define COLOR_PURPLE        P2D_Color(255, 0  , 255)

#endif
