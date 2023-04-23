/**
 * @file clientnetworking.c
 * @brief Contains functions for networking
 *
 * This contains networking functions for the client,
 * including connecting to the server and sending and receiving messages.
 *
 * @author Braden Byrnes
 * @bug no known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * @brief Connects to the server
 *
 * This function connects to the server.
 *
 * @return int The socket of the server
 */
int connectToServer()
{
    // server socket
    int sock;
    // server address
    struct sockaddr_in server;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // Check if socket was created
    if (sock == -1)
    {
        printf("Unable to create socket\n");
        return -1;
    }

    // Set server address, port, and family
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    server.sin_family = AF_INET;
    server.sin_port = htons(4735); // Server port

    // Connect to server and check for errors
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected\n");

    // Return server socket
    return sock;
}

/**
 * @brief Receives messages from the server
 *
 * This function receives messages from the server.
 *
 * @param sock The socket of the server
 * @return char* The message received from the server
 */
char *readServerMessage(int sock)
{
    // Allocate memory for message
    char *message = malloc(2000);

    // Receive message from server and check for errors
    if (recv(sock, message, 2000, 0) < 0)
    {
        printf("Unable to receive\n");
        return "exit";
    }

    return message;
}

/**
 * @brief Sends messages to the server
 *
 * This function sends messages to the server.
 *
 * @param sock The socket of the server
 * @param message The message to send to the server
 * @return void
 */
void sendToServer(int sock, char *message)
{
    // Send message to server and check for errors
    if (send(sock, message, strlen(message), 0) < 0)
    {
        printf("Unable to send\n");
    }
}