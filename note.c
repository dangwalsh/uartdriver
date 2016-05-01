/*
 * note.c
 *
 *  Created on: Apr 17, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "note.h"


void Timer_Init(void) {
	SYSCTL->RCGCPWM  = (1<<0);
	SYSCTL->RCGCADC  = (1<<1);
	SYSCTL->RCGCGPIO = (1<<1)|(1<<4)|(1<<3);
}

void Note_Init(void) {
	GPIOB->PCTL  &= ~(1<<5);
	GPIOB->AMSEL &= ~(1<<5);
	GPIOB->AFSEL &= ~(1<<5);
	GPIOB->DEN   |=  (1<<5);
	GPIOB->DIR   |=  (1<<5);
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


void Pitch_Init(void) {
	GPIOE->DIR      &= ~(1<<1);
	GPIOE->AFSEL     =  (1<<1);
	GPIOE->DEN      &= ~(1<<1);
	GPIOE->AMSEL     =  (1<<1);

	ADC1->ACTSS     &= ~(1<<3);
	ADC1->EMUX       =  (0xF<<12);
	ADC1->SSMUX3     =  2;
	ADC1->SSCTL3     =  0x06;
	ADC1->IM         =  (1<<3);
	ADC1->ACTSS     |=  (1<<3);
	ADC1->ISC        =  (1<<3);
	NVIC_EnableIRQ(ADC1SS3_IRQn);
}

void PWM0_Init(uint16_t period, uint16_t duty){
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

void PWM0_Duty(uint16_t duty) {
	PWM0->_0_CMPA = duty - 1;
}

