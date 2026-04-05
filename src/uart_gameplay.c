#include "uart_gameplay.h"

bool is_uart_input = false;    // Indicates if the last input came from UART (vs push button)
uint16_t uart_result;          // Stores the numeric result corresponding to UART key press

// Detects and handles UART input during gameplay
void detect_uart(void){
    if (uart_available()) {                        // Check if a character is available in UART buffer
        char c = uart_getc_nonblocking();          // Read character without blocking program execution

        // Reset game immediately if user sends '0' or 'p'
        if (c == '0' || c == 'p') {
            reset_game();
        }

        // If currently in name entry state, pass input to name handler
        if (state == NAME_INPUT) {
            handle_name_input(c);
        }

        // If in seed entry mode, handle input as hexadecimal seed
        else if (seed_mode) {
            handle_seed_input(c);
        } 

        // Otherwise, interpret input as gameplay control
        else {
            switch (c) {

                // Octave control — both letter and symbol keys supported
                case 'k': case ',': 
                    octave_inc();                  // Increase current octave
                    break;
                case 'l': case '.': 
                    octave_dec();                  // Decrease current octave
                    break;

                // Player move input: map multiple keys to the same color index (0–3)
                case '1': case 'q':
                case '2': case 'w':
                case '3': case 'e':
                case '4': case 'r':
                    handle_game_choice_keyboard(c);
                    break;

                // Enter seed input mode — user can type 8 hex digits afterward
                case '9': case 'o':
                    start_seed_mode();
                    break; 

                default:
                    break;                         // Ignore all other characters
            }
        }
    }
}

// Resets gameplay state if not currently entering name or seed
void reset_game(void){
    if (!seed_mode && state != NAME_INPUT) {
        octave = 3;                                // Reset octave to default
        init_LFSR(cur_seed);                       // Initialize random sequence generator with current seed
        reset_LFSR();                              // Reset sequence state
        sequence_index = 0;                        // Reset current sequence progress
        sequence_length = 1;                       // Start with 1 element sequence
        state = SIMON_GENERATE;                    // Transition to sequence generation state
        return; 
    }
}

// Handles player input received via UART instead of physical button
void handle_game_choice_keyboard(char c){
    if (state == AWAITING_INPUT) {                 // Only accept input when waiting for user
        is_uart_input = true;                      // Mark that this input came from UART
        state = HANDLE_INPUT;                      // Move to input handling state
        elapsed_time = 0;                          // Reset timer for input duration tracking
        
        // Map UART key to corresponding color index (0–3)
        if(c == '1' || c == 'q') { uart_result = 0; }
        else if(c == '2' || c == 'w') { uart_result = 1; }
        else if(c == '3' || c == 'e') { uart_result = 2; }
        else if(c == '4' || c == 'r') { uart_result = 3; }

        // Provide immediate feedback (sound and LED display)
        play_sound(uart_result);                   // Play tone for selected color
        display_segs(uart_result);                 // Display the corresponding segment
    }
}
