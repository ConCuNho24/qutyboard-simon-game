#include "pushbutton.h"

// Stores the current stable (debounced) state of all push buttons.
// Bit value 1 = button released, 0 = button pressed (since pull-ups are enabled).
volatile uint8_t pb_debounced = 0xFF;

// Debouncing routine using a vertical counter method.
// This helps filter out mechanical noise when a button is pressed or released.
void pb_debounce(void) {
    // Two static counters used to track button stability over multiple samples.
    static uint8_t vcount1 = 0;     // Most significant bit of vertical counter
    static uint8_t vcount0 = 0;     // Least significant bit of vertical counter
     
    // Read current raw button input (active-low because of pull-ups)
    uint8_t pb_sample = PORTA.IN;

    // Detect which buttons have changed state compared to the debounced value
    uint8_t pb_changed = pb_sample ^ pb_debounced;

    // Update counters for all bits that changed
    vcount1 = (vcount1 ^ vcount0) & pb_changed;  // Increment high bit conditionally
    vcount0 = ~vcount0 & pb_changed;             // Increment low bit conditionally

    // When both counter bits are set, toggle the debounced output bit
    pb_debounced ^= (vcount0 & vcount1);         
} // pb_debounce

// Initialize push button input pins with internal pull-up resistors.
// This ensures buttons read as '1' (HIGH) when not pressed and '0' when pressed.
void pb_init(void) {
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;   // Enable pull-up for button 1
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;   // Enable pull-up for button 2
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;   // Enable pull-up for button 3
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;   // Enable pull-up for button 4
}
