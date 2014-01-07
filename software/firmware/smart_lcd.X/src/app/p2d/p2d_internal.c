/**
 * @file p2d_internal.c
 * @brief p2d internal data
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

/*P2D context*/
context_st context;

/*redirected functions*/
PutFunc_t Put = LCD_Put;
SetWndFunt_t SetWnd = LCD_SetWnd;
SetPosFunc_t SetPos = LCD_SetPos;
GetWidthFunc_t GetWidth = LCD_GetWidth;
GetHeightFunc_t GetHeight = LCD_GetHeight;
