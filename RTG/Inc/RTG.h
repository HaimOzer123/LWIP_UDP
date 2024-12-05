/**
 * @file RTG.h
 * @brief Header file for the Real-Time Gateway (RTG) system.
 *
 * This file defines constants, variables, and function prototypes for
 * the Real-Time Gateway system. It includes UDP server communication,
 * debugging via UART, and lwIP network configuration.
 *
 * @details The RTG system is designed for hardware testing and communication
 * over a UDP server. It handles incoming commands, executes tests on various
 * peripherals, and sends results back to the client.
 *
 * @note Ensure that the lwIP stack and network interfaces are properly
 * initialized before calling any RTG-related functions.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#ifndef INC_RTG_H_
#define INC_RTG_H_

#include "main.h"
#include "inet.h"
#include "lwip.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Protocol.h"

// General configuration for the RTG system

/** @brief Debug UART handle. */
extern UART_HandleTypeDef huart3;
#define UART_DEBUG &huart3 /**< Macro for accessing the debug UART. */

/** @brief UDP server port number. */
#define SERVER_PORT 50007

/** @brief lwIP network interface for the RTG system. */
extern struct netif gnetif;

/** @brief Constants for special characters. */
#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

/** @brief Maximum length of the incoming packet buffer. */
#define MAX_BUF_LEN 100

// Global variables for UDP communication

/** @brief Callback flag indicating if a command has been received. */
extern uint8_t callback_flag;

/** @brief Buffer for storing incoming UDP packets. */
extern uint8_t incoming_buffer[MAX_BUF_LEN];

/** @brief UDP protocol control block for managing communication. */
extern struct udp_pcb* upcb;

/** @brief Destination IP address for UDP packets. */
extern ip_addr_t dest_ipaddr;

/** @brief Destination port number for UDP packets. */
extern uint16_t dest_port;

/** @brief Length of the incoming UDP packet buffer. */
extern uint16_t incoming_len;

// Function declarations

/**
 * @brief Main function for the RTG program.
 *
 * This function initializes the UDP server, processes incoming commands,
 * and handles real-time gateway operations.
 */
void rtg_main(void);

/**
 * @brief Initialize the UDP server.
 *
 * This function sets up the UDP server by creating a control block,
 * binding it to a port, and setting a receive callback.
 */
void udpServer_init(void);

/**
 * @brief Disconnect the UDP server.
 *
 * This function removes the UDP server and frees associated resources.
 *
 * @param[in] pcb Pointer to the UDP control block to disconnect.
 */
void udp_disconnect(struct udp_pcb* pcb);

/**
 * @brief Send a UDP packet.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] p Pointer to the pbuf containing the data to send.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t udp_send(struct udp_pcb* pcb, struct pbuf* p);

/**
 * @brief Connect to a remote host via UDP.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] ipaddr Pointer to the remote host's IP address.
 * @param[in] port Port number of the remote host.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t udp_connect(struct udp_pcb* pcb, const ip_addr_t* ipaddr, u16_t port);

/**
 * @brief Allocate a new UDP control block.
 *
 * @return struct udp_pcb* Pointer to the newly allocated UDP control block.
 */
struct udp_pcb* udp_new(void);

/**
 * @brief Bind the UDP server to an IP address and port number.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] ipaddr Pointer to the IP address to bind to.
 * @param[in] port Port number to bind to.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t udp_bind(struct udp_pcb* pcb, const ip_addr_t* ipaddr, u16_t port);

/**
 * @brief Receive a UDP packet.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] arg Pointer to user-defined arguments (unused).
 * @param[in] p Pointer to the received pbuf.
 */
void udp_recv(struct udp_pcb* pcb, void* arg, void* p);

/**
 * @brief Remove the UDP server.
 *
 * @param[in] pcb Pointer to the UDP control block to remove.
 */
void udp_remove(struct udp_pcb* pcb);

/**
 * @brief Send a UDP packet to a specific IP address and port.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] p Pointer to the pbuf containing the data to send.
 * @param[in] ipaddr Pointer to the destination IP address.
 * @param[in] port Destination port number.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t udp_sendto(struct udp_pcb* pcb, struct pbuf* p, const ip_addr_t* ipaddr, u16_t port);

/**
 * @brief Send a packet with specified payload and destination.
 *
 * @param[in] pcb Pointer to the UDP control block.
 * @param[in] payload Pointer to the payload data.
 * @param[in] payload_len Length of the payload data.
 * @param[in] ipaddr Pointer to the destination IP address.
 * @param[in] port Destination port number.
 * @return err_t Returns ERR_OK on success, or an error code on failure.
 */
err_t send_packet(struct udp_pcb* pcb, const void* payload, u16_t payload_len, const ip_addr_t* ipaddr, u16_t port);

#endif /* INC_RTG_H_ */
