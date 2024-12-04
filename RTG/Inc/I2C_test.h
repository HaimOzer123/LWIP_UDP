/*
 * I2C_test.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */

#ifndef INC_I2C_TEST_H_
#define INC_I2C_TEST_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c4;
extern I2C_HandleTypeDef hi2c2;

#define UART_DEBUG &huart3
#define I2C_4 &hi2c4
#define I2C_2 &hi2c2

uint8_t test_i2c(uint8_t *bit_pattern, uint8_t pattern_length, uint16_t iterations);

#endif /* INC_I2C_TEST_H_ */
