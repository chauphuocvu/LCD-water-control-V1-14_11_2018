#ifndef __UARTSTDIO__
#define __UARTSTDIO__


#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/	 
#include <stdarg.h>
#include "stm32f4xx.h"
#include <stdio.h>

/* Exported functions --------------------------------------------------------*/  	 
void UART_GPIO_Configuration(void);
void UARTstdio_Configuration(USART_TypeDef* Uartx,uint32_t BaudRate);
int UARTwrite(const char *pcBuf, unsigned long ulLen);
unsigned char UARTgetc(void);
unsigned int UARTgets(char *pcBuf, unsigned long ulLen);
void UARTprintf(const char *pcString, ...);

#endif
