/**
 * @file servernetworking.c
 * @brief Contains functions for networking
 *
 * This contains networking functions for the server,
 * including accepting connections and sending and receiving messages.
 *
 * @author Braden Byrnes
 * @bug no known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "servernetworking.h"

/**
 * @brief Accepts connections
 *
 * This function accepts connections from clients.
 *
 * @return int The socket of the client
 */
int acceptConnections()
{
    // server socket, client socket, client size
    int sock, clientsock, c;
    // server and client addresses
    struct sockaddr_in server, client;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // Check if socket was created
    if (sock == -1)
    {
        printf("Unable to create socket\n");
        return -1;
    }

    // Set server address, port, and family
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4735); // Random high port

    // Bind socket to address and check for errors
    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error when binding\n");
        return -1;
    }

    // Listen for connections
    listen(sock, 3);
    printf("Server listening\n");

    // Get client size
    c = sizeof(struct sockaddr_in);

    // Accept connection from client
    clientsock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
    // Check if connection was accepted
    if (clientsock < 0)
    {
        printf("Error when accepting\n");
        return -1;
    }

    // Return client socket
    return clientsock;
}

/**
 * @brief Receives messages from clients
 *
 * This function receives messages from clients.
 *
 * @param clientsock The socket of the client
 * @return char* The message from the client
 */
char *readClientMessage(int clientsock)
{
    char *message;
    int read_size;
    // Allocate memory for message
    message = malloc(2000);

    // Receive message from client
    read_size = recv(clientsock, message, 2000, 0);
    // Check if client disconnected
    if (read_size == 0)
    {
        printf("Client disconnected\n");
        fflush(stdout);
        return "exit";
    }
    // Check for errors when receiving
    else if (read_size == -1)
    {
        printf("Error when receiving\n");
    }

    return message;
}

/**
 * @brief Sends messages to clients
 *
 * This function sends messages to clients.
 *
 * @param clientsock The socket of the client
 * @param message The message to send to the client
 * @return void
 */
void sendToClient(int clientsock, char *message)
{
    // Send message to client and check for errors
    if (send(clientsock, message, strlen(message), 0) < 0)
    {
        printf("Error when sending\n");
    }
}
