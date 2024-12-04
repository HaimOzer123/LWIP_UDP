/*
 * ADC_test.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */


#include "ADC_test.h"

/**
 * Perform ADC test.
 *
 * @param iterations Number of iterations to sample ADC.
 * @return 1 for success, 0 for failure.
 */
uint8_t test_adc(uint16_t iterations) {
    printf("Starting ADC Test with %u iterations...\n", iterations);

    uint32_t adc_value = 0;
    uint32_t sum = 0;

    for (uint16_t i = 0; i < iterations; i++) {
        // Start ADC conversion
        HAL_ADC_Start(&hadc1);

        // Wait for ADC conversion to complete
        if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);
            printf("Iteration %u: ADC Value = %lu\n", i + 1, adc_value);
            sum += adc_value;
        } else {
            printf("ADC conversion timeout on iteration %u.\n", i + 1);
            HAL_ADC_Stop(&hadc1);
            return 0; // Failure
        }

        // Stop ADC conversion
        HAL_ADC_Stop(&hadc1);

        // Add delay between iterations
        HAL_Delay(100);
    }

    printf("ADC Test Completed. Average Value = %lu\n", sum / iterations);
    return 1; // Success
}
