#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdint.h>

#define MASK 0xE2025CABU  // Polynomial mask used for the LFSR feedback

/**
 * @brief Initialize the LFSR with a given seed (student number).
 * @param student_number Initial seed for LFSR
 */
void init_LFSR(uint32_t student_number);

/**
 * @brief Generate the next step (2-bit value) from the LFSR.
 * @return Next sequence step (0–3)
 */
uint8_t next_step(void);

/**
 * @brief Reset the LFSR state back to the original seed.
 */
void reset_LFSR(void);

/**
 * @brief Set a new seed for the LFSR without changing the current state.
 * @param new_seed New seed value
 */
void set_seed(uint32_t new_seed);

/**
 * @brief Advance the LFSR state and update the seed to match current state.
 */
void advanced_LFSR(void);

#endif
