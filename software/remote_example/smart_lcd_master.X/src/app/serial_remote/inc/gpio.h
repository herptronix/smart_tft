/**
 * @file gpio.h
 * @brief macro for gpio management
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

#ifndef _gpio_h_
#define _gpio_h_

#include "main.h"

/*GPIO direction constant*/
#define GPIO_PIN_INPUT      1
#define GPIO_PIN_OUTPUT     0
#define GPIO_PORT_OUTPUT    0x0000
#define GPIO_PORT_INPUT     0xFFFF
#define GPIO_ANALOG         0
#define GPIO_DIGITAL        1

/*
 * GPIO macro for single pin management
 */

/*example:
 * GPIO_SetPinDirection(B, 4, GPIO_PIN_OUTPUT); <==> TRISBbits.TRISB4 = 0
 * GPIO_SetPin(B, 4, 1);                        <==> LATBbits.LATB4 = 1
 */
#define GPIO_SetPinDirection(port, pin, dir)        private_indirect_gpio_pin(TRIS, port, pin) = dir
#define GPIO_SetPin(port, pin, state)               private_indirect_gpio_pin(LAT , port, pin) = state
#define GPIO_GetPin(port, pin)                      private_indirect_gpio_r_pin(PORT, port, pin)
#define GPIO_SetPinMode(pin, mode)                  private_indirect_gpio_mode(pin) = mode
/*
 * GPIO macro for a whole port management
 */

/*example:
 * GPIO_SetPortDirection(B, GPIO_PORT_INPUT);   <==> TRISB = 0xFFFF;
 * a = GPIO_GetPort(B);                         <==> a = PORTB
 */
#define GPIO_SetPortDirection(port, dir)            private_indirect_gpio_port(TRIS, port) = dir
#define GPIO_SetPort(port, state)                   private_indirect_gpio_port(LAT, port) = state
#define GPIO_GetPort(port)                          private_indirect_gpio_port(PORT, port)


/*don't use it in your code!*/
#define private_indirect_gpio_pin(reg, port, pin)   reg##port##bits.reg##port##pin
#define private_indirect_gpio_r_pin(reg, port, pin) reg##port##bits.R##port##pin
#define private_indirect_gpio_port(reg, port)       reg##port
#define private_indirect_gpio_mode(pin)             AD1PCFGbits.PCFG##pin

#endif
