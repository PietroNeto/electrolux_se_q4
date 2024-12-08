

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

#define START_BYTE 0xAA
#define END_BYTE 0xBB
#define MAX_MESSAGE_LENGTH 256

extern uint8_t simulated_rx_index;
extern uint8_t simulated_rx_size;

void uart_init(void);                // Initializes UART (simulation)
void uart_send_byte(uint8_t byte);   // Simulates sending a byte via UART
uint8_t uart_read_byte(void);        // Simulates reading a byte from UART
void uart_simulate_message(const uint8_t *message, uint8_t length);

#endif // UART_H