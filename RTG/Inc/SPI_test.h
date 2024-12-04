/*
 * SPI_test.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */

/*
 * SPI_test.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */

#ifndef INC_SPI_TEST_H_
#define INC_SPI_TEST_H_

#include "main.h"
#include "RTG.h"
#include "Protocol.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

// SPI Handles
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

// Macros
#define SPI_SUCCESS 1     // Return value for success
#define SPI_FAILURE 0xFF  // Return value for failure

// SPI Ports
#define SPI_1 &hspi1  // SPI1: Master
#define SPI_2 &hspi2  // SPI2: Slave

// Function Prototypes

/**
 * @brief Runs an SPI test between SPI1 (Master) and SPI2 (Slave).
 *
 * @param bit_pattern Pointer to the bit pattern to transmit.
 * @param pattern_length Length of the bit pattern.
 * @param iterations Number of iterations for the test.
 * @return uint8_t Returns SPI_SUCCESS (1) on success, SPI_FAILURE (0xFF) on failure.
 */
uint8_t test_spi(const char *bit_pattern, size_t pattern_length, int iterations);

/**
 * @brief Callback for SPI reception complete.
 *
 * This function handles SPI receive completion interrupt for SPI2.
 * It reinitializes the receive process.
 *
 * @param hspi Pointer to the SPI handle that triggered the interrupt.
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);

#endif /* INC_SPI_TEST_H_ */

