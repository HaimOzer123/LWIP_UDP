/**
 * @file UART_test.c
 * @brief Implementation of UART testing functions.
 *
 * This file contains the implementation of functions for testing UART communication,
 * including transmission and reception between UART5 and UART2.
 *
 * @details Required connections for UART testing:
 * - TX5 (PC_12) <--> RX2 (PD_6)
 * - RX5 (PD_2)  <--> TX2 (PD_5)
 *
 * The test verifies data integrity over multiple iterations by transmitting
 * a bit pattern and checking the received data for mismatches or errors.
 * It also includes error handling for transmission and reception failures.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "UART_test.h"
#include "UdpUut.h"
#include "Protocol.h"

// UART Test Function variables

/** @brief Flag for UART5 RX complete callback. */
volatile uint8_t UART_5_RX_Complete_Callback_Flag = 0;

/** @brief Flag for UART2 RX complete callback. */
volatile uint8_t UART_2_RX_Complete_Callback_Flag = 0;

/** @brief Flag for UART5 error callback. */
volatile uint8_t Uart_5_ErrorCallback_Flag = 0;

/** @brief Flag for UART2 error callback. */
volatile uint8_t Uart_2_ErrorCallback_Flag = 0;

/** @brief HAL status variables for UART operations. */
volatile HAL_StatusTypeDef status2tx, status2rx, status5tx, status5rx;

/**
 * @brief Test UART communication between UART5 and UART2.
 *
 * This function transmits a specified bit pattern between UART5 and UART2
 * over multiple iterations. It verifies data integrity and handles errors
 * during transmission and reception.
 *
 * @param[in] bit_pattern Pointer to the bit pattern to transmit.
 * @param[in] pattern_length Length of the bit pattern.
 * @param[in] iterations Number of iterations for the test.
 * @return uint8_t Returns 1 on success, TEST_FAILURE on failure.
 */
uint8_t test_uart(const char* bit_pattern, uint8_t pattern_length, uint8_t iterations) {
    uint8_t recv_msg5_rx[UART_BUFFER_SIZE_MEDIUM] = {0};
    uint8_t recv_msg2_rx[UART_BUFFER_SIZE_MEDIUM] = {0};

    for (uint8_t i = 0; i < iterations; ++i) {
        printf("\nIteration %d:\r\n", i + 1);

        uint32_t iteration_start_time = HAL_GetTick(); // Track total time for the iteration

        while (HAL_GetTick() - iteration_start_time < SHORT_TIMEOUT) { // Limit to SHORT_TIMEOUT per iteration
            // UART2 Transmission
            status2tx = HAL_UART_Transmit(UART_2, (uint8_t*)bit_pattern, pattern_length + 1, SHORT_TIMEOUT);
            if (status2tx != HAL_OK) {
                printf("UART2 TX failed with status: %d\r\n", status2tx);
                return TEST_FAILURE;
            }
            HAL_Delay(SHORT_Delay);

            // UART5 Transmission
            status5tx = HAL_UART_Transmit(UART_5, (uint8_t*)bit_pattern, pattern_length + 1, SHORT_TIMEOUT);
            if (status5tx != HAL_OK) {
                printf("UART5 TX failed with status: %d\r\n", status5tx);
                return TEST_FAILURE;
            }
            HAL_Delay(SHORT_Delay);

            // UART5 Reception
            status5rx = HAL_UART_Receive_IT(UART_5, recv_msg5_rx, pattern_length + 1);
            if (status5rx != HAL_OK) {
                printf("UART5 RX failed with status: %d\r\n", status5rx);
                return TEST_FAILURE;
            }

            // UART2 Reception
            status2rx = HAL_UART_Receive_IT(UART_2, recv_msg2_rx, pattern_length + 1);
            if (status2rx != HAL_OK) {
                printf("UART2 RX failed with status: %d\r\n", status2rx);
                return TEST_FAILURE;
            }

            // Error Handling and Data Verification
            if (Uart_5_ErrorCallback_Flag == 1 || Uart_2_ErrorCallback_Flag == 1) {
                printf("Error detected in UART5 or UART2\r\n");
                Uart_5_ErrorCallback_Flag = 0;
                Uart_2_ErrorCallback_Flag = 0;
            } else {
                if (UART_5_RX_Complete_Callback_Flag == 1) {
                    printf("Received message by UART5 RX: %s\r\n", recv_msg5_rx);
                    UART_5_RX_Complete_Callback_Flag = 0;
                }
                if (UART_2_RX_Complete_Callback_Flag == 1) {
                    printf("Received message by UART2 RX: %s\r\n", recv_msg2_rx);
                    UART_2_RX_Complete_Callback_Flag = 0;
                }

                // Compare received data
                if (strncmp(bit_pattern, (char*)recv_msg5_rx, pattern_length) == 0 &&
                    strncmp(bit_pattern, (char*)recv_msg2_rx, pattern_length) == 0) {
                    printf("Iteration %d passed\r\n", i + 1);
                    break; // Exit while loop once successful
                } else {
                    printf("Data mismatch detected. Retrying...\r\n");
                }
            }
        }

        if (HAL_GetTick() - iteration_start_time >= SHORT_TIMEOUT) {
            printf("Iteration %d failed due to timeout\r\n", i + 1);
            return TEST_FAILURE;
        }
    }
    printf("***********************\r\n");
    printf("\nUART test complete\r\n");
    return TEST_SUCCESS;
}

/**
 * @brief Callback for UART RX complete event.
 *
 * This function is triggered when a UART RX operation completes.
 * It sets the corresponding callback flag for UART5 or UART2.
 *
 * @param[in] huart Pointer to the UART handle that triggered the interrupt.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == UART5) {
        UART_5_RX_Complete_Callback_Flag = 1;
    } else if (huart->Instance == USART2) {
        UART_2_RX_Complete_Callback_Flag = 1;
    }
}

/**
 * @brief Callback for UART error event.
 *
 * This function is triggered when a UART error occurs.
 * It sets the corresponding error callback flag for UART5 or UART2.
 *
 * @param[in] huart Pointer to the UART handle that triggered the error.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == UART5) {
        Uart_5_ErrorCallback_Flag = 1;
    } else if (huart->Instance == USART2) {
        Uart_2_ErrorCallback_Flag = 1;
    }
}
