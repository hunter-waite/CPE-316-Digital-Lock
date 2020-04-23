/*
 * keypad.h
 *
 *  Created on: Apr 19, 2020
 *      Author: Hunter
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "msp.h"
#include "delay.h"

/*
 * Keypad connections
 * When keypad is face up from left to right
 * keypad:  0       1       2       3       4       5       6
 * msp:     2.7     2.6     2.4     5.6     6.6     6.7     2.3
 * R/C:     ROW0    ROW1    ROW2    ROW3    COL0    COL1    COL2
 */


// define row and column bits to be used
#define COL0    (BIT6)
#define COL1    (BIT7)
#define COL2    (BIT3)

#define ROW0    (BIT7)
#define ROW1    (BIT6)
#define ROW2    (BIT4)
#define ROW3    (BIT6)

void keypad_init();
uint8_t keypad_get();
void set_columns();
void clear_columns();

#endif /* KEYPAD_H_ */
