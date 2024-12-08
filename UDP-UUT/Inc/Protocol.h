/**
 * @file Protocol.h
 * @brief Header file defining the communication protocol for testing peripherals.
 *
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

/** @brief Bitfield for testing the Timer peripheral. */
#define TEST_PERIPHERAL_TIMER 1

/** @brief Bitfield for testing the UART peripheral. */
#define TEST_PERIPHERAL_UART  2

/** @brief Bitfield for testing the SPI peripheral. */
#define TEST_PERIPHERAL_SPI   4

/** @brief Bitfield for testing the I2C peripheral. */
#define TEST_PERIPHERAL_I2C   8

/** @brief Bitfield for testing the ADC peripheral. */
#define TEST_PERIPHERAL_ADC   16

/** @brief Return code indicating success. */
#define TEST_SUCCESS 1

/** @brief Return code indicating failure. */
#define TEST_FAILURE 0xFF

/** @brief Enumeration for buffer sizes used in UART communication. */
typedef enum {
    UART_BUFFER_SIZE_SMALL = 64,
    UART_BUFFER_SIZE_MEDIUM = 128,
    UART_BUFFER_SIZE_LARGE = 256
} UartBufferSize;

/**
 * @brief Structure defining a test command.
 *
 * This structure is used to send commands to test a specific peripheral.
 */
typedef struct {
    uint32_t test_id;         /**< Unique test ID to identify the command. */
    uint8_t peripheral;       /**< Peripheral to test (use one of the TEST_PERIPHERAL_* bitfields). */
    uint8_t iterations;       /**< Number of iterations to run the test. */
    uint8_t pattern_length;   /**< Length of the bit pattern (for data transmission tests). */
    char bit_pattern[100];    /**< Bit pattern to be transmitted during the test. */
} TestCommand;

/**
 * @brief Structure defining a test result.
 *
 * This structure is used to send the result of a test back to the requester.
 */
typedef struct {
    uint32_t test_id;         /**< Test ID corresponding to the original command. */
    uint8_t result;           /**< Test result: 1 for success, 0xFF for failure. */
} TestResult;

#endif // PROTOCOL_H
