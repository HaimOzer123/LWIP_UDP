/**
 * @file I2C_test.h
 * @brief Header file for I2C testing and scanning functions.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef INC_I2C_TEST_H_
#define INC_I2C_TEST_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief UART handler for debugging purposes. */
extern UART_HandleTypeDef huart3;

/** @brief I2C handler for I2C4 peripheral. */
extern I2C_HandleTypeDef hi2c4;

/** @brief I2C handler for I2C2 peripheral. */
extern I2C_HandleTypeDef hi2c2;

/** @brief Debug UART interface. */
#define UART_DEBUG &huart3

/** @brief I2C4 interface. */
#define I2C_4 &hi2c4

/** @brief I2C2 interface. */
#define I2C_2 &hi2c2

/**
 * @brief Test the I2C communication with a specific bit pattern.
 *
 * This function sends a specified bit pattern to test the
 * functionality of the I2C communication.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to send.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of times to send the pattern.
 * @return Status of the I2C test (0 for success, non-zero for failure).
 */
uint8_t test_i2c(char *bit_pattern, uint8_t pattern_length, uint16_t iterations);

/**
 * @brief Scan for devices on the specified I2C bus.
 *
 * This function scans the I2C bus for connected devices
 * and prints their addresses using the debug UART.
 *
 * @param[in] hi2c Pointer to the I2C handler.
 * @return Status of the scan (0 for success, non-zero for failure).
 */
uint8_t I2C_Scan(I2C_HandleTypeDef *hi2c);

#endif /* INC_I2C_TEST_H_ */
