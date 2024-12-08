/**
 * @file ADC_test.h
 * @brief Header file for ADC testing functions.
 *
 * This file provides the declarations for functions and definitions
 * used to test the ADC functionality on the STM32F7 microcontroller.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef INC_ADC_TEST_H_
#define INC_ADC_TEST_H_

#include "RTG.h"

/**
 * @brief ADC handler for ADC1 peripheral.
 */
extern ADC_HandleTypeDef hadc1;

/**
 * @brief Test the ADC by reading values over a specified number of iterations.
 *
 * This function reads ADC values for the given number of iterations and
 * verifies the ADC's functionality by outputting the values for debugging.
 *
 * @param[in] iterations Number of ADC readings to perform.
 * @return Status of the ADC test (1 for success, 0xFF for failure).
 */
uint8_t test_adc(uint16_t iterations);

#endif /* INC_ADC_TEST_H_ */
