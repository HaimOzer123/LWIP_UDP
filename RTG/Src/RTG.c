/*
 *	EVB configuration:
 *	IP: 		192.168.7.2
 *	NETMASK: 	255.255.255.0 (or 192.168.7.0/24)
 *	GATEWAY: 	192.168.7.1 (not in use but required by IDE)
 *	Port:		50,007
 */
#include "Protocol.h"
#include "RTG.h"
#include "UART_test.h"
#include "ADC_test.h"
#include "Timer_test.h"

uint8_t callback_flag = 0;
ip_addr_t dest_ipaddr = {0};
u16_t dest_port = 0;
struct udp_pcb *upcb;
uint8_t incomming_buffer[MAX_BUF_LEN] = {0};
u16_t incomming_len = 0;

void rtg_main() {
    printf("UDP Server is running...\r\n");
    udpServer_init();

    while (1) {
        ethernetif_input(&gnetif);
        sys_check_timeouts();

        if (callback_flag == 1) {
            printf("Received command for testing\r\n");
            callback_flag = 0;
        }
    }
}
