/*
 * Protocol.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// Define peripheral bitfield
#define TEST_PERIPHERAL_TIMER 1
#define TEST_PERIPHERAL_UART  2
#define TEST_PERIPHERAL_SPI   4
#define TEST_PERIPHERAL_I2C   8
#define TEST_PERIPHERAL_ADC   16

// Command structure
typedef struct {
    uint32_t test_id;         // Unique test ID
    uint8_t peripheral;       // Peripheral to test
    uint8_t iterations;       // Number of test iterations
    uint8_t pattern_length;   // Length of the bit pattern
    char bit_pattern[100];    // Bit pattern to test
} TestCommand;

// Response structure
typedef struct {
    uint32_t test_id;         // Test ID
    uint8_t result;           // 1 = Success, 0xFF = Failure
} TestResult;

#endif // PROTOCOL_H
