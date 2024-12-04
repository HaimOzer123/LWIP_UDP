/*
 * I2C_test.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */


#include "RTG.h"
#include "I2C_test.h"

unsigned char data_from_i2c4;


uint8_t test_i2c(uint8_t *bit_pattern, uint8_t pattern_length, uint16_t iterations) {
    uint8_t received_data[pattern_length];
    HAL_StatusTypeDef status;
    HAL_I2C_Slave_Receive_IT(I2C_2, &data_from_i2c4, pattern_length);
    if (HAL_I2C_IsDeviceReady(I2C_4, 44 << 1, 3, HAL_MAX_DELAY) != HAL_OK) {
        printf("Slave device at address 44 is not ready.\r\n");
        return 0xFF; // Error
    }

    for (uint16_t i = 0; i < iterations; i++) {
        printf("Iteration %d/%d\r\n", i + 1, iterations);

        // Master transmits bit pattern to slave
        status = HAL_I2C_Master_Transmit(I2C_4, 44, bit_pattern, pattern_length, HAL_MAX_DELAY);
        if (status != HAL_OK) {
            printf("Transmission failed at iteration %d. Error: %d\r\n", i + 1, status);
            return 0xFF; // Error
        }

        // Slave receives the data
        status =  HAL_I2C_Slave_Receive_IT(I2C_2, &data_from_i2c4, pattern_length);
        if (status != HAL_OK) {
            printf("Reception failed at iteration %d. Error: %d\r\n", i + 1, status);
            return 0xFF; // Error
        }

        // Verify received data matches transmitted data
        if (memcmp(bit_pattern, received_data, pattern_length) != 0) {
            printf("Data mismatch at iteration %d.\r\n", i + 1);
            return 0xFF; // Error
        }

        printf("Iteration %d successful.\r\n", i + 1);
    }
    printf("***********************\r\n");
    printf("\nI2C test completed successfully.\r\n");
    return 1; // Success
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	HAL_I2C_Slave_Receive_IT(I2C_2, &data_from_i2c4, sizeof(data_from_i2c4));
}
