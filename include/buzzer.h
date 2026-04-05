#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <avr/io.h>
#include "octave.h"

#define F_TIMER 3333333UL  /**< Timer clock frequency in Hz */

/**
 * @brief Initializes the buzzer module.
 *        Configures the timer/counter for PWM output to drive the buzzer.
 */
void buzzer_init(void);

/**
 * @brief Plays a sound corresponding to a given step.
 * @param step Index of the note (0–3) to play, mapped to frequency table.
 */
void play_sound(uint8_t step);

/**
 * @brief Stops any currently playing sound on the buzzer.
 */
void stop_sound(void);

#endif
