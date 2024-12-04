/*
 * Timer_test.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */
#include "RTG.h"
#include "Protocol.h"
#include "Timer_test.h"


volatile uint32_t tim3_seconds = 0;
volatile uint32_t tim2_seconds = 0;
volatile uint8_t tim3_done = 0;
volatile uint8_t tim2_done = 0;
volatile uint32_t random_duration = 0;


uint8_t test_timer(uint16_t iterations) {
    printf("Starting Timer Test with %u iterations...\r\n", iterations);
    srand(time(NULL));
    for (uint16_t i = 0; i < iterations; i++) {
    	printf("\nIteration %d:\r\n", i + 1);
    // Generate a random time duration between 1 and 10 seconds
    random_duration = (rand() % 10) + 1;
    printf("Random duration: %lu seconds\r\n", random_duration);

    HAL_TIM_Base_Start_IT(TIM3A); //needs to be done by the developer
    HAL_TIM_Base_Start_IT(TIM2A); //needs to be done by the developer

    // Reset flags and counters
    tim3_seconds = 0;
    tim2_seconds = 0;
    tim3_done = 0;
    tim2_done = 0;

    // Wait for both timers to complete the random duration
    while (!tim3_done || !tim2_done) {

    }
    // Compare the timers
    if (tim3_seconds == random_duration && tim2_seconds == random_duration) {
        printf("Timers are synchronized: TIM3 = %lu, TIM2 = %lu\r\n", tim3_seconds, tim2_seconds);

    } else {
        printf("Timers mismatch: TIM3 = %lu, TIM2 = %lu\r\n", tim3_seconds, tim2_seconds);
        return 0xFF; // Failure
    }
    }
    printf("Timers Test Passed for all %u iterations.\r\n", iterations);
    printf("Timer Test complete.\r\n");
    return 1;
}

// Timer interrupt callback
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        tim3_seconds++;
        if (tim3_seconds >= random_duration) {
            tim3_done = 1;
            HAL_TIM_Base_Stop_IT(TIM3A); // Stop TIM1
        }
    } else if (htim->Instance == TIM2) {
        tim2_seconds++;
        if (tim2_seconds >= random_duration) {
            tim2_done = 1;
            HAL_TIM_Base_Stop_IT(TIM2A); // Stop TIM2
        }
    }
}
