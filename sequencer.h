/*
 * sequencer.h
 *
 *  Created on: Apr 12, 2016
 *      Author: danielwalsh
 */

#ifndef SEQUENCER_H_
#define SEQUENCER_H_

void Sequencer_Init(uint16_t period, uint16_t duty);
void Sequencer_Play(int);

#endif /* SEQUENCER_H_ */
