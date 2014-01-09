
#include "uart.h"
#include "hw_config.h"


static void (*pUsrIsr)(uint8_t byte) = NULL;


void UartMaskRxInterrupt(void) {

}

void UartUnmaskRxInterrupt(void) {
  
}

void UartConfigure(uint32_t speed) {

  UARTConfigure(UART5, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetFifoMode(UART5, UART_INTERRUPT_ON_RX_NOT_EMPTY);
  UARTSetLineControl(UART5, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  UARTSetDataRate(UART5, PER_CLK, speed);
  
  INTEnable(INT_SOURCE_UART_RX(UART5), INT_ENABLED);
  INTSetVectorPriority(INT_VECTOR_UART(UART5), INT_PRIORITY_LEVEL_2);
  INTSetVectorSubPriority(INT_VECTOR_UART(UART5), INT_SUB_PRIORITY_LEVEL_0);

  UARTEnable(UART5, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
}


void UartRegisterRxISR( void (*pFunc)(uint8_t byte)) {
  pUsrIsr = pFunc;
}



void UartSendByte(uint8_t b) {
  while(!UARTTransmitterIsReady(UART5));
  UARTSendDataByte(UART5, b);
  //while(!UARTTransmissionHasCompleted(UART5));
}



void __ISR(_UART_5_VECTOR, ipl2) UartIsr(void) {

  /*reception handling*/
  if(INTGetFlag(INT_SOURCE_UART_RX(UART5))) {

    /*error flag? just clear it*/
    if(U5STAbits.OERR) U5STAbits.OERR = 0;

    /*byte received? send it to the external handler*/
    if(U5STAbits.URXDA) {
      if(pUsrIsr != NULL) {
        pUsrIsr(U5RXREG);
      }
    }

    /*reception completed*/
    INTClearFlag(INT_SOURCE_UART_RX(UART5));
	}

	/*emission handling*/
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART5)))
	{
		INTClearFlag(INT_SOURCE_UART_TX(UART5));
	}
}
