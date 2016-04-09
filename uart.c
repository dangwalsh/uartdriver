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
void UART_Init(void) { 			// should be called only once
	SYSCTL->RCGCUART |= 0x0001; 	// activate UART0
	SYSCTL->RCGCGPIO |= 0x0001;	// activate port A

	UART0->CTL &= ~0x0001;		// disable UART
	UART0->IBRD = 43;			// IBRD = int( 80000000/( 16* 115,200)) = int( 43.40278)
	UART0->FBRD = 26;			// FBRD = round( 0.40278 * 64) = 26
	UART0->LCRH = 0x0070;		// 8-bit word length, enable FIFO
	UART0->CTL = 0x0301;			// enable RXE, TXE and UART

	GPIOA->PCTL = (GPIOA->PCTL & 0xFFFFFF00) + 0x00000011; // UART
	GPIOA->AMSEL &= ~0x03;		// TM4C, disable analog on PA1-0
	GPIOA->AFSEL |= 0x03;		// enable alt funct on PA1-0
	GPIOA->DEN |= 0x03;			// enable digital I/ O on PA1-0
}

// Wait for new input, then return ASCII code
char UART_InChar(void) {
	while ((UART0->FR & 0x0010) != 0);// wait until RXFE is 0
	return ((char)(UART0->DR & 0xFF));
}

// Wait for buffer to be not full, then output
void UART_OutChar(char data) {
	while ((UART0->FR & 0x0020) != 0); // wait until TXFF is 0
	UART0->DR = data;
}
