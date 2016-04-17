/*
 * sequencer.c
 *
 *  Created on: Apr 15, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"


void Sequencer_Init(uint16_t period, uint16_t duty) {
	SYSCTL->RCGCPWM  |=  0x01;
	SYSCTL->RCGCGPIO |=  0x02;
	while((SYSCTL->PRGPIO & 0x02) == 0) { }
	GPIOB->AFSEL     |=  0x40;
	GPIOB->PCTL       = (GPIOB->PCTL & 0xF0FFFFFF) + 0x04000000;
	GPIOB->AMSEL     &= ~0x40;
	GPIOB->DEN       |=  0x40;
	SYSCTL->RCC       =  0x00100000 | (SYSCTL->RCC & (~0x000E0000));
	PWM0->_0_CTL      =  0x00;
	PWM0->_0_GENA     =  0xC8;
	PWM0->_0_LOAD     =  period - 1;
	PWM0->_0_CMPA     =  duty - 1;
	PWM0->_0_CTL     |=  0x00000001;
	PWM0->ENABLE     |=  0x00000001;
}

void Sequencer_Play(int duty) {
	PWM0->_0_CMPA = duty;
}
