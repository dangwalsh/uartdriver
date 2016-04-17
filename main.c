/*
 * main.c
 *
 *  Created on: Apr 9, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "uart.h"
#include "note.h"



int main() {
	int i = 0;
	int sequence[96] = { 0 };

	sequence[0] = 1;
	sequence[12] = 1;

	sequence[24] = 1;
	sequence[36] = 1;

	sequence[48] = 1;
	sequence[60] = 1;

	sequence[72] = 1;
	sequence[84] = 1;

	Note_Init();
	UART_Init();

	while(1) {
		char c = UART_InChar();
		if (c == 0xF8) {
			Note_Toggle(sequence[i]);
			if (i >= 96)
				i = 0;
			else
				i++;
		}
	}
}

