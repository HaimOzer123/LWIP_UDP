/**
 * @file RTG.c
 * @brief Implementation of the Real-Time Gateway (RTG) system.
 *
 * This file contains the implementation of the UDP server, handling incoming packets,
 * and executing real-time communication and testing commands.
 *
 * * @details
 * - IP Configuration:
 *   - IP:       192.168.7.2
 *   - NETMASK:  255.255.255.0 (or 192.168.7.0/24)
 *   - GATEWAY:  192.168.7.1 (not in use but required by IDE)
 * - Server Port: 50007
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "Protocol.h"
#include "RTG.h"
#include "UART_test.h"
#include "ADC_test.h"
#include "Timer_test.h"

/**
 * @brief Flag indicating a callback event from the UDP server.
 *
 * When set to 1, a testing command has been received.
 */
uint8_t callback_flag = 0;

/**
 * @brief IP address structure for the destination.
 *
 * Holds the IP address of the remote client for UDP communication.
 */
ip_addr_t dest_ipaddr = {0};

/**
 * @brief Destination port for UDP communication.
 *
 * This specifies the port number of the remote client.
 */
u16_t dest_port = 0;

/**
 * @brief UDP protocol control block.
 *
 * Represents the UDP connection state.
 */
struct udp_pcb *upcb;

/**
 * @brief Buffer for incoming UDP packets.
 *
 * Stores the data received from the remote client.
 */
uint8_t incomming_buffer[MAX_BUF_LEN] = {0};

/**
 * @brief Length of the incoming UDP packet.
 *
 * Indicates the size of the data received in bytes.
 */
u16_t incomming_len = 0;

/**
 * @brief Main function for the Real-Time Gateway (RTG) system.
 *
 * This function initializes the UDP server, processes incoming packets,
 * and handles real-time communication and testing commands. It operates
 * in a continuous loop, managing network traffic and executing tests as
 * commands are received.
 *
 * @details
 * - IP Configuration:
 *   - IP:       192.168.7.2
 *   - NETMASK:  255.255.255.0 (or 192.168.7.0/24)
 *   - GATEWAY:  192.168.7.1 (not in use but required by IDE)
 * - Server Port: 50007
 */
void rtg_main() {
    /**
     * @brief Prints a message indicating that the UDP server is running.
     */
    printf("UDP Server is running...\r\n");

    /**
     * @brief Initializes the UDP server and sets up the protocol control block.
     */
    udpServer_init();

    /**
     * @brief Continuous loop for processing network traffic and handling tests.
     *
     * The loop listens for incoming UDP packets, processes them, and handles
     * timeout events for the system.
     */
    while (1) {
        /**
         * @brief Processes incoming packets and passes them to the network interface.
         */
        ethernetif_input(&gnetif);

        /**
         * @brief Checks for system timeouts and processes timeout events.
         */
        sys_check_timeouts();

        /**
         * @brief Checks if a callback event has occurred.
         *
         * If the `callback_flag` is set, a testing command has been received,
         * and the system processes the command.
         */
        if (callback_flag == 1) {
            printf("Received command for testing\r\n");

            /**
             * @brief Resets the callback flag after processing the command.
             */
            callback_flag = 0;
        }
    }
}
