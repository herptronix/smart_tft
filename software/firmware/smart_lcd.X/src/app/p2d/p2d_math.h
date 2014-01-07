/**
 * @file p2d_math.h
 * @brief p2d math functions (synthetized sin table & random)
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-04-07  : initial version
 *  0.2b  2013-08-27  : Add sqrt function
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

#ifndef _p2d_math_h_
#define _p2d_math_h_

#include "p2d.h"

#define P2D_G_DIV 32767

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
 * @param uint16_t val
 * @return uint8_t: sqrt(val)
 */
uint8_t P2D_sqrt(uint16_t val);

#endif
