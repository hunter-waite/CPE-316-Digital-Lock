/*
 * lcd.h
 *      Author: Joel
 */

#include "msp.h"
#include "delay.h"

#ifndef LCD_H_
#define LCD_H_

#define PORT_LCD_DATA   (P4)
#define PORT_LCD_CTL    (P5)
#define BIT_RS          (BIT0)
#define BIT_RW          (BIT1)
#define BIT_E           (BIT2)

void Write_Instr_LCD(uint8_t DATA);
void Write_Data_LCD(uint8_t DATA);
void Write_Char_LCD(char letter);
void Clear_LCD();
void Home_LCD();
void Entry_Mode_LCD(uint8_t cursorForward, uint8_t shiftOn);
void Display_Power_LCD(uint8_t displayOn, uint8_t cursorOn, uint8_t blinkOn);
void Shift_Move_LCD(uint8_t shiftDisplay, uint8_t dirRight);
void Function_Set_LCD(uint8_t dualLine, uint8_t fiveByTen);
void secondLine_LCD();
void Write_String_LCD(char string[21], int line);
void initialize_LCD();

#endif /* LCD_H_ */



