#include "timer.h"

volatile uint16_t elapsed_time = 0;   // Tracks total time passed in milliseconds
volatile uint16_t pressed_time = 0;   // Tracks button press duration

void timer_init(void) {

    // Configure TCB0 for a 1ms periodic interrupt
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Set timer mode to periodic interrupt
    TCB0.CCMP = 3333;                   // 3333 ticks ≈ 1ms at 3.3 MHz clock
    TCB0.INTCTRL = TCB_CAPT_bm;         // Enable interrupt on compare match
    TCB0.CTRLA = TCB_ENABLE_bm;         // Start TCB0

    // Configure TCB1 for a 5ms periodic interrupt
    TCB1.CTRLB = TCB_CNTMODE_INT_gc;    // Set timer mode to periodic interrupt
    TCB1.CCMP = 16667;                  // 16667 ticks ≈ 5ms at 3.3 MHz clock
    TCB1.INTCTRL = TCB_CAPT_bm;         // Enable interrupt on compare match
    TCB1.CTRLA = TCB_ENABLE_bm;         // Start TCB1
}

// Interrupt Service Routine for TCB0: runs every 1ms
ISR(TCB0_INT_vect) { 
    elapsed_time++;                     // Increment total elapsed time
    pressed_time++;                     // Track how long button has been pressed
    TCB0.INTFLAGS = TCB_CAPT_bm;        // Clear interrupt flag
}

// Interrupt Service Routine for TCB1: runs every 5ms
ISR(TCB1_INT_vect) { 
    pb_debounce();                      
    swap_display_digit();               
    TCB1.INTFLAGS = TCB_CAPT_bm;        // Clear interrupt flag
}
