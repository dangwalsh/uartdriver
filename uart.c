/*
 * uart.c
 *
 *  Created on: Apr 9, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "uart.h"

// Assumes an 80 MHz bus clock, creates 115200 baud rate
void UART_Init(int baud) { 				// should be called only once
	SYSCTL->RCGCUART |= (1<<1); 			// activate UART1
	SYSCTL->RCGCGPIO |= (1<<1);			// activate port B

	UART1->CTL &= ~(1<<0);				// disable UART
	UART1->IBRD = 32;					// IBRD = int(16000000/(16 * 31250)) = int(32.0)
	UART1->FBRD = 0;						// FBRD = round( 0.0 * 64) = 0
	UART1->LCRH = (0x3<<5);				// 8-bit word length, enable FIFO
	UART1->CC = 0x0;
	UART1->CTL = (1<<0)|(1<<8)|(1<<9);	// enable RXE, TXE and UART

	GPIOB->PCTL = (1<<0)|(1<<4); 		// UART port B pin 0-1
	GPIOB->AMSEL &= ~0x03;				// TM4C, disable analog on PB1-0
	GPIOB->AFSEL |= (1<<0)|(1<<1);		// enable alt funct on PB1-0
	GPIOB->DEN |= (1<<0)|(1<<1);			// enable digital I/O on PB1-0
}

// Wait for new input, then return ASCII code
char UART_InChar(void) {
	char data;
	while ((UART1->FR & (1<<4)) != 0);	// wait until RXFE is 0
	data = (UART1->DR & 0xFF);
	return data;
}

// Wait for buffer to be not full, then output
void UART_OutChar(char data) {
	while ((UART1->FR & (1<<5)) != 0); 	// wait until TXFF is 0
	UART1->DR = data;
}
