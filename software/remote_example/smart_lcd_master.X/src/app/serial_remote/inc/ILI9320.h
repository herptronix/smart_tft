/**
 * @file ILI9320.h
 * @brief lcd driver
 * @author Duboisset Philippe
 * @version 0.4b
 * @date (yyyy-mm-dd) 2013-04-07
 *                    2013-07-27: improvement of power-on sequence
 *                    2013-08-20: modification of <0x0003, 0x1038> (RGB swap, for compatibility with SDL)
 *                    2013-11-14: LCD_WriteReg is now accessible outside (for gamma ajdustement)
 *
 * Copyright (C) <2013>  Duboisset Philippe <duboisset.philippe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ILI9320_h_
#define _ILI9320_h_

#include "main.h"


typedef uint16_t color_t;   /*color is represented by an usigned 16bits word*/
typedef uint16_t length_t;
typedef int16_t  coord_t;   /*lcd coordinates type*/
typedef struct {
  coord_t x, y;
  length_t w, h;
} rect_st;                  /*basic lcd window representation*/


/**
 * @function LCD_Init
 * @brief turn on & configure the LCD
 * @param none
 * @return none
 */
void LCD_Init(void);

/**
 * @function LCD_WriteReg (user version)
 * @brief write into a SFR of the LCD
 * @param addr: SFR address; see ILI9320.pdf
 * @param data: 16bit word; see ILI9320.pdf
 * @return none
 */
void LCD_WriteReg(uint16_t addr, uint16_t data);

/**
 * @function LCD_GetWidth
 * @brief return the width of the screen
 * @param none
 * @return coord_t: width of the screen
 */
length_t LCD_GetWidth(void);

/**
 * @function LCD_GetHeight
 * @brief return the height of the screen
 * @param none
 * @return coord_t: height of the screen
 */
length_t LCD_GetHeight(void);

/**
 * @function LCD_SetPos
 * @brief set the cursor position
 * @param x: cursor x
 * @param y: cursor y
 * @return none
 */
void LCD_SetPos(coord_t x, coord_t y);

/**
 * @function LCD_SetWnd
 * @brief set the hardware window
 * @param *rec: pointer to the window clip
 * @return uint32_t: number of pixels contained in the window
 */
void LCD_SetWnd(const rect_st *rec);

/**
 * @function LCD_Put
 * @brief put a pixel on the display, and increment the cursor position
 * @param col: pixel color
 * @return none
 */
void LCD_Put(color_t col);

#endif
