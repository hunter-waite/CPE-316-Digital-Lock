#include "msp.h"
#include "keypad.h"
#include "lcd.h"
#include "delay.h"

/**
 * Digital Lock for CPE316
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}
