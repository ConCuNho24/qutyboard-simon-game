#include "seed.h"

// Flag indicating whether the seed has been successfully changed
bool is_seed_changed = false;

// Stores the next valid seed value entered by the user
uint32_t next_game_seed = 0;

// Indicates whether the system is currently in "seed input mode"
bool seed_mode = false;

// Temporary buffer to store user-entered seed characters (hexadecimal)
char seed_buffer[9] = {0};  // 8 chars + null terminator

// Tracks how many characters have been entered for the seed
uint8_t seed_len = 0;

// Flag indicating whether the entered seed so far is valid (contains only hex digits)
bool is_valid_seed = true;

// Holds the current active seed used for the game
uint32_t cur_seed = STUDENT_ID_SEED;

// Handles character-by-character input of a new hexadecimal seed
void handle_seed_input(char c){
    // Validate the character — only '0'-'9' or 'a'-'f' are acceptable
    if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
        is_valid_seed = false;  // Mark the entire seed as invalid
    } 

    // Store the character in the buffer and increment the index
    seed_buffer[seed_len++] = c;

    // When the user has entered the full seed (8 hex digits)
    if (seed_len == SEED_MAX ){
        if(is_valid_seed){  
            // Convert the 8-character hexadecimal string into a 32-bit integer
            uint32_t new_seed_value = 0;
            for (uint8_t i = 0; i < SEED_MAX; i++) {
                char x = seed_buffer[i];
                uint8_t value = (x >= '0' && x <= '9') ? x - '0' : x - 'a' + 10;
                new_seed_value = (new_seed_value << 4) | value; // Shift and combine
            }

            // Update global seed variables
            next_game_seed = new_seed_value;
            cur_seed = next_game_seed;
            is_seed_changed = true;  // Notify main logic that a new seed is available
        }
        else{
            // If invalid characters were entered, discard the seed
            is_seed_changed = false;
        }

        // Return to waiting for game input and reset seed mode
        state = AWAITING_INPUT;
        seed_len = 0;
        seed_mode = false;
    } 
}

// Initializes the system to accept a new seed from the user
void start_seed_mode(void){
    is_valid_seed = true;  // Reset validation flag
    seed_mode = true;      // Enter seed input mode
    seed_len = 0;          // Clear input buffer index
}
