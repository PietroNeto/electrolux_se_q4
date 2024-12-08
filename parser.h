#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t command;
    int32_t payload[8]; // Adjust size as needed
    uint8_t payload_length;
} ParsedMessage;

bool parse_message(uint8_t *data, uint8_t length, ParsedMessage *message);
uint8_t calculate_checksum(uint8_t *data, uint8_t length);

#endif // PARSER_H
