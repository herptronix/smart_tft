/**
 * @file gui_w_rot_button.h
 * @brief rotary button implementation
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

#ifndef _gui_w_rot_button_h_
#define _gui_w_rot_button_h_

#include "gui.h"

/**
 * gr_enum_e: degree per step
 */
typedef enum {
  ROTARY_BTN_GR_5_DEG,
  ROTARY_BTN_GR_10_DEG,
  ROTARY_BTN_GR_15_DEG,
  ROTARY_BTN_GR_30_DEG,
  _ROTARY_BTN_GR_CNT
} gr_enum_e;


/**
 * @function GUI_W_RotaryButtonAdd
 * @brief add a rotary button (~rotary encoder)
 * @param const rect_st *rec: object dimension (must be square !)
 * @param int8_t *pVar: pointer to the int8 which will recieve the increment/decrement
 * @param gr_enum_e granularity: rotation steps, in degrees. see gr_enum_e
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_RotaryButtonAdd(const rect_st *rec, int8_t *pVar, gr_enum_e granularity);

#endif
