#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "display_macros.h"

/**
 * @brief Initializes the 7-segment display module.
 *        Configures SPI, output pins, and enables SPI interrupts.
 */
void display_init(void);

/**
 * @brief Shows a specific bar segment on the display.
 * @param step Index of the segment to light (0–3), corresponding to left/right bars.
 */
void display_segs(uint8_t step);

/**
 * @brief Turns off both digits of the display.
 */
void display_off(void);

/**
 * @brief Alternates between left and right digit for multiplexing.
 *        Should be called periodically (e.g., in timer ISR) for flicker-free display.
 */
void swap_display_digit(void);

/**
 * @brief Displays failure pattern (e.g., two dashes) on the display.
 */
void display_fail(void);

/**
 * @brief Displays a numeric score (0–99) on the 2-digit 7-segment display.
 * @param score Value to display.
 */
void display_score(uint8_t score);

/**
 * @brief Displays success pattern (e.g., both digits ON) on the display.
 */
void display_success(void);

#endif
