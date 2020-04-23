#include "msp.h"
#include "keypad.h"
#include "LCD.h"
#include "delay.h"
#include <string.h>

int main(void)
{
    initialize_LCD();           //initialize LCD
    keypad_init();              //initialize keypad
    char input[4];
    int charPosition = 0;
    int unlocked = 0;
    char password[] = {'1', '2', '3', '4'};

    while(1)
    {
        Write_String_LCD("LOCKED", 1);
        Write_String_LCD("ENTER KEY ", 2);

        while(1)
        {
            char temp = keypad_get();   //get the key that is being pressed
            if(temp != 12)              //key is being pressed
            {
                if(temp == '*')
                {
                    Clear_LCD();
                    charPosition = 0;
                    unlocked = 0;
                    Write_String_LCD("LOCKED", 1);
                    Write_String_LCD("ENTER KEY ", 2);
                }
                else if(unlocked == 0)
                {
                    Write_Char_LCD(temp);
                    input[charPosition] = temp;
                    charPosition++;
                    delay_us(500000);
                }

                if(charPosition == 4)
                {
                    Clear_LCD();
                    delay_us(1500000);
                    if(strncmp(input, password, sizeof(input)) == 0)
                    {
                        unlocked = 1;
                        charPosition = 0;
                        Write_String_LCD("UNLOCKED", 1);
                    }
                    else
                    {
                        Write_String_LCD("LOCKED", 1);
                        Write_String_LCD("ENTER KEY ", 2);
                        charPosition = 0;
                    }
                }
            }
        }
    }


}   //end main
