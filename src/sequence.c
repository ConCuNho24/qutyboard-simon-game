#include "sequence.h"

static uint32_t STATE_LFSR = 0;   // Current LFSR state used to generate random steps
static uint32_t SEED = 0;         // Initial seed value used for reset and reproducibility

// Initialize the LFSR with a given seed (e.g., student number)
void init_LFSR(uint32_t student_number) {
    SEED = student_number;
    STATE_LFSR = SEED;
}

// Generate the next pseudo-random 2-bit step (values 0–3)
uint8_t next_step(void) {
    uint32_t bit = STATE_LFSR & 1U;   // Extract least significant bit
    STATE_LFSR >>= 1;                 // Shift the register right by one bit
    if (bit) {
        STATE_LFSR ^= MASK;           // Apply XOR feedback when LSB is 1
    }
    return (uint8_t)(STATE_LFSR & 0b11);  // Return the lowest two bits for Simon step
}

// Reset LFSR state back to its seed (restarts sequence)
void reset_LFSR(void) {
    STATE_LFSR = SEED;
}

// Set a new seed value without immediately resetting the LFSR
void set_seed(uint32_t new_seed) {
    SEED = new_seed;
}

// Save the current LFSR state as the new seed (advances randomness between games)
void advanced_LFSR(void){
    SEED = STATE_LFSR;
}
