/*
 * keypad.c
 *
 *  Created on: Apr 19, 2020
 *      Author: Hunter
 */

#include "keypad.h"

// initializes all the pins used in the keypad
void keypad_init() {
    // Initialize rows as inputs
    P2->SEL0 &= ~(ROW0 | ROW1 | ROW2);  // set P6.1 to input
    P2->SEL1 &= ~(ROW0 | ROW1 | ROW2);
    P2->DIR &= ~(ROW0 | ROW1 | ROW2);
    P2->REN |= (ROW0 | ROW1 | ROW2);    // Enable pulldown resistor
    P2->OUT &= ~(ROW0 | ROW1 | ROW2);    // Enable pulldown resistor

    P5->SEL0 &= ~ROW3;  // set P4.0,P4.2,P4.4 to inputs
    P5->SEL1 &= ~ROW3;
    P5->DIR &= ~ROW3;
    P5->REN |= ROW3;    // enable pulldown resistor
    P5->OUT &= ~ROW3;    // enable pulldown resistor

    // Initialize Columns as outputs
    P6->SEL0 &= ~(COL0 | COL1);  // set P4.5,P4.7 to outputs
    P6->SEL1 &= ~(COL0 | COL1);
    P6->DIR |= (COL0 | COL1);

    P2->SEL0 &= ~COL2;  // set P4.5,P4.7 to outputs
    P2->SEL1 &= ~COL2;
    P2->DIR |= COL2;
}

uint8_t keypad_get() {

    set_columns();
    delay_us(100);   // allow signals to settle

    // check if no buttons are pressed
    if( !(P2->IN & (ROW0 | ROW1 | ROW2)) && !(P5->IN & ROW3) )
        return 12;

    // check the first column
    clear_columns();
    P6->OUT |= (COL0);
    delay_us(100);   // allow signals to settle
    if( P2->IN & ROW0 )
        return '1';
    else if ( P2->IN & ROW1 )
        return '4';
    else if ( P2->IN & ROW2 )
        return '7';
    else if ( P5->IN & ROW3 )
        return '*';

    // check the second column
    clear_columns();
    P6->OUT |= (COL1);
    delay_us(100);   // allow signals to settle
    if( P2->IN & ROW0 )
        return '2';
    else if ( P2->IN & ROW1 )
        return '5';
    else if ( P2->IN & ROW2 )
        return '8';
    else if ( P5->IN & ROW3 )
        return '0';

    // check the third column
    clear_columns();
    P2->OUT |= (COL2);
    delay_us(100);   // allow signals to settle
    if( P2->IN & ROW0 )
        return '3';
    else if ( P2->IN & ROW1 )
        return '6';
    else if ( P2->IN & ROW2 )
        return '9';
    else if ( P5->IN & ROW3 )
        return '#';

    // something didn't work
    return 12;
}

// sets all the columns to high
void set_columns() {
    P6->OUT |= (COL0 | COL1);   // set columns high
    P2->OUT |= COL2;
}

// sets all the columns to low
void clear_columns() {
    P6->OUT &= ~(COL0 | COL1);   // set columns low
    P2->OUT &= ~COL2;
}
