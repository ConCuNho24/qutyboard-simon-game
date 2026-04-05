#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "pushbutton.h"
#include "timer.h"
#include "buzzer.h"
#include "adc.h"
#include "display.h"
#include "uart.h"
#include "octave.h"

/**
 * @brief Initializes all hardware peripherals required for the Simon game:
 *        - Pushbuttons
 *        - Timers (TCB0, TCB1)
 *        - Buzzer
 *        - ADC (for playback delay)
 *        - 7-segment display
 *        - UART
 *        - Default octave
 */
void initialisation(void);

#endif
