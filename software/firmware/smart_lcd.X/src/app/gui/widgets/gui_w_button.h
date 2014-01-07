/**
 * @file gui_w_button.h
 * @brief basic button implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13  : initial version
 *  0.2b  2013-08-27  Add alignment & place order
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
#ifndef _gui_w_button_h_
#define _gui_w_button_h_

#include "gui.h"

/**
 * sprite & texte place order
 */
typedef enum {
  G_BTN_PLACE_IMG_L_TEXT_R, /*on same y: sprite | pitch 2px | text*/
  G_BTN_PLACE_IMG_R_TEXT_L, /*on same y: text | pitch 2px | sprite*/
  G_BTN_PLACE_IMG_T_TEXT_B, /*on same x: sprite | pitch 2px | text*/
  G_BTN_PLACE_IMG_B_TEXT_T  /*on same x: text | pitch 2px | sprite*/
} btn_placeOrder_e;


/**
 * @function GUI_W_ButtonSetPlacementOrder
 * @brief define the position of sprite & text
 * @param btn_placeOrder_e o: place order
 * @return none
 */
void GUI_W_ButtonSetPlacementOrder(btn_placeOrder_e order);


/**
 * @function GUI_W_ButtonAdd
 * @brief add a basic button
 * @param const rect_st *rec: object dimension
 * @param const void *str: text of the button (will be copied into it)
 * @param gui_img_t img: image of the button
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_ButtonAdd(const rect_st *rec, const void /*@null@*/ *str, gui_img_t img);


#endif
