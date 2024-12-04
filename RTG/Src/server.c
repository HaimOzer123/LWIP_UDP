#include "RTG.h"
#include "Protocol.h"
#include "UART_test.h"
#include "ADC_test.h"
#include "Timer_test.h"
#include "SPI_test.h"
#include "I2C_test.h"

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



err_t send_packet(struct udp_pcb* pcb, const void* payload, u16_t payload_len, const ip_addr_t* ipaddr, u16_t port)
{
    err_t err;
    struct pbuf* p;

    // allocate a pbuf for the payload
    p = pbuf_alloc(PBUF_TRANSPORT, payload_len, PBUF_RAM);
    if (!p) {
        // failed to allocate pbuf
        return ERR_MEM;
    }

    // copy the payload into the pbuf
    memcpy(p->payload, payload, payload_len);

    // send the packet
    err = udp_sendto(pcb, p, ipaddr, port);

    // free the pbuf
    pbuf_free(p);

    return err;
}


void udpServer_init(void) {
	// UDP Control Block structure
   upcb = udp_new();
   callback_flag = 0;
   err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT);  // 50,007 is the server UDP port

   /* 3. Set a receive callback for the upcb */
   if (err == ERR_OK) {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb);
   }
}
