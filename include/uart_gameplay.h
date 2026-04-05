#ifndef UARTGAMEPLAY_H
#define UARTGAMEPLAY_H

#include "uart.h"
#include "global_var.h"
#include "game_state.h"
#include "timer.h"
#include "octave.h"
#include "buzzer.h"
#include "display.h"
#include "sequence.h"
#include "highscore.h"
#include "seed.h"

extern bool is_uart_input;              ///< True if input came from UART
extern uint16_t uart_result;            ///< Stores button value (0-3) from UART

/**
 * @brief Checks for incoming UART data and handles it based on current game state.
 *        Can trigger seed input, name input, game controls, or octave adjustments.
 */
void detect_uart(void);

/**
 * @brief Resets the game to initial state if not in seed input or name input mode.
 *        Resets sequence, LFSR, and octave.
 */
void reset_game(void);

/**
 * @brief Handles single character input for the highscore name buffer.
 * @param c Character received from UART
 */
void handle_name_input(char c);

/**
 * @brief Processes a single character input for seed collection.
 * @param c Character received from UART
 */
void handle_seed_input(char c);

/**
 * @brief Maps keyboard input to button presses in the game.
 *        Updates uart_result and triggers sound/display.
 * @param c Character received from UART
 */
void handle_game_choice_keyboard(char c);

/**
 * @brief Starts seed collection mode by resetting related flags and buffer.
 */
void start_seed_mode(void);

#endif
