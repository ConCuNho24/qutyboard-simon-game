#include "initialisation.h"

// Initialize all peripherals
void initialisation(void){
    pb_init();       // Initialize push buttons
    timer_init();    // Initialize timers
    buzzer_init();   // Initialize buzzer
    adc_init();      // Initialize ADC
    display_init();  // Initialize display
    uart_init();     // Initialize UART
}
