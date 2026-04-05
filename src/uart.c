#include "uart.h"

volatile uint8_t uart_buf[UART_BUF_SIZE];  // Circular buffer to store received bytes
volatile uint8_t uart_head = 0;            // Next write position
volatile uint8_t uart_tail = 0;            // Next read position

// Initialize UART0 for 9600 baud, enable TX/RX and RX interrupt
void uart_init(void) {
    PORTB.DIRSET = PIN2_bm;                   // Set PB2 as TX
    USART0.BAUD = 1389;                       // 9600 BAUD @ 3.33MHz
    USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm; 
    USART0.CTRLA = USART_RXCIE_bm;           // Enable RX complete interrupt
}

// Blocking read: waits for a byte
uint8_t uart_getc(void) {
    while (!(USART0.STATUS & USART_RXCIF_bm));
    return USART0.RXDATAL;
}

// Non-blocking read from circular buffer
uint8_t uart_getc_nonblocking(void) {
    if (uart_head == uart_tail) return 0;      // Buffer empty
    uint8_t data = uart_buf[uart_tail];
    uart_tail = (uart_tail + 1) % UART_BUF_SIZE;
    return data;
}

// Blocking transmit: waits for buffer then sends
void uart_putc(uint8_t c) {
    while (!(USART0.STATUS & USART_DREIF_bm));
    USART0.TXDATAL = c;
}

// Check if buffer has unread data
uint8_t uart_available(void) {
    return (uart_head != uart_tail);
}

// RX complete interrupt: store incoming byte into ring buffer
ISR(USART0_RXC_vect) {
    uint8_t data = USART0.RXDATAL;
    uint8_t next = (uart_head + 1) % UART_BUF_SIZE;

    if (next != uart_tail) {                   // Avoid overflow
        uart_buf[uart_head] = data;
        uart_head = next;
    }
}

// Send string
void uart_puts(char* string) {
    char *ptr = string;
    while (*ptr != '\0') {
        uart_putc(*ptr);
        ptr++;
    }
}

// Send 8-bit number as ASCII digits without using division
void uart_put_uint8(uint8_t n) {
    uint8_t digit;

    if (n >= 100) {                            // Hundreds
        digit = 0;
        while (n >= 100) { n -= 100; digit++; }
        uart_putc('0' + digit);
        digit = 0;
        while (n >= 10) { n -= 10; digit++; }
        uart_putc('0' + digit);
        uart_putc('0' + n);                    // Ones
    } 
    else if (n >= 10) {                        // Tens
        digit = 0;
        while (n >= 10) { n -= 10; digit++; }
        uart_putc('0' + digit);
        uart_putc('0' + n);
    } 
    else {                                     // Single digit
        uart_putc('0' + n);
    }
}
