/**
 * @file p2d_math.c
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

#include "p2d_internal.h"


/**
 * private variables
 */
static uint32_t rnd = 0;
static const int16_t arSin[360] = {
      0,    571,   1143,   1714,   2285,   2855,   3425,   3993,   4560,   5125,
   5689,   6252,   6812,   7370,   7927,   8480,   9031,   9580,  10125,  10667,
  11206,  11742,  12274,  12803,  13327,  13847,  14364,  14875,  15383,  15885,
  16383,  16876,  17363,  17846,  18323,  18794,  19259,  19719,  20173,  20620,
  21062,  21497,  21925,  22347,  22761,  23169,  23570,  23964,  24350,  24729,
  25100,  25464,  25820,  26168,  26509,  26841,  27165,  27480,  27787,  28086,
  28377,  28658,  28931,  29195,  29450,  29696,  29934,  30162,  30381,  30590,
  30790,  30981,  31163,  31335,  31497,  31650,  31793,  31927,  32050,  32164,
  32269,  32363,  32448,  32522,  32587,  32642,  32687,  32722,  32747,  32762,
  32767,  32762,  32747,  32722,  32687,  32642,  32587,  32522,  32448,  32363,
  32269,  32164,  32050,  31927,  31793,  31650,  31497,  31335,  31163,  30981,
  30790,  30590,  30381,  30162,  29934,  29696,  29450,  29195,  28931,  28658,
  28377,  28086,  27787,  27480,  27165,  26841,  26509,  26168,  25820,  25464,
  25100,  24729,  24350,  23964,  23570,  23169,  22761,  22347,  21925,  21497,
  21062,  20620,  20173,  19719,  19259,  18794,  18323,  17846,  17363,  16876,
  16383,  15885,  15383,  14875,  14364,  13847,  13327,  12803,  12274,  11742,
  11206,  10667,  10125,   9580,   9031,   8480,   7927,   7370,   6812,   6252,
   5689,   5125,   4560,   3993,   3425,   2855,   2285,   1714,   1143,    571,
      0,   -571,  -1143,  -1714,  -2285,  -2855,  -3425,  -3993,  -4560,  -5125,
  -5689,  -6252,  -6812,  -7370,  -7927,  -8480,  -9031,  -9580, -10125, -10667,
 -11206, -11742, -12274, -12803, -13327, -13847, -14364, -14875, -15383, -15885,
 -16383, -16876, -17363, -17846, -18323, -18794, -19259, -19719, -20173, -20620,
 -21062, -21497, -21925, -22347, -22761, -23169, -23570, -23964, -24350, -24729,
 -25100, -25464, -25820, -26168, -26509, -26841, -27165, -27480, -27787, -28086,
 -28377, -28658, -28931, -29195, -29450, -29696, -29934, -30162, -30381, -30590,
 -30790, -30981, -31163, -31335, -31497, -31650, -31793, -31927, -32050, -32164,
 -32269, -32363, -32448, -32522, -32587, -32642, -32687, -32722, -32747, -32762,
 -32767, -32762, -32747, -32722, -32687, -32642, -32587, -32522, -32448, -32363,
 -32269, -32164, -32050, -31927, -31793, -31650, -31497, -31335, -31163, -30981,
 -30790, -30590, -30381, -30162, -29934, -29696, -29450, -29195, -28931, -28658,
 -28377, -28086, -27787, -27480, -27165, -26841, -26509, -26168, -25820, -25464,
 -25100, -24729, -24350, -23964, -23570, -23169, -22761, -22347, -21925, -21497,
 -21062, -20620, -20173, -19719, -19259, -18794, -18323, -17846, -17363, -16876,
 -16383, -15885, -15383, -14875, -14364, -13847, -13327, -12803, -12274, -11742,
 -11206, -10667, -10125,  -9580,  -9031,  -8480,  -7927,  -7370,  -6812,  -6252,
  -5689,  -5125,  -4560,  -3993,  -3425,  -2855,  -2285,  -1714,  -1143,   -571
};


/**
 * @function P2D_RandInit
 * @brief Initialize the random geerator with a given key
 * @param uint32_t key: user seed
 * @return none
 */
void P2D_RandInit(uint32_t key) {
  rnd = key;
}


/**
 * @function P2D_Rand
 * @brief Return a pseudo random number between 0 and a given maximum
 * @param uint16_t max
 * @return uint16_t: pseudo random
 */
uint16_t P2D_Rand(uint16_t max) {
  rnd = (1103515245U * rnd + 12345) & 0x7FFFFFFF;
  return (uint16_t) (rnd % (max + 1));
}


/**
 * @function P2D_Sin
 * @brief return sinus value
 * @param int16_t deg: angle, in degree
 * @return int16_t: sinus, between -32767 and +32767
 */
int16_t P2D_Sin(int16_t deg) {
  deg = deg % 360;
  if(deg < 0) deg += 360;
  return arSin[deg];
}


/**
 * @function P2D_Cos
 * @brief return cosinus value
 * @param int16_t deg: angle, in degree
 * @return int16_t: cosinus, between -32767 and +32767
 */
int16_t P2D_Cos(int16_t deg) {
  return P2D_Sin(deg + 90);
}


/**
 * @function P2D_Abs
 * @brief return abs value
 * @param int32_t val
 * @return int32_t: abs
 */
int32_t P2D_Abs(int32_t val) {
  if(val < 0) val = -val;
  return val;
}


/**
 * @function P2D_sqrt
 * @brief return the root of a given value
 *   from app note #TB040, Microchip
 * @param uint16_t val
 * @return uint8_t: sqrt(val)
 */
uint8_t P2D_sqrt(uint16_t val) {

  uint8_t res, bit;
  uint32_t tmp;

  if(val < 2) {
    res = val;
  }
  else {
    res = 0;
    tmp = 0;
    for(bit = 0x80; bit != 0x00 && tmp != val; bit >>= 1) {
      res |= bit;
      tmp = (uint32_t) res * res;
      if(tmp > val) res ^= bit;
    }
  }

  return res;
}
