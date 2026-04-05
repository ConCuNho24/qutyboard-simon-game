#ifndef SEED_H
#define SEED_H

#define STUDENT_ID_SEED 0x12051632 ///< Default seed for the LFSR, based on student ID
#define SEED_MAX 8                 ///< Maximum length for new seed

#include "general_include.h"
#include "game_state.h"
#include "global_var.h"

extern bool is_seed_changed;            // True if new seed entered via UART
extern uint32_t next_game_seed;         // Stores the new seed value
extern bool seed_mode;                  // True when collecting seed digits
extern char seed_buffer[9];             // Buffer to store 8 hex digits + null
extern uint8_t seed_len;                // Number of seed digits in buffer
extern bool is_valid_seed;              // Tracks if seed digits are valid hex
extern uint32_t cur_seed;               // Currently active seed for LFSR

/**
 * @brief Enable seed input mode to collect new seed digits via UART.
 */
void start_seed_mode(void);

/**
 * @brief Handles a single character input for seed entry.
 *        Updates buffer, validates hex digits, and sets new seed when complete.
 * @param c Input character from UART
 */
void handle_seed_input(char c);

#endif
