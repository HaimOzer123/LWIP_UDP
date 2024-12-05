/**
 * @file Timer_test.h
 * @brief Header file for Timer testing functions.
 *
 * This file provides the declarations for testing timer synchronization
 * between TIM3 and TIM2 on the STM32F756ZG microcontroller.
 *
 * @note TIM3 and TIM2 must be connected to appropriate hardware timers in the STM32.
 * Ensure interrupt callbacks are enabled in the HAL configuration.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef TIMER_TEST_H
#define TIMER_TEST_H

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/** @brief UART handle for debugging. */
extern UART_HandleTypeDef huart3;

/** @brief TIM3 handle. */
extern TIM_HandleTypeDef htim3;

/** @brief TIM2 handle. */
extern TIM_HandleTypeDef htim2;

/** @brief Debug UART interface. */
#define UART_DEBUG &huart3

/** @brief TIM3 timer interface. */
#define TIM3A &htim3

/** @brief TIM2 timer interface. */
#define TIM2A &htim2

/**
 * @brief Test the synchronization of TIM3 and TIM2.
 *
 * This function tests the synchronization of two timers (TIM3 and TIM2)
 * over a specified number of iterations. Each iteration involves
 * generating a random duration and verifying that both timers
 * operate accurately for the duration.
 *
 * @param[in] iterations Number of iterations to run the test.
 * @return uint8_t Returns 1 on success, 0xFF on failure.
 */
uint8_t test_timer(uint16_t iterations);

#endif // TIMER_TEST_H
