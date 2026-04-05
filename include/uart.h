#ifndef UART_H
#define UART_H
#define UART_BUF_SIZE 64
#include "general_include.h"

/**
 * @brief Initializes UART0 for 9600 baud communication, enables TX/RX and RX interrupt.
 */
void uart_init(void);

/**
 * @brief Blocking read from UART. Waits until a byte is received and returns it.
 * @return Received byte from UART
 */
uint8_t uart_getc(void);

/**
 * @brief Blocking UART transmit. Waits until ready, then sends one byte.
 * @param c Byte to transmit
 */
void uart_putc(uint8_t c);

/**
 * @brief Non-blocking read using circular buffer. Returns 0 if no data available.
 * @return Received byte or 0 if buffer empty
 */
uint8_t uart_getc_nonblocking(void);

/**
 * @brief Sends a null-terminated string over UART.
 * @param string Pointer to string to transmit
 */
void uart_puts(char* string);

/**
 * @brief Checks if unread UART data exists in the circular buffer.
 * @return Non-zero if data available, 0 if buffer empty
 */
uint8_t uart_available(void);

/**
 * @brief Transmits an 8-bit unsigned integer as ASCII digits over UART.
 * @param n Number to send (0-255)
 */
void uart_put_uint8(uint8_t n);

#endif
