#ifndef OCTAVE_H
#define OCTAVE_H

#include <stdint.h>

extern uint8_t octave;                  // Current musical octave
extern const uint32_t per_table[9][4]; // Period table for buzzer tones

/**
 * @brief Increment the current octave by 1, up to a maximum of 8
 */
void octave_inc(void);

/**
 * @brief Decrement the current octave by 1, down to a minimum of 0
 */
void octave_dec(void);

#endif
