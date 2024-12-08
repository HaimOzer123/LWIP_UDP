/**
 * @file SPI_test.c
 * @brief Implementation of SPI testing functions.
 *
 * This file contains the implementation of functions to test SPI communication
 * between SPI1 (Master) and SPI2 (Slave) on the STM32F7 microcontroller.
 *
 * @details Required hardware connections for SPI testing:
 *
 * 		 SPI1			SPI2
 *   - PA5 (SCK)  <--> PB10 (SCK)
 *   - PA6 (MISO) <--> PC2  (MISO)
 *   - PB5 (MOSI) <--> PC3  (MOSI)
 *
 * Ensure these connections are properly configured before running the test.
 * Both SPI peripherals should be initialized in the CubeMX configuration.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "SPI_test.h"
#include "UdpUut.h"
#include "Protocol.h"

/** @brief Data received from SPI1 (Master). */
static uint8_t data_from_spi1 = 0;

/**
 * @brief Runs an SPI test between SPI1 (Master) and SPI2 (Slave).
 *
 * This function transmits a specified bit pattern from SPI1 to SPI2
 * and verifies the received data. The test runs for a given number of
 * iterations, and results are printed for debugging.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to transmit.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of iterations for the test.
 * @return uint8_t Returns SPI_SUCCESS (1) on success, SPI_FAILURE (TEST_FAILURE) on failure.
 */
uint8_t test_spi(const char *bit_pattern, size_t pattern_length, int iterations) {
    uint8_t data_to_spi2 = 0;  // Data sent to slave

    printf("Starting SPI Test with pattern: %s, length: %d, iterations: %d\n\r",
           bit_pattern, (int)pattern_length, iterations);

    HAL_SPI_Receive_IT(SPI_2, &data_from_spi1, 1);

    for (int i = 0; i < iterations; i++) {
        printf("\nIteration %d:\r\n", i + 1);
        data_to_spi2++;
        data_to_spi2 %= 255;

        HAL_Delay(100);  // Delay for readability

        // Transmit data from Master (SPI1) to Slave (SPI2)
        if (HAL_SPI_Transmit(SPI_1, &data_to_spi2, 1, 100) == HAL_OK) {
            printf("Master sent: 0x%02X\n\r", data_to_spi2);
        } else {
            printf("Master Transmit Error! Returning TEST_FAILURE\n\r");
            return TEST_FAILURE;  // Return failure code
        }

        // Receive data from Slave (SPI2)
        if (HAL_SPI_Receive_IT(SPI_1, &data_from_spi1, 1) == HAL_OK) {
            printf("Master received: 0x%02X\n\r", data_from_spi1);
        } else {
            printf("Master Receive Error! Returning TEST_FAILURE\n\r");
            return TEST_FAILURE;  // Return failure code
        }

        // Compare transmitted and received data
        if (data_to_spi2 != data_from_spi1) {
            printf("Mismatch! Sent: 0x%02X, Received: 0x%02X\n\r", data_to_spi2, data_from_spi1);
            return TEST_FAILURE;  // Return failure if mismatch
        } else {
            printf("Match! Sent: 0x%02X, Received: 0x%02X\n\r", data_to_spi2, data_from_spi1);
            printf("Iteration %d passed\r\n", i + 1);
        }
    }

    printf("***********************\r\n");
    printf("\nSPI test complete.\r\n");
    return TEST_SUCCESS;  // Return success code
}

/**
 * @brief Callback for SPI reception complete.
 *
 * This function handles SPI receive completion interrupt for SPI2.
 * It reinitializes the receive process to enable continuous data reception.
 *
 * @param[in] hspi Pointer to the SPI handle that triggered the interrupt.
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == SPI_2) {
        HAL_SPI_Receive_IT(SPI_2, &data_from_spi1, sizeof(data_from_spi1));
    }
}
