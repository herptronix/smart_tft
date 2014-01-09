
#ifndef _uart_h_
#define _uart_h_

#include "main.h"

void UartConfigure(uint32_t speed);

void UartRegisterRxISR( void (*pFunc)(uint8_t byte));

void UartSendByte(uint8_t b);

void UartMaskRxInterrupt(void);

void UartUnmaskRxInterrupt(void);
#endif
