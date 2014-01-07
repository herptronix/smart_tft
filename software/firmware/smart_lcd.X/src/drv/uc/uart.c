/**
 * @file uart.c
 * @brief PIC32 uart driver
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-23
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

#include "uart.h"
#include "hw_config.h"

/**
 * local variables
 */
static void (*pUsrIsr)(uint8_t byte) = NULL;


/**
 * @function UartMaskRxInterrupt
 * @brief mask RX ISR
 * @param none
 * @return none
 */
void UartMaskRxInterrupt(void) {
  INTEnable(INT_SOURCE_UART_RX(UART5), INT_DISABLED);
}


/**
 * @function UartUnmaskRxInterrupt
 * @brief unmask RX ISR
 * @param none
 * @return none
 */
void UartUnmaskRxInterrupt(void) {
  INTEnable(INT_SOURCE_UART_RX(UART5), INT_ENABLED);
}


/**
 * @function UartConfigure
 * @brief configure & turn on the uart
 * @param uint32_t speed: desired speed, in bauds
 * @return none
 */
void UartConfigure(uint32_t speed) {

  UARTConfigure(UART5, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetFifoMode(UART5, UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART5, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART5, PER_CLK, speed);
  
  UartUnmaskRxInterrupt();
  INTSetVectorPriority(INT_VECTOR_UART(UART5), INT_PRIORITY_LEVEL_2);
  INTSetVectorSubPriority(INT_VECTOR_UART(UART5), INT_SUB_PRIORITY_LEVEL_0);

  UARTEnable(UART5, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}


/**
 * @function UartRegisterRxISR
 * @brief register an external function as RX ISR handler
 * @param void (*pFunc)(uint8_t byte): pointer to the external handler
 * @return none
 */
void UartRegisterRxISR(void (*pFunc)(uint8_t byte)) {
  pUsrIsr = pFunc;
}


/**
 * @function UartSendByte
 * @brief put a byte on TX
 * @param uint8_t b: byte
 * @return none
 */
void UartSendByte(uint8_t b) {
  while(!UARTTransmitterIsReady(UART5));
  UARTSendDataByte(UART5, b);
}


/**
 * @function UartIsr
 * @brief low level RX ISR handler
 * @param uint8_t b: byte
 * @return none
 */
void __ISR(_UART_5_VECTOR, ipl2) UartIsr(void) {

  /*reception handling*/
  if(INTGetFlag(INT_SOURCE_UART_RX(UART5))) {

    /*error flag? just clear it*/
    if(U5STAbits.OERR) U5STAbits.OERR = 0;

    /*byte received? send it to the external handler*/
    if(U5STAbits.URXDA) {
      if(pUsrIsr != NULL) pUsrIsr(U5RXREG);
    }

    /*reception completed*/
    INTClearFlag(INT_SOURCE_UART_RX(UART5));
  }

	/*emission handling... for now, not based on tx interrupt TODO*/
  if( INTGetFlag(INT_SOURCE_UART_TX(UART5))) {
    INTClearFlag(INT_SOURCE_UART_TX(UART5));
  }
}
