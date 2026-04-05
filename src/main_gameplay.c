#include "main_gameplay.h"

uint8_t step;                // Current step in Simon sequence
uint8_t final_button_choice; // Last button pressed by player (physical or UART)

// Generate the next Simon step and play it
void simon_generate(void){
    if(sequence_index == sequence_length){      
        // Sequence finished, reset LFSR and wait for player input
        reset_LFSR();
        sequence_index = 0;
        state = AWAITING_INPUT;
    }
    else if(sequence_index < sequence_length){
        // If seed has changed (new game), reinitialize LFSR
        if(is_seed_changed){                    
            set_seed(next_game_seed);
            init_LFSR(next_game_seed);
            reset_LFSR();
            is_seed_changed = false;
        }
        step = next_step();                     // Generate next step from LFSR
        play_sound(step);                       // Play corresponding buzzer sound
        display_segs(step);                     // Show step visually on display
        elapsed_time = 0; 
        state = SIMON_PLAY_ON;
    }
}

// Turn on display and buzzer for the current step
void simon_play_on(void){
    if(elapsed_time >= playback_delay/2){      // After half of playback delay
        display_off();                         // Turn off LED segments
        stop_sound();                           // Stop buzzer
        state = SIMON_PLAY_OFF;                // Move to "off" phase
    }  
}

// Turn off display/buzzer and advance sequence
void simon_play_off(void){
    if(elapsed_time >= playback_delay){        // After full playback delay
        sequence_index ++;                     // Move to next step
        state = SIMON_GENERATE;                // Generate next step
    }
}

// Wait for player input
void awaiting_input(void){
    bool is_button_pressed = false;
    uint8_t pressed_button;

    // Detect which physical button is pressed
    if (pb_falling & PIN4_bm) { pressed_button = 0; is_button_pressed = true; }
    else if (pb_falling & PIN5_bm) { pressed_button = 1; is_button_pressed = true; }
    else if (pb_falling & PIN6_bm) { pressed_button = 2; is_button_pressed = true; }
    else if (pb_falling & PIN7_bm) { pressed_button = 3; is_button_pressed = true; }
    
    if (is_button_pressed) {
        play_sound(pressed_button);           // Immediate feedback
        display_segs(pressed_button);         // Light corresponding segment
        final_button_choice = pressed_button; // Record pressed button
        elapsed_time = 0;                      // Reset timers
        pressed_time = 0;
        state = HANDLE_INPUT;                 // Move to handle press duration
    }
}

// Handle player's button press duration and decide next action
void handle_input(void){
    if (!is_uart_input) {                       // Physical button input
        // Check for button release
        if (pb_rising & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm)) {
            if (pressed_time >= playback_delay / 2) { // Long enough press
                display_off();
                stop_sound();
                elapsed_time = 0;
                state = EVALUATE_INPUT;        // Evaluate correctness
            } else {
                state = HANDLE_PRESS_CASE;    // Short press, wait remaining time
            }
        }
    } 
    else {                                      // UART input
        if (elapsed_time >= playback_delay / 2){ // Wait half delay for consistency
            stop_sound();
            display_off();
            final_button_choice = uart_result;   // Use UART button value
            state = EVALUATE_INPUT;
            is_uart_input = false;               // Reset UART flag
        }
    }
}

// Handle case where button was released too early
void handle_press_case(void){
    if (elapsed_time >= playback_delay / 2){    // Wait remaining half delay
        stop_sound();
        display_off();
        state = EVALUATE_INPUT;                 // Then evaluate input
    }
}

// Compare player's input to expected Simon sequence step
void evaluate_input(void){
    step = next_step();                         // Get next expected step
    sequence_index++;
    if (step != final_button_choice){           // Wrong input
        display_fail();                         // Show fail symbol
        elapsed_time = 0;
        state = FAIL_STATE;
    } else {                                    // Correct input
        if (sequence_index == sequence_length){ // Sequence complete
            display_success();                  // Indicate success
            pin_playback_delay = playback_delay;
            reset_LFSR();                        // Reset for next round
            sequence_index = 0;
            sequence_length++;                   // Increase sequence length
            current_sequence = sequence_length;
            elapsed_time = 0;
            state = SUCCESS_STATE;
        } else {
            state = AWAITING_INPUT;             // Wait for next input
        }
    }
}

// Handle failure sequence
void fail_state(void){
    if(elapsed_time >= playback_delay){
        display_score(sequence_length);          // Show player's score
        uart_puts("GAME OVER\n");
        uart_put_uint8(sequence_length);
        uart_puts("\n");
        elapsed_time = 0;
        state = DISP_SCORE;
    }
}

// Display score and prepare for new game or name input
void disp_score(void){
    if(elapsed_time >= playback_delay){
        display_off();
        reset_LFSR();
        for(uint8_t i = 0; i < current_sequence; i++){
            next_step();                         // Advance LFSR to sync sequence
        }
        advanced_LFSR();                          // Move LFSR forward for next game
        current_score = sequence_length;
        sequence_index = 0;
        sequence_length = 1;
        current_sequence = 1;
        elapsed_time = 0;
        if (is_top5(current_score)){              // If score qualifies for highscore
            uart_puts("Enter name: ");
            state = NAME_INPUT;
            elapsed_time = 0;
        } else {
            state = AFTER_SCORE;                  // Otherwise, proceed
        }
    }
}

// Wait for name input timeout (5s)
void name_input(void){
    if (elapsed_time >= 5000){ 
        state = FINISH_NAME_INPUT; 
    }
}

// Finalize name input and update highscores
void finish_name_input(void){
    name_buffer[name_len] = '\0';                // Null terminate name
    insert_highscore(name_buffer, current_score);
    transmit_highscores();                        // Send updated highscore table
    name_len = 0;
    state = SIMON_GENERATE;                       // Start new game
}

// Short delay before starting next game after displaying score
void after_score(void){
    if(elapsed_time >= playback_delay){
        state = SIMON_GENERATE;
    }
}

// Display success feedback and start next sequence
void success_state(void){
    if(elapsed_time > pin_playback_delay){
        display_off();
        state = SIMON_GENERATE;
        uart_puts("SUCCESS\n");
        uart_put_uint8(sequence_length - 1);
        uart_puts("\n");
    }
}
