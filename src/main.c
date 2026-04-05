#include "general_include.h"
#include "sequence.h"
#include "initialisation.h"
#include "game_state.h"
#include "adc.h"
#include "uart_gameplay.h"
#include "global_var.h"
#include "main_gameplay.h"

// Define the initial game state
Game_State state = SIMON_GENERATE;

// Game variables
uint8_t sequence_length = 1;
uint8_t sequence_index = 0;
uint16_t playback_delay = MIN_PLAYBACK_DELAY; 

uint8_t current_sequence = 1;
uint16_t current_score = 0;
uint16_t pin_playback_delay;

// Function prototypes
void state_machine(void);
uint8_t pb_rising, pb_falling;

int main(void){
    // Disable global interrupts during initialization
    cli();

    // Initialize all required peripherals (buttons, timer, ADC, display, UART, etc.)
    initialisation();

    // Enable global interrupts after initialization
    sei();

    // Start the main game loop (this function never returns)
    state_machine();

    // Infinite loop as a safety fallback (should never reach here)
    while (1);
}

// Main state machine controlling the entire game flow
void state_machine(void){
    // Initialize pseudo-random sequence generator using LFSR with student ID as seed
    cur_seed = STUDENT_ID_SEED;
    init_LFSR(cur_seed);

    uint8_t pb_state = 0xFF;   // Current button state (all released initially)
    uint8_t pb_state_r = 0xFF; // Previous button state
    uint8_t pb_changed;        // Tracks state changes between iterations

    while (1)
    {  
        // Update button state tracking
        pb_state_r = pb_state;
        pb_state = pb_debounced;     // Read the latest debounced button values

        // Detect button transitions by XORing previous and current states
        pb_changed = pb_state_r ^ pb_state;

        // Identify falling edge (button pressed)
        pb_falling = pb_changed & pb_state_r;

        // Identify rising edge (button released)
        pb_rising = pb_changed & pb_state;

        // Dynamically adjust playback delay using the ADC value
        // Maps ADC range (0–255) to the delay range (MIN–MAX)
        playback_delay = (((uint16_t)(MAX_PLAYBACK_DELAY - MIN_PLAYBACK_DELAY) * ADC0.RESULT) >> 8) + MIN_PLAYBACK_DELAY;
        
        // Check UART input to deal with gameplay
        detect_uart();

        // Main state machine controlling the Simon game flow
        switch(state){
            case SIMON_GENERATE:
                // Generate a new sequence to be displayed to the player
                simon_generate();
                break;     

            case SIMON_PLAY_ON:
                // Turn LEDs/sounds ON during sequence playback
                simon_play_on();
                break;
            
            case SIMON_PLAY_OFF:
                // Turn LEDs/sounds OFF between sequence elements
                simon_play_off();
                break;
            
            case AWAITING_INPUT:
                // Wait for player button input
                awaiting_input();
                break;
            
            case HANDLE_INPUT:
                // Handle a single input press and store player’s choice
                handle_input();
                break;
            
            case HANDLE_PRESS_CASE:
                // Determine which button was pressed and react accordingly
                handle_press_case();
                break;

            case EVALUATE_INPUT:
                // Check if player's input matches the generated sequence
                evaluate_input();
                break;

            case FAIL_STATE:
                // Trigger failure effects and show loss message
                fail_state();
                break;
                
            case DISP_SCORE:
                // Display the final score to the player
                disp_score();
                break;

            case NAME_INPUT:
                // Allow player to enter their name for the high score list
                name_input();
                break;

            case FINISH_NAME_INPUT:
                // Finalize name entry and save to high score table
                finish_name_input();
                break;

            case AFTER_SCORE:
                // Leave a blank before jump into new game
                after_score();
                break;
                
            case SUCCESS_STATE:
                // Display success animation and proceed to next round
                success_state();
                break;

            default:
                // Fallback to initial state in case of undefined state
                state = SIMON_GENERATE;
        }
    }
}
