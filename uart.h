/*
 * uart.h
 *
 *  Created on: Apr 9, 2016
 *      Author: danielwalsh
 */

#ifndef UARTDRIVER_UART_H_
#define UARTDRIVER_UART_H_

void UART_Init(int);
char UART_InChar(void);
void UART_OutChar(char);

#endif /* UARTDRIVER_UART_H_ */
