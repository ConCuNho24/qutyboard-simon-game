#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "uart.h"
#include "general_include.h"
#include "global_var.h"
#include "timer.h"

#define HS_MAX 5        ///< Maximum number of highscore entries (Top 5)
#define NAME_MAX 20     ///< Maximum length of player name

/**
 * @brief Structure representing a highscore entry
 */
typedef struct {
    char name[NAME_MAX+1];  ///< Player name (null-terminated)
    uint16_t score;         ///< Player score
} highscore_t;

// ===== Highscore storage =====
extern highscore_t highs[HS_MAX];       ///< Array storing top highscores
extern uint8_t high_count;              ///< Current number of stored highscores

// ===== Name input buffer =====
extern char name_buffer[NAME_MAX+1];    ///< Buffer to store player-entered name
extern uint8_t name_len;                ///< Current length of name in buffer

// ===== Highscore management functions =====
/**
 * @brief Handles name input from user (UART or buttons)
 * @param c Character input
 */
void handle_name_input(char c);

/**
 * @brief Inserts a new highscore into the sorted highscores array
 * @param name Player name
 * @param score Player score
 */
void insert_highscore(const char *name, uint16_t score);

/**
 * @brief Transmits all stored highscores via UART
 */
void transmit_highscores(void);

/**
 * @brief Checks whether a given score qualifies for top 5
 * @param score Score to check
 * @return true if score is higher than the lowest top 5 score or if less than 5 entries exist
 */
bool is_top5(uint16_t score);

#endif
