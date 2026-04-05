#include "adc.h"

// Initialize ADC0 in free-running mode to read potentiometer on AIN2
void adc_init(void) {
    ADC0.CTRLA = ADC_ENABLE_bm;            // Enable ADC module
    ADC0.CTRLB = ADC_PRESC_DIV2_gc;        // Set clock prescaler to divide by 2

    // Set ADC timebase for 1us per conversion @ 3.3 MHz, VDD as reference
    ADC0.CTRLC = (4 << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc;

    ADC0.CTRLE = 64;                       // Sample length of 64 ADC clocks
    ADC0.CTRLF = ADC_FREERUN_bm;           // Enable free-running mode
    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;      // Select input channel AIN2 (potentiometer)

    // Start single-ended 8-bit conversion immediately
    ADC0.COMMAND = ADC_MODE_SINGLE_8BIT_gc | ADC_START_IMMEDIATE_gc;
} // adc_init
