/**
 * @file client.h
 * @brief Header file for the UDP client implementation.
 *
 * This file defines the structures, macros, and function prototypes for
 * sending test commands to the server and receiving results.
 *
 * @details The client communicates with a UDP server to execute hardware tests
 * on various peripherals, including UART, ADC, Timer, SPI, and I2C.
 * Results are logged to a file for later analysis.
 *
 * @note Ensure the client is configured with the correct server IP and port.
 * Use the provided `sudo ifconfig` command to configure the client's IP address.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef INC_CLIENT_H_
#define INC_CLIENT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

/** @brief Server IP address for UDP communication. */
#define SERVER_IP "192.168.7.2"

/** @brief Server UDP port number. */
#define SERVER_PORT 50007

/** @brief Maximum buffer size for communication. */
#define MAX_BUFFER_SIZE 100

/** @brief Bitfield for Timer peripheral. */
#define TEST_PERIPHERAL_TIMER 1

/** @brief Bitfield for UART peripheral. */
#define TEST_PERIPHERAL_UART  2

/** @brief Bitfield for SPI peripheral. */
#define TEST_PERIPHERAL_SPI   4

/** @brief Bitfield for I2C peripheral. */
#define TEST_PERIPHERAL_I2C   8

/** @brief Bitfield for ADC peripheral. */
#define TEST_PERIPHERAL_ADC   16

/**
 * @brief Structure for sending a test command to the server.
 */
typedef struct {
    uint32_t test_id;         /**< Unique Test ID. */
    uint8_t peripheral;       /**< Peripheral to test. */
    uint8_t iterations;       /**< Number of iterations for the test. */
    uint8_t pattern_length;   /**< Length of the test bit pattern. */
    char bit_pattern[MAX_BUFFER_SIZE]; /**< Test bit pattern. */
} TestCommand;

/**
 * @brief Structure for receiving test results from the server.
 */
typedef struct {
    uint32_t test_id; /**< Unique Test ID. */
    uint8_t result;   /**< 1 for success, 0xFF for failure. */
} TestResult;

// Function prototypes

/**
 * @brief Display the test menu for the user.
 */
void display_menu();

/**
 * @brief Send a test command to the server and receive the result.
 *
 * @param[in] sock The UDP socket descriptor.
 * @param[in] server_addr Pointer to the server's address structure.
 */
void send_test_command(int sock, struct sockaddr_in* server_addr);

/**
 * @brief Save the test result to a log file.
 *
 * @param[in] result Pointer to the test result structure.
 * @param[in] duration Duration of the test in seconds.
 */
void save_test_result(TestResult* result, double duration);

#endif /* INC_CLIENT_H_ */
