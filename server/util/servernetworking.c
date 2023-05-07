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
#include <unistd.h> 
#include <pthread.h>
#include "servernetworking.h"
#include "serverfunctions.h"
void sendToClient(int clientsock, char *message);
struct clientMessageData readClientMessage(int clientsock);
void *clientThread(void *);

struct clientMessageData
{
    int readSize;
    char *message;
};

// server socket, client socket, client size, and new socket
int sock, clientsock, c, *newSock;
/**
 * @brief Accepts connections
 *
 * This function accepts connections from clients.
 *
 * @return int The socket of the client
 */
int acceptConnections()
{
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
    while ((clientsock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        printf("Connection accepted\n");

        pthread_t sniffThread;
        newSock = malloc(1);
        *newSock = clientsock;

        if (pthread_create(&sniffThread, NULL, clientThread, (void *)newSock) < 0)
        {
            printf("Error when creating thread\n");
            return -1;
        }
    }

    // old code, may be useful later
    // // Check if connection was accepted
    // if (clientsock < 0)
    // {
    //     printf("Error when accepting\n");
    //     return -1;
    // }

    // // Return client socket
    // return clientsock;

    return 0; // temporary return value
}

void *clientThread(void *clientsock)
{
    // main client logic
    int sock = *(int*)clientsock;
    recvIntArr(sock);

    return NULL;
}

/**
 * @brief Receives messages from clients
 *
 * This function receives messages from clients.
 *
 * @param clientsock The socket of the client
 * @return char* The message from the client
 */
struct clientMessageData readClientMessage(int clientsock)
{
    struct clientMessageData s;

    // Allocate memory for message
    s.message = malloc(2000);

    // Receive message from client
    s.readSize = recv(clientsock, s.message, 2000, 0);
    // Check for errors when receiving
    if (s.readSize == -1)
    {
        printf("Error when receiving\n");
    }

    return s;
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

void recvIntArr(int clientsock)
{
    size_t size;

    read (clientsock, &size, sizeof(size_t));
    size = ntohl(size);

    long intArr[size];
    read(clientsock, intArr, sizeof(intArr));

    quickSort(intArr, 0, size - 1);

    send(clientsock, intArr, sizeof(intArr), 0);
}