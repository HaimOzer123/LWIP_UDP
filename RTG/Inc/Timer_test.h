/*
 * Timer_test.h
 *
 *  Created on: Dec 3, 2024
 *      Author: Haim
 */
#ifndef TIMER_TEST_H
#define TIMER_TEST_H


#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern UART_HandleTypeDef huart3;	//Change to match your UART number
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;

#define UART_DEBUG &huart3
#define TIM3A &htim3
#define TIM2A &htim2

uint8_t test_timer(uint16_t iterations);

#endif // TIMER_TEST_H

