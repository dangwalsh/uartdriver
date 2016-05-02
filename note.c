/*
 * note.c
 *
 *  Created on: Apr 17, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "note.h"


void Timer_Init(void) {
	SYSCTL->RCGCPWM  |= (1<<0);
	SYSCTL->RCGCADC  |= (1<<1);
	SYSCTL->RCGCGPIO |= (1<<1)|(1<<4)|(1<<3);
}

void Note_Init(void) {
	GPIOB->PCTL  &= ~(1<<5);
	GPIOB->AMSEL &= ~(1<<5);
	GPIOB->AFSEL &= ~(1<<5);
	GPIOB->DEN   |=  (1<<5);
	GPIOB->DIR   |=  (1<<5);
}

void Note_Toggle(int event) {
	GPIOB->DATA ^= (event<<5);
}


void Pitch_Init(void) {
	GPIOE->DIR      &= ~(1<<1);
	GPIOE->AFSEL     =  (1<<1);
	GPIOE->DEN      &= ~(1<<1);
	GPIOE->AMSEL     =  (1<<1);

	ADC1->ACTSS     &= ~(1<<3);
	ADC1->EMUX       =  (0xF<<12);
	ADC1->SSMUX3     =  (1<<1);
	ADC1->SSCTL3     =  (1<<1)|(1<<2);
	ADC1->IM         =  (1<<3);
	ADC1->ACTSS     |=  (1<<3);
	ADC1->ISC        =  (1<<3);
	NVIC_EnableIRQ(ADC1SS3_IRQn);
}

void PWM0_Init(uint16_t period, uint16_t duty){
	SYSCTL->RCGCPWM  |=  (1<<0);
	SYSCTL->RCGCGPIO |=  (1<<1);
	while((SYSCTL->PRGPIO & (1<<1)) == 0) { }

	GPIOB->AFSEL     |=  (1<<6);
	GPIOB->PCTL       = (GPIOB->PCTL & 0xF0FFFFFF) + 0x04000000;
	GPIOB->AMSEL     &= ~(1<<6);
	GPIOB->DEN       |=  (1<<6);

	SYSCTL->RCC       =  0x00100000 | (SYSCTL->RCC & (~0x000E0000));

	PWM0->_0_CTL      =  0x00;
	PWM0->_0_GENA     =  0xC8;
	PWM0->_0_LOAD     =  period - 1;
	PWM0->_0_CMPA     =  duty - 1;
	PWM0->_0_CTL     |=  (1<<0);
	PWM0->ENABLE     |=  (1<<0);
}

void PWM0_Duty(uint16_t duty) {
	PWM0->_0_CMPA = duty - 1;
}

