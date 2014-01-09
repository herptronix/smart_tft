/**
 * @file local_functions.h
 * @brief non-serializable function
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-17
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

#ifndef _local_functions_h_
#define _local_functions_h_

#include "tft_defines.h"

/**
 * @function GUI_Rect
 * @brief generate a rect_st
 * @param coord_t x, coord_t y, length_t w, length_t h: rect parameters
 * @return rect_st
 */
rect_st GUI_Rect(coord_t x, coord_t y, length_t w, length_t h);

/**
 * @function P2D_Color
 * @brief converts a standart RGB 8:8:8 into a RGB 5:6:5 (which is the format of the LCD)
 * @param uint8_t r, g, b: red, green, blue range[0-255]
 * @return color_t: corresponding RGB 5:6:5 color
 */
color_t P2D_Color(uint8_t r, uint8_t g, uint8_t b);

/**
 * @function P2D_RandInit
 * @brief Initialize the random geerator with a given key
 * @param uint32_t key: user seed
 * @return none
 */
void P2D_RandInit(uint32_t key);

/**
 * @function P2D_Rand
 * @brief Return a pseudo random number between 0 and a given maximum
 * @param uint16_t max
 * @return uint16_t: pseudo random
 */
uint16_t P2D_Rand(uint16_t max);

/**
 * @function P2D_Sin
 * @brief return sinus value
 * @param int16_t deg: angle, in degree
 * @return int16_t: sinus, between -32767 and +32767
 */
int16_t P2D_Sin(int16_t deg);

/**
 * @function P2D_Cos
 * @brief return cosinus value
 * @param int16_t deg: angle, in degree
 * @return int16_t: cosinus, between -32767 and +32767
 */
int16_t P2D_Cos(int16_t deg);

/**
 * @function P2D_Abs
 * @brief return abs value
 * @param int32_t val
 * @return int32_t: abs
 */
int32_t P2D_Abs(int32_t val);

/**
 * @function P2D_sqrt
 * @brief return the root of a given value
 *   from app note #TB040, Microchip
 * @param uint16_t val
 * @return uint8_t: sqrt(val)
 */
uint8_t P2D_sqrt(uint16_t val);

#endif
