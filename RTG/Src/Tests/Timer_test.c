/**
 * @file Timer_test.c
 * @brief Implementation of Timer testing functions.
 *
 * This file contains the implementation of functions to test the synchronization
 * of TIM3 and TIM2 timers on the STM32F756ZG microcontroller.
 *
 * @details This test validates that two timers (TIM3 and TIM2) can accurately
 * operate for a random duration and remain synchronized. The test ensures
 * that both timers generate periodic interrupts and measure time correctly.
 *
 * @note Ensure both TIM3 and TIM2 are configured for periodic interrupts,
 * and the interrupt service routine is enabled. Random durations between
 * 1 and 10 seconds are tested.
 *
 * @hardware TIM3 and TIM2 should be configured as follows:
 * - TIM3: Timer for random duration measurement.
 * - TIM2: Timer for random duration measurement.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "RTG.h"
#include "Protocol.h"
#include "Timer_test.h"

/** @brief Counter for TIM3 elapsed seconds. */
volatile uint32_t tim3_seconds = 0;

/** @brief Counter for TIM2 elapsed seconds. */
volatile uint32_t tim2_seconds = 0;

/** @brief Flag indicating TIM3 completion. */
volatile uint8_t tim3_done = 0;

/** @brief Flag indicating TIM2 completion. */
volatile uint8_t tim2_done = 0;

/** @brief Random duration for the test (1 to 10 seconds). */
volatile uint32_t random_duration = 0;

/**
 * @brief Test the synchronization of TIM3 and TIM2.
 *
 * This function generates random durations and tests whether both
 * timers (TIM3 and TIM2) can accurately measure the same duration.
 *
 * @param[in] iterations Number of iterations to run the test.
 * @return uint8_t Returns 1 on success, 0xFF on failure.
 */
uint8_t test_timer(uint16_t iterations) {
    printf("Starting Timer Test with %u iterations...\r\n", iterations);

    srand(time(NULL));
    for (uint16_t i = 0; i < iterations; i++) {
        printf("\nIteration %d:\r\n", i + 1);

        // Generate a random time duration between 1 and 10 seconds
        random_duration = (rand() % 10) + 1;
        printf("Random duration: %lu seconds\r\n", random_duration);

        HAL_TIM_Base_Start_IT(TIM3A);  // Start TIM3 with interrupt
        HAL_TIM_Base_Start_IT(TIM2A);  // Start TIM2 with interrupt

        // Reset flags and counters
        tim3_seconds = 0;
        tim2_seconds = 0;
        tim3_done = 0;
        tim2_done = 0;

        // Wait for both timers to complete the random duration
        while (!tim3_done || !tim2_done) {
            // Busy-wait loop to synchronize timers
        }

        // Compare the timers
        if (tim3_seconds == random_duration && tim2_seconds == random_duration) {
            printf("Timers are synchronized: TIM3 = %lu, TIM2 = %lu\r\n", tim3_seconds, tim2_seconds);
            printf("Iteration %d passed\r\n", i + 1);
        } else {
            printf("Timers mismatch: TIM3 = %lu, TIM2 = %lu\r\n", tim3_seconds, tim2_seconds);
            return 0xFF;  // Failure
        }
    }

    printf("***********************\r\n");
    printf("\nTimer Test complete.\r\n");
    return 1;
}

/**
 * @brief Callback for Timer interrupt.
 *
 * This function handles periodic timer interrupts for TIM3 and TIM2.
 * It increments the second counters and stops the timers when the
 * random duration is reached.
 *
 * @param[in] htim Pointer to the timer handle that triggered the interrupt.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        tim3_seconds++;
        if (tim3_seconds >= random_duration) {
            tim3_done = 1;
            HAL_TIM_Base_Stop_IT(TIM3A);  // Stop TIM3
        }
    } else if (htim->Instance == TIM2) {
        tim2_seconds++;
        if (tim2_seconds >= random_duration) {
            tim2_done = 1;
            HAL_TIM_Base_Stop_IT(TIM2A);  // Stop TIM2
        }
    }
}
