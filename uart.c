#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated RX buffer for testing
static uint8_t simulated_rx_buffer[MAX_MESSAGE_LENGTH];
uint8_t simulated_rx_index = 0;
uint8_t simulated_rx_size = 0;

void uart_init(void) {
    printf("UART initialized.\n");
}

void uart_send_byte(uint8_t byte) {
    printf("UART send byte: 0x%X\n", byte);
}

uint8_t uart_read_byte(void) {
    if (simulated_rx_index < simulated_rx_size) {
        return simulated_rx_buffer[simulated_rx_index++];
    }
    return 0; // No more data
}

// Simulates injecting a message into the RX buffer
void uart_simulate_message(const uint8_t *message, uint8_t length) {
    memcpy(simulated_rx_buffer, message, length);
    simulated_rx_size = length;
    simulated_rx_index = 0;
}
