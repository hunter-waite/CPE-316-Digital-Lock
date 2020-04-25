/*
 * lock.c
 * Miscellaneous functions for the lock
 *  Created on: Apr 25, 2020
 *      Author: Hunter Waite
 */

#include "lock.h"

// changes variables associated with unlocked state and writes
void unlocked_lock(uint8_t *charPosition, uint8_t *unlocked){
    *unlocked = 1;                              // set the lock to unlocked state
    *charPosition = 0;                          // reset character position
    write_unlocked();
}

// Resets the lock and displays and displays the resetting message
void reset_lock(uint8_t *charPosition, uint8_t *unlocked, uint8_t *passReset) {
    int temp = 0;                       // used for dots loop
    char dots[RESET_NUM+1];             // dots for second line reset

    memset(dots,'\0',RESET_NUM+1);      // null terminate

    Clear_LCD();                        // clear screen
    Write_String_LCD("RESETTING", 1);   // write reset to the top line
    Display_Power_LCD(1, 0, 0);         // turn off cursor

    while (temp < RESET_NUM) {          // loop through reset number of times
        memset(dots,' ',RESET_NUM);     // write the dots character array to all spaces
        dots[temp] = '.';
        Write_String_LCD(dots, 2);      // write the dots to the second line
        delay_us(DOT_DELAY);
        temp++;
    }

    delay_us(MISC_DELAY);
    *charPosition = 0;                  // reset variables
    *unlocked = 0;
    *passReset = 0;

    write_locked();                     // write the locked script
    Display_Power_LCD(1, 1, 1);         // turn on cursor
    return;
}

// Writes the locked message to the LCD
void write_locked(){
    Clear_LCD();
    Write_String_LCD("LOCKED", 1);
    Write_String_LCD("ENTER KEY ", 2);
    return;
}

//  Writes the reset password message to the LCD
void write_reset(){
    Clear_LCD();
    Write_String_LCD("CHANGE PASSWORD", 1);
    Write_String_LCD("ENTER NEW KEY ", 2);
    return;
}

// writes unlocked message to screen
void write_unlocked(){
    Clear_LCD();
    Write_String_LCD("UNLOCKED", 1);
    Write_String_LCD("CHANGE PASS '#'", 2);
}

void write_incorrect(){
    Clear_LCD();
    Write_String_LCD("INCORRECT", 1);
    Write_String_LCD("PASSWORD", 2);
}
