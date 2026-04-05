#ifndef MAINGAMEPLAY_H
#define MAINGAMEPLAY_H

#include "global_var.h"
#include "sequence.h"
#include "buzzer.h"
#include "seed.h"
#include "display.h"
#include "uart.h"
#include "timer.h"
#include "uart_gameplay.h"
#include "pushbutton.h"
#include "highscore.h"

/**
 * @brief Generates the next step in the Simon sequence and updates the display and sound.
 *        Also handles seed initialization if seed mode is active.
 */
void simon_generate(void);

/**
 * @brief Turns on display and buzzer for the current step during playback.
 */
void simon_play_on(void);

/**
 * @brief Turns off display and buzzer after step playback.
 */
void simon_play_off(void);

/**
 * @brief Waits for user input via pushbuttons and updates state accordingly.
 */
void awaiting_input(void);

/**
 * @brief Handles user input, either from buttons or UART keyboard.
 */
void handle_input(void);

/**
 * @brief Handles short button press cases 
 */
void handle_press_case(void);

/**
 * @brief Compares user input to the expected Simon sequence step and updates game state.
 */
void evaluate_input(void);

/**
 * @brief Handles the fail state: displays fail message, score, and prepares next state.
 */
void fail_state(void);

/**
 * @brief Displays the current score on 7-segment display and manages highscore checking.
 */
void disp_score(void);

/**
 * @brief Handles user name input for entering highscore.
 */
void name_input(void);

/**
 * @brief Finalizes name input and inserts score into highscores.
 */
void finish_name_input(void);

/**
 * @brief Prepares game state to continue after displaying score.
 */
void after_score(void);

/**
 * @brief Handles success state: indicates correct sequence completion and prepares next round.
 */
void success_state(void);

#endif
