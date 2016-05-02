/*
 * note.h
 *
 *  Created on: Apr 17, 2016
 *      Author: danielwalsh
 */

#ifndef NOTE_H_
#define NOTE_H_



void Timer_Init(void);
void Note_Init(void);
void Note_Toggle(int);
void Pitch_Init(void);
void PWM0_Init(uint16_t period, uint16_t duty);
void PWM0_Duty(uint16_t duty);

#endif /* NOTE_H_ */
