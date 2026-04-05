#include "highscore.h"

// Highscore array and count
highscore_t highs[HS_MAX];
uint8_t high_count = 0;

// Input buffer for name
char name_buffer[NAME_MAX+1] = {0};
uint8_t name_len = 0;

// Handle single character input for name
void handle_name_input(char c){
    if (c == '\r' || c == '\n') { // Enter key ends input
        state = FINISH_NAME_INPUT;
        return;
    }
    else if (name_len < NAME_MAX) { // Add char if space available
        name_buffer[name_len++] = c;
        elapsed_time = 0; // Reset timer
    }
}

// Check if score qualifies for top 5
bool is_top5(uint16_t score) {
    if (high_count < HS_MAX) return true;           // Less than max entries
    if (score > highs[high_count-1].score) return true; // Higher than lowest
    return false;
}

// Insert new highscore in sorted order
void insert_highscore(const char *name, uint16_t score) {
    uint8_t pos = high_count;
    for (uint8_t i = 0; i < high_count; i++) {
        if (score > highs[i].score) { // Find correct position
            pos = i;
            break;
        }
    }
    if (high_count < HS_MAX) high_count++; // Increase count if not full
    for (uint8_t i = high_count - 1; i > pos; i--) { // Shift lower scores
        highs[i] = highs[i - 1];
    }
    strncpy(highs[pos].name, name, NAME_MAX); // Copy name
    highs[pos].name[NAME_MAX] = '\0';         // Ensure null-termination
    highs[pos].score = score;                 // Set score
}

// Send highscores via UART
void transmit_highscores(void) {
    uart_puts("\n");
    for (uint8_t i = 0; i < high_count; i++) {
        uart_puts(highs[i].name);
        uart_putc(' ');
        uart_put_uint8(highs[i].score);
        uart_puts("\n");
    }
}
