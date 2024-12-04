#ifndef UART_TEST_H
#define UART_TEST_H

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// UART Handles
extern UART_HandleTypeDef huart3; /**< UART3 handle for debugging. Change to match your configuration. */
extern UART_HandleTypeDef huart5; /**< UART5 handle for communication. Change to match your configuration. */
extern UART_HandleTypeDef huart2; /**< UART2 handle for communication. Change to match your configuration. */

/// Flags for UART callbacks
extern uint8_t uart2_flag_calback; /**< UART2 callback flag for RX complete or error. */
extern uint8_t uart5_flag_calback; /**< UART5 callback flag for RX complete or error. */

/// Debug and communication UART definitions
#define UART_DEBUG &huart3 /**< Debug UART handle, typically used for logging. */
#define UART_2 &huart2     /**< UART2 handle, used for communication. */
#define UART_5 &huart5     /**< UART5 handle, used for communication. */

// Define a short timeout duration in milliseconds
#define SHORT_TIMEOUT 1000 // Timeout for UART operations

// Define UART testing flags and status variables
extern volatile uint8_t UART_5_RX_Complete_Callback_Flag; // UART5 RX complete callback flag
extern volatile uint8_t UART_2_RX_Complete_Callback_Flag; // UART2 RX complete callback flag
extern volatile uint8_t Uart_5_ErrorCallback_Flag;        // UART5 error callback flag
extern volatile uint8_t Uart_2_ErrorCallback_Flag;        // UART2 error callback flag

// Function declarations
uint8_t test_uart(const char* bit_pattern, uint8_t pattern_length, uint8_t iterations);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart);

#endif // UART_TEST_H

