#include "octave.h"

// Lookup table for tone periods across 9 octaves
// Each row represents one octave, each column represents a specific note frequency.
// Values are timer periods (in microseconds or timer ticks) used to generate tones.
// Smaller period = higher pitch frequency.
const uint32_t per_table[9][4] = {
    {82222, 98039, 61689, 164444},   // Octave 0 - lowest frequency range
    {41111, 49020, 30844, 82222},    // Octave 1
    {20556, 24510, 15422, 41156},    // Octave 2
    {10278, 12255, 7716, 20556},     // Octave 3 - default starting octave
    {5139,  6127,  3858, 10278},     // Octave 4
    {2569,  3063,  1929, 5139},      // Octave 5
    {1285,  1531,   965, 2569},      // Octave 6
    {642,    765,   482, 1285},      // Octave 7
    {321,    382,   241, 642}        // Octave 8 - highest frequency range
};

// Current octave index (starts at 3 by default)
uint8_t octave = 3;

// Increase the octave by 1 step (higher pitch)
// Ensures it does not exceed the maximum of 8
void octave_inc(void) {
    if (octave < 8) {
        octave++;
    }
}

// Decrease the octave by 1 step (lower pitch)
// Ensures it does not go below 0
void octave_dec(void) {
    if (octave > 0) {
        octave--;
    }
}
