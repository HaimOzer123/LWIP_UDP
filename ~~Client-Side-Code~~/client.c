/**
 * @file client.c
 * @brief Implementation of the UDP client for hardware testing.
 *
 * This file implements functions for sending test commands to the server,
 * receiving results, and logging them to a file. It also provides a menu
 * interface for the user to select the desired test.
 *
 * @details The client communicates with a server over UDP to execute hardware
 * tests on various peripherals. Test results are logged with timestamps and
 * durations for analysis.
 *
 * @note Ensure the server is running and the client is properly configured
 * with the correct IP address and port.
 *
 * @author Haim
 * @date Dec 3, 2024
 */

#include "client.h"

// Display the menu for the user
/**
 * @brief Display the test menu for user input.
 *
 * This function prints a menu of available tests and prompts the user
 * to select an option.
 */
void display_menu() {
    printf("\n======= Test Menu =======\n");
    printf("1. UART Test\n");
    printf("2. ADC Test\n");
    printf("3. Timer Test\n");
    printf("4. SPI Test\n");
    printf("5. I2C Test\n");
    printf("6. Exit\n");
    printf("=========================\n");
    printf("Enter your choice: ");
}

// Send the test command to the server
/**
 * @brief Send a test command to the server and handle the response.
 *
 * This function prepares a test command based on the user's selection,
 * sends it to the server, and waits for the result. The result is then
 * logged to a file with the test duration.
 *
 * @param[in] sock The UDP socket descriptor.
 * @param[in] server_addr Pointer to the server's address structure.
 */
void send_test_command(int sock, struct sockaddr_in* server_addr) {
    TestCommand command = {0};
    TestResult result = {0};
    char choice[10];
    double duration = 0.0;

    // Get user choice
    fgets(choice, sizeof(choice), stdin);
    int option = atoi(choice);

    if (option == 6) {
        printf("Exiting the program...\n");
        exit(0);
    }

    // Prepare the test command
    command.test_id = rand() % 10000; // Random test ID for uniqueness
    command.iterations = 5;          // Default 5 iterations

    switch (option) {
        case 1: // UART Test
            command.peripheral = TEST_PERIPHERAL_UART;
            strcpy(command.bit_pattern, "HelloUART");
            command.pattern_length = strlen(command.bit_pattern);
            break;
        case 2: // ADC Test
            command.peripheral = TEST_PERIPHERAL_ADC;
            break;
        case 3: // Timer Test
            command.peripheral = TEST_PERIPHERAL_TIMER;
            break;
        case 4: // SPI Test
            command.peripheral = TEST_PERIPHERAL_SPI;
            strcpy(command.bit_pattern, "SPI_TEST");
            command.pattern_length = strlen(command.bit_pattern);
            break;
        case 5: // I2C Test
            command.peripheral = TEST_PERIPHERAL_I2C;
            strcpy(command.bit_pattern, "I2CTEST");
            command.pattern_length = strlen(command.bit_pattern);
        break;

        default:
            printf("Invalid choice! Try again.\n");
            return;
    }

    // Send the command to the server
    clock_t start_time = clock(); // Start timer
    sendto(sock, &command, sizeof(TestCommand), 0, (struct sockaddr*)server_addr, sizeof(*server_addr));

    // Receive the result from the server
    socklen_t server_len = sizeof(*server_addr);
    recvfrom(sock, &result, sizeof(TestResult), 0, (struct sockaddr*)server_addr, &server_len);

    // Calculate duration
    clock_t end_time = clock();
    duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print and save the result
    if (result.result == 1) {
        printf("Test %d succeeded in %.2f seconds.\n", result.test_id, duration);
    } else {
        printf("Test %d failed in %.2f seconds.\n", result.test_id, duration);
    }

    save_test_result(&result, duration);
}

// Save the test result to a log file
/**
 * @brief Save the test result to a log file with a timestamp.
 *
 * This function logs the test ID, timestamp, duration, and result
 * (success or failure) to a file named `test_results.log`.
 *
 * @param[in] result Pointer to the test result structure.
 * @param[in] duration Duration of the test in seconds.
 */
void save_test_result(TestResult* result, double duration) {
    FILE* log_file = fopen("test_results.log", "a");
    if (!log_file) {
        perror("Error opening log file");
        return;
    }

    // Get the current timestamp
    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline character

    // Log the result
    fprintf(log_file, "Test-ID: %d, Timestamp: %s, Duration: %.2f seconds, Result: %s\n",
            result->test_id, timestamp, duration, (result->result == 1) ? "Success" : "Failure");

    fclose(log_file);
}

// Main function
/**
 * @brief Main function for the UDP client program.
 *
 * This function initializes a UDP socket, connects to the server,
 * and runs a loop to display the test menu and handle user commands.
 *
 * @return int Returns 0 on successful execution.
 */
int main() {
    int sock;
    struct sockaddr_in server_addr;

    // Create a UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Main loop
    while (1) {
        display_menu();
        send_test_command(sock, &server_addr);
    }

    close(sock);
    return 0;
}
