#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

#define MIN_PLAYBACK_DELAY 250   /**< Minimum playback delay in ms */
#define MAX_PLAYBACK_DELAY 2000  /**< Maximum playback delay in ms */

/**
 * @brief Initializes the ADC module.
 *        Configures ADC to read analog input for adjusting playback speed.
 *        Sets reference voltage, input channel, and prescaler.
 */
void adc_init(void);

#endif
