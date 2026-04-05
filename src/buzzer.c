#include "buzzer.h"

// Initialize buzzer on PB0 using TCA0 in single-slope PWM mode
void buzzer_init(void) {
    PORTB.OUTCLR = PIN0_bm;                  // Turn buzzer off initially
    PORTB.DIRSET = PIN0_bm;                  // Set PB0 as output

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc;   // Select clock prescaler /4

    // Single-slope PWM mode, enable WO0 (PB0 output)
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;

    TCA0.SINGLE.PER = 1;                     // PWM period initial value
    TCA0.SINGLE.CMP0 = 0;                    // PWM duty cycle initially 0

    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm; // Enable TCA0
}

// Play a specific tone (0-3) based on current octave
void play_sound(uint8_t tone)
{   
    uint32_t per_old = per_table[octave][tone]; // Get period from lookup table
    uint16_t per_new = (uint16_t)(per_old >> 2); // Scale period for PWM

    TCA0.SINGLE.PERBUF = per_new;            // Update PWM period buffer
    TCA0.SINGLE.CMP0BUF = per_new >> 1;      // Update duty cycle buffer (50%)
}

// Stop buzzer sound
void stop_sound(void)
{
    TCA0.SINGLE.CMP0BUF = 0;                 // Set duty cycle to 0 to silence buzzer
}
