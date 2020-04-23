/*
 * lcd.c
 *
 *      Author: Joel
 */

#include "lcd.h"

#define PORT_LCD_DATA   (P4)
#define PORT_LCD_CTL    (P5)
#define BIT_RS          (BIT0)
#define BIT_RW          (BIT1)
#define BIT_E           (BIT2)

void Write_Instr_LCD(uint8_t DATA)
{
    PORT_LCD_CTL->OUT &= ~(BIT_RS | BIT_RW);
    delay_us(3000);
    PORT_LCD_CTL->OUT |= BIT_E;
    delay_us(3000);
    PORT_LCD_DATA->OUT = DATA;
    delay_us(3000);
    PORT_LCD_CTL->OUT &= ~BIT_E;
    delay_us(3000);
}

void Write_Data_LCD(uint8_t DATA)
{
    PORT_LCD_CTL->OUT &= ~(BIT_RW);
    PORT_LCD_CTL->OUT |= BIT_RS;
    delay_us(3000);
    PORT_LCD_CTL->OUT |= BIT_E;
    delay_us(3000);
    PORT_LCD_DATA->OUT = DATA;
    delay_us(3000);
    PORT_LCD_CTL->OUT &= ~BIT_E;
    delay_us(3000);
}

void Write_Char_LCD(char letter)
{
    uint8_t firstNibble = letter & ~(0XF);
    uint8_t secondNibble = ((letter & 0XF) << 4);
    Write_Data_LCD(firstNibble);
    Write_Data_LCD(secondNibble);
}

void Clear_LCD()
{
    Write_Instr_LCD(0X0);
    Write_Instr_LCD(0X1 << 4);
    delay_us(2000);
}

void Home_LCD()
{
    Write_Instr_LCD(0X0);
    Write_Instr_LCD(0X2 << 4);
    delay_us(2000);
}

//Happens after each data transfer
void Entry_Mode_LCD(uint8_t cursorForward, uint8_t shiftOn)
{
    uint8_t entryMode = BIT2 | (cursorForward << 1) | shiftOn;
    Write_Instr_LCD(0X0);
    Write_Instr_LCD(entryMode << 4);
    delay_us(1000);
}

void Display_Power_LCD(uint8_t displayOn, uint8_t cursorOn, uint8_t blinkOn)
{
    uint8_t mode = BIT3 | (displayOn << 2) | (cursorOn << 1) | (blinkOn);
    Write_Instr_LCD(0X0);
    Write_Instr_LCD(mode << 4);
    delay_us(1000);
}

void Shift_Move_LCD(uint8_t shiftDisplay, uint8_t dirRight)
{
    uint8_t mode = (shiftDisplay << 3) | (dirRight << 2);
    Write_Instr_LCD(0X1 << 4);
    Write_Instr_LCD(mode << 4);
    delay_us(1000);
}

void Function_Set_LCD(uint8_t dualLine, uint8_t fiveByTen)
{
    uint8_t mode = (dualLine << 3) | (fiveByTen << 2);
    Write_Instr_LCD(0X2 << 4);
    Write_Instr_LCD(mode << 4);
    delay_us(1000);
}

void secondLine_LCD()
{
    Write_Instr_LCD(0XC << 4);
    Write_Instr_LCD(0X0);
    delay_us(1000);
}

void Write_String_LCD(char string[21], int line)
{
    int i = 0;
    if(line == 1)
        Home_LCD();
    else if(line == 2)
        secondLine_LCD();
    while(string[i] != '\0')
    {
        Write_Char_LCD(string[i]);
        i++;
    }
}

void initialize_LCD()
{
    delay_us(40000);        //Wait 40ms after LCD is turned on

    P4->SEL1 = 0;          //configure all of port 4 as simple I/O
    P4->SEL0 = 0;
    P5->SEL1 = 0;          //configure port 5 as simple I/O
    P5->SEL0 = 0;
    P4->DIR = 0XFF;        //configure port 4 as output
    P5->DIR = 0X07;        //configure port 5.0-2 as output


    Write_Instr_LCD(0X20);      //Set 4-bit (nibble) mode
    delay_us(100000);

    Function_Set_LCD(1, 0);         //sets dual line mode and 5x8 font
    Display_Power_LCD(1, 1, 1);     //display, cursor, and blink on
    Clear_LCD();                    //clear display and move cursor to home
    Entry_Mode_LCD(1, 0);           //Increment mode, display shift off
}




