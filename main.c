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
	UART_Init();
	while(1) {
		char c = UART_InChar();
		if (c == 0xF8) {

		}
	}
	return 0;
}

