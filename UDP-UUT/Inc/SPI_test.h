/**
 * @file SPI_test.h
 * @brief Header file for SPI testing functions.
 *
 * @note Hardware connection:
 * - Connect the appropriate MOSI, MISO, SCK, and NSS lines between SPI1 and SPI2.
 *
 * @author Haim
 * @date Dec 3, 2024
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

/** @brief SPI1 handle (Master). */
extern SPI_HandleTypeDef hspi1;

/** @brief SPI2 handle (Slave). */
extern SPI_HandleTypeDef hspi2;

// Macros

/** @brief Return value indicating successful SPI test. */
#define SPI_SUCCESS 1

/** @brief Return value indicating failed SPI test. */
#define SPI_FAILURE 0xFF

// SPI Ports

/** @brief SPI1 configured as Master. */
#define SPI_1 &hspi1

/** @brief SPI2 configured as Slave. */
#define SPI_2 &hspi2

// Function Prototypes

/**
 * @brief Runs an SPI test between SPI1 (Master) and SPI2 (Slave).
 *
 * This function transmits a specified bit pattern from SPI1 to SPI2
 * and verifies the received data. The test is repeated for the given
 * number of iterations.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to transmit.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of iterations for the test.
 * @return uint8_t Returns SPI_SUCCESS (1) on success, SPI_FAILURE (0xFF) on failure.
 */
uint8_t test_spi(const char *bit_pattern, size_t pattern_length, int iterations);

/**
 * @brief Callback for SPI reception complete.
 *
 * This function is triggered upon completion of SPI data reception
 * on SPI2. It reinitializes the receive process to enable continuous
 * reception in the slave mode.
 *
 * @param[in] hspi Pointer to the SPI handle that triggered the interrupt.
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);

#endif /* INC_SPI_TEST_H_ */
