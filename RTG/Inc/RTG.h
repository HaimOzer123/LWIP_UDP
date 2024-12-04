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
#include "Protocol.h" // Include Protocol definitions for TestCommand and TestResult

// General configuration for the RTG system

// Define the UART debug port
extern UART_HandleTypeDef huart3; // Debug UART handle
#define UART_DEBUG &huart3

// Define the port number for the server
#define SERVER_PORT 50007

// Define the lwIP network interface
extern struct netif gnetif; // Generic data structure used for all lwIP network interfaces

// Define constants for special characters
#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

// Define the maximum length of the incoming packet buffer
#define MAX_BUF_LEN 100

// Define global variables for UDP communication
extern uint8_t callback_flag;       // Rename from callback_flag
extern uint8_t incoming_buffer[MAX_BUF_LEN]; // Incoming packet buffer
extern struct udp_pcb* upcb;            // UDP protocol control block
extern ip_addr_t dest_ipaddr;       // Destination IP address
extern uint16_t dest_port;          // Destination port number
extern uint16_t incoming_len;       // Length of the incoming buffer

// Main function for the RTG program
void rtg_main(void);
// UDP server initialization and communication
void udpServer_init(void);
void udp_disconnect(struct udp_pcb*); // Disconnect the UDP server
err_t udp_send(struct udp_pcb*, struct pbuf*); // Send a UDP packet
err_t udp_connect(struct udp_pcb*, const ip_addr_t*, u16_t); // Connect to a remote host
struct udp_pcb* udp_new(void); // Allocate a new udp_pcb structure
err_t udp_bind(struct udp_pcb*, const ip_addr_t*, u16_t); // Bind the UDP server to an IP address and port number
void udp_recv(struct udp_pcb*, void*, void*); // Receive a UDP packet
void udp_remove(struct udp_pcb*); // Remove the UDP server
err_t udp_sendto(struct udp_pcb*, struct pbuf*, const ip_addr_t*, u16_t); // Send a UDP packet to a specific IP address and port number
err_t send_packet(struct udp_pcb*, const void*, u16_t, const ip_addr_t*, u16_t); // Send a packet

#endif /* INC_RTG_H_ */
