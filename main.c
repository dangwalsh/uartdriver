/*
 * main.c
 *
 *  Created on: Apr 9, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "uart.h"

int main() {
	UART_Init(31250);
	char c = UART_InChar();
	return 0;
}

