#include "delay.h"

// Software delays by usec microseconds
void delay_us (uint32_t usec) {
    int iterations, i;
    switch(CS->CTL0){
        case FREQ_1_5MHZ:   // 1.5 MHz 29.9 usec without any loops min delay 29900 nanoseconds
            iterations = (usec * 1000-50000) / 7289+ (((usec * 1000-50000) % 7289) > 0);
            for(i = 0; i < iterations; i++);
            break;
        case FREQ_3MHZ: // 3 MHz
            iterations = (usec * 1000-26000) / 3644+ (((usec * 1000-26000) % 3644) > 0);
            for(i = 0; i < iterations; i++);
            break;
        case FREQ_6MHZ: // 6 MHz
            iterations = (usec * 1000-13600) / 1821+ (((usec * 1000-13600) % 1821) > 0);
            for(i = 0; i < iterations; i++);
            break;
        case FREQ_12MHZ:    // 12 MHz
            iterations = (usec * 1000-7000) / 911+ (((usec * 1000-7000) % 911) > 0);
            for(i = 0; i < iterations; i++);
            break;
        case FREQ_24MHZ:    // 24 MHz
            iterations = (usec * 1000* 10-(3700* 10)) / 4554+ (((usec * 1000* 10-(3700* 10)) % 4554) > 0);
            for(i = 0; i < iterations; i++);
            break;
        case FREQ_48MHZ:    // 48 MHz
            // advised against doing 48 MHz for now
            break;
        default:    // Defaults to 1.5 MHz
            iterations = (usec * 1000-50000) / 7289+ (((usec * 1000-50000) % 7289) > 0);
            for(i = 0; i < iterations; i++);
            break;
    }
}

// sets the MCLK frequency to the selected DCO Frequency
void set_DCO (uint32_t freq) {
    CS->KEY = CS_KEY_VAL;   // enables write access to the CS registers
    CS -> CTL0 = 0;         // clear the frequency
    switch (freq) {         // selects what frequency to run the DCO Clock on
        case FREQ_1_5MHZ:   // 1.5 MHz
            CS->CTL0 = FREQ_1_5MHZ;
            break;
        case FREQ_3MHZ: // 3 MHz
            CS->CTL0 = FREQ_3MHZ;
            break;
        case FREQ_6MHZ: // 6 MHz
            CS->CTL0 = FREQ_6MHZ;
            break;
        case FREQ_12MHZ:    // 12 MHz
            CS->CTL0 = FREQ_12MHZ;
            break;
        case FREQ_24MHZ:    // 24 MHz
            CS->CTL0 = FREQ_24MHZ;
            break;
        case FREQ_48MHZ:    // 48 MHz
            // advised against doing 48 MHz for now
            CS->CTL0 = FREQ_1_5MHZ;
            break;
        default:    // Defaults to 1.5 MHz
            CS->CTL0 = FREQ_1_5MHZ;
            break;
    }
    CS->CTL1 |= CS_CTL1_SELM__DCOCLK;   // make sure the DCO uses M Clock
    CS->KEY = 0;    // Block unwanted access to the clocks
}
