///*
// * UART_test.c
// *
// *  Created on: Dec 3, 2024
// *      Author: Haim
// *
// *******************************************************
// * UART Test Connections:
// *
// * Required connections for UART5 and UART2:
// *
// *   - TX5 (PC_12)CN8 ---> RX2 (PD_6)CN9
// *   - RX5 (PD_2)CN8  ---> TX2 (PD_5)CN9
// *******************************************************/

#include "UART_test.h"
#include "RTG.h"
#include "Protocol.h"

// UART Test Function variables
volatile uint8_t UART_5_RX_Complete_Callback_Flag = 0;
volatile uint8_t UART_2_RX_Complete_Callback_Flag = 0;
volatile uint8_t Uart_5_ErrorCallback_Flag = 0;
volatile uint8_t Uart_2_ErrorCallback_Flag = 0;

volatile HAL_StatusTypeDef status2tx, status2rx, status5tx, status5rx;

uint8_t test_uart(const char* bit_pattern, uint8_t pattern_length, uint8_t iterations) {
    uint8_t recv_msg5_rx[128] = {0};
    uint8_t recv_msg2_rx[128] = {0};

    for (uint8_t i = 0; i < iterations; ++i) {
        printf("\nIteration %d:\r\n", i + 1);

        uint32_t iteration_start_time = HAL_GetTick(); // Track total time for the iteration

        while (HAL_GetTick() - iteration_start_time < SHORT_TIMEOUT) { // Limit to SHORT_TIMEOUT per iteration
            // UART2 Transmission
            status2tx = HAL_UART_Transmit(UART_2, (uint8_t*)bit_pattern, pattern_length + 1, SHORT_TIMEOUT);
            if (status2tx != HAL_OK) {
                printf("UART2 TX failed with status: %d\r\n", status2tx);
                return 0xFF;
            }
            HAL_Delay(100);

            // UART5 Transmission
            status5tx = HAL_UART_Transmit(UART_5, (uint8_t*)bit_pattern, pattern_length + 1, SHORT_TIMEOUT);
            if (status5tx != HAL_OK) {
                printf("UART5 TX failed with status: %d\r\n", status5tx);
                return 0xFF;
            }
            HAL_Delay(100);

            // UART5 Reception
            status5rx = HAL_UART_Receive_IT(UART_5, recv_msg5_rx, pattern_length + 1);
            if (status5rx != HAL_OK) {
                printf("UART5 RX failed with status: %d\r\n", status5rx);
                return 0xFF;
            }

            // UART2 Reception
            status2rx = HAL_UART_Receive_IT(UART_2, recv_msg2_rx, pattern_length + 1);
            if (status2rx != HAL_OK) {
                printf("UART2 RX failed with status: %d\r\n", status2rx);
                return 0xFF;
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
            return 0xFF;
        }
    }

    printf("UART test complete\r\n");
    return 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == UART5) {
        UART_5_RX_Complete_Callback_Flag = 1;
    } else if (huart->Instance == USART2) {
        UART_2_RX_Complete_Callback_Flag = 1;
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == UART5) {
        Uart_5_ErrorCallback_Flag = 1;
    } else if (huart->Instance == USART2) {
        Uart_2_ErrorCallback_Flag = 1;
    }
}



