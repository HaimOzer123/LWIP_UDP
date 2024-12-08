/**
 * @file udp_server.c
 * @brief Implementation of a UDP server for executing hardware tests.
 *
 * This file contains functions for handling UDP communication, receiving test commands,
 * executing the appropriate hardware tests, and sending results back to the client.
 *
 * @details Supported peripherals for testing:
 * - UART
 * - ADC
 * - Timer
 * - SPI
 * - I2C
 *
 * @note Ensure the hardware peripherals are properly configured before running the server.
 * The server listens on a predefined UDP port and executes tests based on incoming commands.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "UdpUut.h"
#include "Protocol.h"
#include "UART_test.h"
#include "ADC_test.h"
#include "Timer_test.h"
#include "SPI_test.h"
#include "I2C_test.h"

/**
 * @brief Execute a hardware test based on the received command.
 *
 * This function determines the peripheral to test and executes the corresponding test function.
 *
 * @param[in] command Pointer to the TestCommand structure containing test parameters.
 * @return uint8_t Returns 1 on success, 0xFF on failure.
 */
static uint8_t execute_test(TestCommand* command) {
    printf("Executing test for Peripheral: %u, Test-ID: %u\r\n",
           (unsigned int)command->peripheral,
           (unsigned int)command->test_id);

    switch (command->peripheral) {
        case TEST_PERIPHERAL_UART:
            return test_uart(command->bit_pattern, command->pattern_length, command->iterations);
        case TEST_PERIPHERAL_ADC:
            return test_adc(command->iterations);
        case TEST_PERIPHERAL_TIMER:
            return test_timer(command->iterations);
        case TEST_PERIPHERAL_SPI:
            return test_spi(command->bit_pattern, command->pattern_length, command->iterations);
        case TEST_PERIPHERAL_I2C:
            return test_i2c(command->bit_pattern, command->pattern_length, command->iterations);
        default:
            printf("Invalid peripheral for testing: %d\r\n", command->peripheral);
            return 0xFF;
    }
}

/**
 * @brief UDP receive callback for handling incoming test commands.
 *
 * This function is triggered when a UDP packet is received. It parses the command,
 * executes the specified test, and sends the result back to the client.
 *
 * @param[in] arg Pointer to user-defined arguments (unused).
 * @param[in] upcb Pointer to the UDP control block.
 * @param[in] p Pointer to the received packet buffer.
 * @param[in] addr Pointer to the sender's IP address.
 * @param[in] port Port number of the sender.
 */
void udp_receive_callback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port) {
    TestCommand command;
    TestResult result;

    // Parse incoming command
    memcpy(&command, p->payload, sizeof(TestCommand));
    pbuf_free(p);

    // Validate pattern length
    if (command.pattern_length != strlen(command.bit_pattern)) {
        printf("Pattern length mismatch. Expected: %d, Received: %d\r\n", (int)strlen(command.bit_pattern), command.pattern_length);
        result.result = 0xFF;  // Indicate error
        result.test_id = command.test_id;
        send_packet(upcb, &result, sizeof(TestResult), addr, port);
        return;
    }

    // Execute the test
    result.test_id = command.test_id;
    result.result = execute_test(&command);

    // Send the result back to the client
    send_packet(upcb, &result, sizeof(TestResult), addr, port);
}

/**
 * @brief Send a UDP packet to the client.
 *
 * This function sends a UDP packet containing the specified payload to the given IP address and port.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] payload Pointer to the data to send.
 * @param[in] payload_len Length of the payload data.
 * @param[in] ipaddr Pointer to the destination IP address.
 * @param[in] port Destination port number.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t send_packet(struct udp_pcb* pcb, const void* payload, u16_t payload_len, const ip_addr_t* ipaddr, u16_t port) {
    err_t err;
    struct pbuf* p;

    // Allocate a pbuf for the payload
    p = pbuf_alloc(PBUF_TRANSPORT, payload_len, PBUF_RAM);
    if (!p) {
        // Failed to allocate pbuf
        return ERR_MEM;
    }

    // Copy the payload into the pbuf
    memcpy(p->payload, payload, payload_len);

    // Send the packet
    err = udp_sendto(pcb, p, ipaddr, port);

    // Free the pbuf
    pbuf_free(p);

    return err;
}

/**
 * @brief Initialize the UDP server.
 *
 * This function creates a UDP control block, binds it to the server port,
 * and sets a receive callback for handling incoming test commands.
 */
void udpServer_init(void) {
    struct udp_pcb* upcb = udp_new(); /**< Pointer to the UDP control block. */
    err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT); /**< Bind the UDP server to SERVER_PORT. */

    if (err == ERR_OK) {
        // Set a receive callback
        udp_recv(upcb, udp_receive_callback, NULL);
    } else {
        // Failed to bind, remove the UDP control block
        udp_remove(upcb);
    }
}
