/*
 * ADC_test.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */

#include "ADC_test.h"
#include "RTG.h"


// Pre-determined ADC results for comparison
static const uint32_t known_adc_values[] = {
		870, 900, 860, 880, 910,
};

static const uint32_t acceptable_offset = 150; // Acceptable error margin to account for SAR ADC variations

// Declare hadc1 as an external variable
extern ADC_HandleTypeDef hadc1;

/**
 * Perform ADC test.
 *
 * @param iterations Number of iterations to sample ADC.
 * @return 1 for success, 0 for failure.
 */
uint8_t test_adc(uint16_t iterations) {
    printf("Starting ADC Test with %u iterations...\r\n", iterations);

    uint32_t adc_value = 0;
    uint32_t success = 1;

    for (uint16_t i = 0; i < iterations; i++) {
        // Start ADC conversion
        HAL_ADC_Start(&hadc1);

        // Wait for ADC conversion to complete
        if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
            adc_value = HAL_ADC_GetValue(&hadc1);

            printf("Iteration %u: ADC Value = %lu (Expected: %lu ± %lu)\r\n",
                   i + 1, adc_value, known_adc_values[i], acceptable_offset);

            // Validate the ADC value within the acceptable range
            if (adc_value < known_adc_values[i] - acceptable_offset ||
                adc_value > known_adc_values[i] + acceptable_offset) {
                printf("Mismatch at iteration %u. Expected: %lu ± %lu, Got: %lu\r\n",
                       i + 1, known_adc_values[i], acceptable_offset, adc_value);
                success = 0; // Mark as failure
            }
        } else {
            printf("ADC conversion timeout on iteration %u.\r\n", i + 1);
            HAL_ADC_Stop(&hadc1);
            return 0xFF; // Failure
        }

        // Stop ADC conversion
        HAL_ADC_Stop(&hadc1);

        // Add delay between iterations
        HAL_Delay(100);
    }

    if (success) {
        printf("ADC Test Passed for all %u iterations.\r\n", iterations);
    } else {
        printf("ADC Test Failed.\r\n");
        return 0xFF;
    }
    printf("ADC Test complete.\r\n");
    return 1;
}
