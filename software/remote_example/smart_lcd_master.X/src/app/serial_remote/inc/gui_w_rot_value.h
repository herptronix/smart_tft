/**
 * @file gui_w_rot_value.h
 * @brief rotary value implementation (use with rot button)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-09-15  : initial version
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

#ifndef _gui_w_rot_value_h_
#define _gui_w_rot_value_h_

#include "gui.h"


/**
 * @function GUI_W_RotaryValueAdd
 * @brief add a rotary value (use with rot button)
 * @param const rect_st *rec: object dimension
 * @param int32_t *pVar: pointer to the int32_t of the rot button
 * @param const int8_t *pStep: pointer to the counter step of the rot button
 * @param const void *strUnit: unit string; may be null
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_RotaryValueAdd(const rect_st *rec, int32_t *pVar, const int8_t *pStep, const void /*@null@*/ *strUnit);

/**
 * @function GUI_W_RotaryValueLock
 * @brief lock / unlock the rotary value. If locked, increment coming from rot button will have no effect
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param bool bLock: != 0 lock the value, 0 unlock the value
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueLock(g_obj_st /*@null@*/ *obj, bool bLock);

/**
 * @function GUI_W_RotaryValueSetMinMax
 * @brief set the range (min/max) of the rotary value
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param int32_t min, max: new range
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueSetMinMax(g_obj_st /*@null@*/ *obj, int32_t min, int32_t max);

/**
 * @function GUI_W_RotaryValueSetDotPos
 * @brief set the dot position
 * @param g_obj_st *obj: pointer to the generic object corresponding to the rot value
 * @param uint8_t posDot: dot pos
 * @return int8_t: 0 success, -1 error
 */
int8_t GUI_W_RotaryValueSetDotPos(g_obj_st /*@null@*/ *obj, uint8_t posDot);

#endif
