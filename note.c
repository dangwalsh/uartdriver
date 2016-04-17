/*
 * note.c
 *
 *  Created on: Apr 17, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "note.h"

void Note_Init(void) {
	SYSCTL->RCGCGPIO |= (1<<1);
	GPIOB->PCTL &= ~(1<<5);
	GPIOB->AMSEL &= ~(1<<5);
	GPIOB->AFSEL &= ~(1<<5);
	GPIOB->DEN |= (1<<5);
	GPIOB->DIR |= (1<<5);
}

void Note_On(void) {
	GPIOB->DATA |= (1<<5);
}

void Note_Off(void) {
	GPIOB->DATA &= ~(1<<5);
}

void Note_Toggle(int event) {
	GPIOB->DATA ^= (event<<5);
}
