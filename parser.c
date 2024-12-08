#include "parser.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

uint8_t calculate_checksum(uint8_t *data, uint8_t length) {
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}

bool parse_message(uint8_t *data, uint8_t length, ParsedMessage *message) {
    printf("\nData received: ");
    for (int i = 0; i < length; i++) {
        printf(" [%02X] ", data[i]);
    }
    printf("\n");

    // Verificar comprimento mínimo e delimitadores
    if (length < 5 || data[0] != START_BYTE || data[length - 1] != END_BYTE) {
        printf("Invalid format: incorrect length or missing delimiters\n");
        return false;
    }

    uint8_t payload_length = length - 4; // Subtrai header (START_BYTE, CMD) e FOOTER (CHECKSUM, END_BYTE)
    uint8_t calculated_checksum = calculate_checksum(data + 1, length - 3); // Calcula do CMD até o penúltimo byte (sem incluir o checksum e o END_BYTE)

    printf("Calculated checksum: %02X\n", calculated_checksum);
    printf("Received checksum: %02X\n", data[length - 2]);

    if (calculated_checksum != data[length - 2]) {
        printf("Checksum mismatch\n");
        return false;
    }

    message->command = data[2];
    message->payload_length = payload_length / 4; // Cada payload tem 4 bytes

    // Converter o payload corretamente
    for (uint8_t i = 0; i < message->payload_length; i++) {
        message->payload[i] = (data[3 + i * 4] << 24) | 
                              (data[3 + i * 4 + 1] << 16) | 
                              (data[3 + i * 4 + 2] << 8) | 
                              (data[3 + i * 4 + 3]);
    }

    return true;
}
