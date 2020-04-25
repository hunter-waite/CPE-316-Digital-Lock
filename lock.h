/*
 * lock.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Hunter
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "msp.h"
#include "keypad.h"
#include "LCD.h"
#include "delay.h"
#include <string.h>

#define RESET_NUM 5
#define LOCK_SIZE 4
#define CHAR_WRITE_DELAY 500000
#define DOT_DELAY 200000
#define MISC_DELAY 800000

void unlocked_lock(uint8_t *charPosition, uint8_t *unlocked);
void reset_lock(uint8_t *charPosition, uint8_t *unlocked, uint8_t *passReset);
void write_locked();
void write_reset();
void write_unlocked();
void write_incorrect();

#endif /* LOCK_H_ */
