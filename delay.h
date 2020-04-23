/*
 * delay.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Hunter
 */
#include "msp.h"


#ifndef DELAY_H_
#define DELAY_H_

#define FREQ_1_5MHZ CS_CTL0_DCORSEL_0
#define FREQ_3MHZ CS_CTL0_DCORSEL_1
#define FREQ_6MHZ CS_CTL0_DCORSEL_2
#define FREQ_12MHZ CS_CTL0_DCORSEL_3
#define FREQ_24MHZ CS_CTL0_DCORSEL_4
#define FREQ_48MHZ CS_CTL0_DCORSEL_5

void set_DCO(uint32_t freq);
void delay_us(uint32_t sec);

#endif /* DELAY_H_ */
