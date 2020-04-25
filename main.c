#include "lock.h"

int main(void)
{
    initialize_LCD();           //initialize LCD
    keypad_init();              //initialize keypad

    char input[LOCK_SIZE];      // input character array of lock size
    uint8_t charPosition = 0;   // location of the character in the array
    uint8_t unlocked = 0;       // determine lock state
    uint8_t passReset = 0;
    char password[LOCK_SIZE] = {'1', '2', '3', '4'};

    write_locked();     // write the locked message

    while(1)
    {
        char temp = keypad_get();   // get the key that is being pressed
        if(temp != 12)              // key is being pressed
        {
            if(temp == '*')         // resets the lock
            {
                reset_lock(&charPosition, &unlocked, &passReset);
            }
            else if(passReset){                     // resetting the password
                if(temp != '#'){
                    Write_Char_LCD(temp);           // write character to screen
                    password[passReset-1] = temp;   // change password at index to new character
                    passReset++;                    // increment index
                }

                delay_us(CHAR_WRITE_DELAY);

                if(passReset > LOCK_SIZE)
                    reset_lock(&charPosition, &unlocked, &passReset);
            }
            else if(temp == '#' && unlocked){                   // triggers reset password sequence
                passReset = 1;
                write_reset();
            }
            else if(unlocked == 0)                  // basic inputting of characters
            {
                Write_Char_LCD(temp);               // write character to screen
                input[charPosition] = temp;         // set entered password at index to character
                charPosition++;                     // increment character index
                delay_us(CHAR_WRITE_DELAY);         // delay to prevent double inputs
            }

            if(charPosition == LOCK_SIZE)   // if finished inputting password
            {
                delay_us(MISC_DELAY);
                // if the password is correct display unlocked message
                if(strncmp(input, password, sizeof(input)) == 0)
                {
                    unlocked_lock(&charPosition, &unlocked);
                }
                else    // if not correct reset to locked screen
                {
                    write_incorrect();
                    delay_us(MISC_DELAY);
                    reset_lock(&charPosition, &unlocked, &passReset);
                }
            }
        }
    }
}   //end main
