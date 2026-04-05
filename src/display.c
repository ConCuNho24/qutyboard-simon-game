#include "display.h"

// Segment patterns for numbers 0-F
uint8_t number_segs [] = {
    SEGS_ZERO, SEGS_ONE, SEGS_TWO, SEGS_THREE, SEGS_FOUR, SEGS_FIVE, SEGS_SIX, SEGS_SEVEN, 
    SEGS_EIGHT, SEGS_NINE, SEGS_A, SEGS_B, SEGS_C, SEGS_D, SEGS_E, SEGS_F 
};

volatile uint8_t digit_l = DISP_OFF;   // Left digit, initially off
volatile uint8_t digit_r = DISP_OFF;   // Right digit, initially off

// Initialize display and SPI
void display_init(void) {
    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;  // Set SPI pins on PC0-3

    // Configure SPI SCK and MOSI as outputs
    PORTC.DIRSET = (PIN0_bm | PIN2_bm);

    // Configure DISP_LATCH pin
    PORTA.OUTSET = PIN1_bm;        // Initial high
    PORTA.DIRSET = PIN1_bm;        // Set as output

    SPI0.CTRLA = SPI_MASTER_bm;    // Enable master mode
    SPI0.CTRLB = SPI_SSD_bm;       // Set mode 0, unbuffered
    SPI0.INTCTRL = SPI_IE_bm;      // Enable SPI interrupt
    SPI0.CTRLA |= SPI_ENABLE_bm;   // Enable SPI
}

// Write a byte to display via SPI
void display_write(uint8_t data) {
    SPI0.DATA = data;              // Tx/Rx register
}

// SPI interrupt service routine
ISR(SPI0_INT_vect){
    PORTA.OUTCLR = PIN1_bm;        // Toggle latch
    PORTA.OUTSET = PIN1_bm;  
    SPI0.INTFLAGS = SPI_IF_bm;     // Clear interrupt flag
}

// Set segments for bar display based on step
void display_segs(uint8_t step)
{
    switch(step)
    {
        case 0:
            digit_l = DISP_BAR_LEFT;   
            digit_r = DISP_OFF;
            break;
        case 1:
            digit_l = DISP_BAR_RIGHT;
            digit_r = DISP_OFF;
            break;
        case 2:
            digit_l = DISP_OFF;
            digit_r = DISP_BAR_LEFT;
            break;
        case 3:
            digit_l = DISP_OFF;
            digit_r = DISP_BAR_RIGHT;  
            break;
        default:
            digit_l = DISP_OFF;
            digit_r = DISP_OFF;
            break;
    }
}

// Turn off both digits
void display_off(void) {
    digit_l = DISP_OFF;
    digit_r = DISP_OFF;
}

// Alternate writing left and right digits
void swap_display_digit(void) {
    static uint8_t toggle = 0;

    if(toggle) {
        display_write(digit_l | DISP_LHS);  
    } else {
        display_write(digit_r);          
    }

    toggle = !toggle;
}

// Show failure symbol
void display_fail(){
    digit_l = DISP_DASH;
    digit_r = DISP_DASH;
}

// Display score (0-99) without using division
void display_score(uint8_t score) {
    if(score < 100){
        uint8_t left_num = 0;
        uint8_t right_num = score;

        // Calculate tens by repeated subtraction
        while(right_num >= 10){
            right_num -= 10;
            left_num++;
        }

        // If score < 10, turn off left digit
        if(score < 10){
            digit_l = DISP_OFF;
            digit_r = number_segs[right_num];
        } else {
            digit_l = number_segs[left_num];
            digit_r = number_segs[right_num];
        }
    }
}

// Show success symbol
void display_success(){
    digit_l = DISP_ON;
    digit_r = DISP_ON;
}
