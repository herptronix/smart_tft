/**
 * @file backlight.c
 * @brief lcd backlight driver
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
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

#include "backlight.h"
#include "gpio.h"

#define BACKLIGHT_PORT D
#define BACKLIGHT_PIN 3


/**
 * @function BacklightInit
 * @brief turn on the backlight
 * @param none
 * @return none
 */
void BacklightInit(void) {
  GPIO_SetPin(BACKLIGHT_PORT, BACKLIGHT_PIN, 1);
  GPIO_SetPinDirection(BACKLIGHT_PORT, BACKLIGHT_PIN, GPIO_PIN_OUTPUT);
}

