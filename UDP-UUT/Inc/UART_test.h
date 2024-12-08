/**
 * @file UART_test.h
 * @brief Header file for UART testing functions.
 *
 * This file contains definitions and declarations for testing UART
 * communication, including configurations for debugging and handling
 * UART callbacks for error and RX complete events.
 *
 * @note Modify the UART handles (`huart3`, `huart5`, `huart2`) to match
 * your hardware configuration as necessary.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef UART_TEST_H
#define UART_TEST_H

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// UART Handles

/**
 * @brief UART3 handle for debugging.
 * Change this to match your hardware configuration.
 */
extern UART_HandleTypeDef huart3;

/**
 * @brief UART5 handle for communication.
 * Change this to match your hardware configuration.
 */
extern UART_HandleTypeDef huart5;

/**
 * @brief UART2 handle for communication.
 * Change this to match your hardware configuration.
 */
extern UART_HandleTypeDef huart2;

/// Flags for UART callbacks

/** @brief UART2 callback flag for RX complete or error. */
extern uint8_t uart2_flag_calback;

/** @brief UART5 callback flag for RX complete or error. */
extern uint8_t uart5_flag_calback;

/// Debug and communication UART definitions

/**
 * @brief Debug UART handle, typically used for logging.
 */
#define UART_DEBUG &huart3

/**
 * @brief UART2 handle, used for communication.
 */
#define UART_2 &huart2

/**
 * @brief UART5 handle, used for communication.
 */
#define UART_5 &huart5

/// Timeout Definitions

/**
 * @brief Short timeout duration in milliseconds for UART operations.
 */
#define SHORT_TIMEOUT 1000
#define SHORT_Delay 100
/// UART Testing Flags and Status Variables

/** @brief UART5 RX complete callback flag. */
extern volatile uint8_t UART_5_RX_Complete_Callback_Flag;

/** @brief UART2 RX complete callback flag. */
extern volatile uint8_t UART_2_RX_Complete_Callback_Flag;

/** @brief UART5 error callback flag. */
extern volatile uint8_t Uart_5_ErrorCallback_Flag;

/** @brief UART2 error callback flag. */
extern volatile uint8_t Uart_2_ErrorCallback_Flag;

/// Function Declarations

/**
 * @brief Tests UART communication with a specified bit pattern.
 *
 * This function transmits and receives a bit pattern using the UART
 * interface and verifies communication over multiple iterations.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to transmit.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of iterations for the test.
 * @return uint8_t Returns 1 on success, 0xFF on failure.
 */
uint8_t test_uart(const char* bit_pattern, uint8_t pattern_length, uint8_t iterations);

/**
 * @brief Callback for UART RX complete event.
 *
 * This function is triggered when a UART RX operation completes.
 * It sets the corresponding callback flags for UART2 or UART5.
 *
 * @param[in] huart Pointer to the UART handle that triggered the interrupt.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

/**
 * @brief Callback for UART error event.
 *
 * This function is triggered when a UART error occurs.
 * It sets the corresponding error callback flags for UART2 or UART5.
 *
 * @param[in] huart Pointer to the UART handle that triggered the error.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart);

#endif // UART_TEST_H
