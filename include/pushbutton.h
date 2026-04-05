#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <stdint.h> 
#include <avr/io.h>

extern volatile uint8_t pb_debounced;   // Debounced state of physical pushbuttons
extern uint8_t pb_rising, pb_falling;   // Rising and falling edge detection

/**
 * @brief Debounces the pushbutton inputs using a vertical counter algorithm.
 *        Updates pb_debounced accordingly.
 */
void pb_debounce(void);

/**
 * @brief Initializes the pushbutton pins with pull-up resistors enabled.
 */
void pb_init(void);

#endif
