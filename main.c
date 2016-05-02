/*
 * main.c
 *
 *  Created on: Apr 9, 2016
 *      Author: danielwalsh
 */

#include "TM4C123GH6PM.h"
#include "bsp.h"
#include "midi.h"
#include "note.h"

volatile static uint32_t adcResult;

void ADC1Seq3_IRQHandler(void) {
	adcResult = ADC1->SSFIFO3;
	ADC1->ISC = (1 << 3);
}

int main() {
	uint16_t duty = 0;
	int tick = 0;
	int sequence[] = {

		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	};

	Timer_Init();
	Note_Init();
	Midi_Init();
	Pitch_Init();
	PWM0_Init(18000, duty);

	while(1) {
		char c = Midi_InChar();
		if (c == 0xF8) {
			PWM0->_0_CMPA = adcResult * 4;
			Note_Toggle(sequence[tick]);
			if (tick >= 96)
				tick = 0;
			else
				tick++;
		}
	}
}

