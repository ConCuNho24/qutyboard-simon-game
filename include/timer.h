#ifndef TIMER_H
#define TIMER_H

#include "general_include.h"
#include "pushbutton.h"
#include "display.h"

extern volatile uint16_t elapsed_time;  // Time elapsed (ms) in current state
extern volatile uint16_t pressed_time;  // Duration (ms) a button has been held

/**
 * @brief Initialize timers TCB0 and TCB1 for periodic interrupts.
 *        TCB0: 1 ms tick (increments elapsed_time and pressed_time)
 *        TCB1: 5 ms tick (handles pushbutton debounce and display multiplexing)
 */
void timer_init(void);

#endif
