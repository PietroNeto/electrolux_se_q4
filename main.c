#include "uart.h"
#include "parser.h"
#include <stdio.h>

volatile uint8_t rx_buffer[MAX_MESSAGE_LENGTH];
volatile uint8_t rx_index = 0;
volatile bool message_ready = false;

void uart_rx_isr(void) {
    uint8_t byte = uart_read_byte();
    if (rx_index == 0 && byte == START_BYTE) {
        rx_buffer[rx_index++] = byte; // Store START_BYTE
    } else if (rx_index > 0) {
        rx_buffer[rx_index++] = byte;
        if (rx_index >= MAX_MESSAGE_LENGTH || byte == END_BYTE) {
            message_ready = true; // Message complete
        }
    }
}

void handle_message(ParsedMessage *message) {
    printf("Command: %d\n", message->command);
    for (uint8_t i = 0; i < message->payload_length; i++) {
        printf("Payload[%d]: %d\n", i, message->payload[i]);
    }
}

int main(void) {
    uart_init();

    // Simulate a message
    uint8_t test_message[] = {
        START_BYTE, 0x10, 0x01, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x32, 0xA7, END_BYTE
    }; // Command: 1, Payload: [100, 50]

    uart_simulate_message(test_message, sizeof(test_message));

    while (simulated_rx_index < simulated_rx_size) {
        uart_rx_isr();
    }

    if (message_ready) {
        ParsedMessage message;
        if (parse_message((uint8_t *)rx_buffer, rx_index, &message)) {
            handle_message(&message);
        } else {
            printf("Invalid message received.\n");
        }

        rx_index = 0; // Reset buffer
        message_ready = false;
    }

    return 0;
}
