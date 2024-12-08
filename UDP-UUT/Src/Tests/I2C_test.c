/**
 * @file I2C_test.c
 * @brief Implementation of I2C testing and scanning functions.
 *
 * This file contains the implementation of functions for scanning I2C devices
 * and testing I2C communication on the STM32F7 microcontroller.
 *
 * @details Required jumper connections for testing:
 * - I2C2-SDA [PF0] <--> I2C4-SDA [PF15]
 * - I2C2-SCL [PF1] <--> I2C4-SCL [PF14]
 *
 * Ensure these connections are properly configured before running the test.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "UdpUut.h"
#include "I2C_test.h"
#include "Protocol.h"

/**
 * @brief Data received from I2C4 slave.
 */
unsigned char data_from_i2c4;

/**
 * @brief Global variable to store the detected I2C device address.
 */
uint8_t address;

/**
 * @brief Scans the I2C bus for connected devices.
 *
 * This function checks for devices on the specified I2C bus.
 * If a device is found, its address is printed and returned.
 *
 * @param[in] hi2c Pointer to the I2C handler.
 * @return Address of the first detected device, or 0 if no device is found.
 */
uint8_t I2C_Scan(I2C_HandleTypeDef *hi2c) {
    printf("Scanning I2C bus...\r\n");
    for (uint8_t addr = 1; addr < 128; addr++) {
        if (HAL_I2C_IsDeviceReady(hi2c, addr << 1, 1, 10) == HAL_OK) {
            printf("Device found at 0x%02X\r\n", addr);
            return addr; // Return the first found address
        }
    }
    printf("No device found.\r\n");
    return 0; // No device found
}

/**
 * @brief Tests I2C communication by sending a bit pattern.
 *
 * This function scans for a valid I2C device, then sends a specified bit
 * pattern to the detected device multiple times to test the I2C communication.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to send.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of iterations to send the pattern.
 * @return 1 for success, or TEST_FAILURE for failure.
 */
uint8_t test_i2c(char *bit_pattern, uint8_t pattern_length, uint16_t iterations) {
    HAL_StatusTypeDef status;

    // Scan for a valid device
    address = I2C_Scan(I2C_4);
    if (address == 0) {
        printf("No device found. Cannot proceed with the test.\r\n");
        return TEST_FAILURE; // Error
    }

    // Prepare slave to receive
    HAL_I2C_Slave_Receive_IT(I2C_2, &data_from_i2c4, sizeof(data_from_i2c4));

    // Perform test iterations
    for (uint16_t i = 0; i < iterations; i++) {
        printf("Iteration %d/%d\r\n", i + 1, iterations);

        // Master transmits bit pattern to slave
        status = HAL_I2C_Master_Transmit(I2C_4, address << 1, (uint8_t *)bit_pattern, pattern_length, HAL_MAX_DELAY);
        if (status != HAL_OK) {
            printf("Transmission failed at iteration %d. Error: %ld\r\n", i + 1, HAL_I2C_GetError(I2C_4));
            return TEST_FAILURE; // Error
        }

        printf("Iteration %d successful.\r\n", i + 1);
    }

    printf("***********************\r\n");
    printf("\nI2C test completed successfully.\r\n");
    return TEST_SUCCESS; // Success
}

/**
 * @brief Callback function for I2C Slave Receive Complete event.
 *
 * This function is triggered when the slave I2C receives data successfully.
 * It prepares the slave for the next reception.
 *
 * @param[in] hi2c Pointer to the I2C handler.
 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    // Prepare for the next reception
    HAL_I2C_Slave_Receive_IT(I2C_2, &data_from_i2c4, sizeof(data_from_i2c4));
}
