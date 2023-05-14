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
void clientChoice(int clientsock);
void *clientThread(void *);
void commWithClient(int clientsock);

// server socket, client socket, client size, and new socket
int sock, clientsock, c, *newSock;

/**
 * @brief Accepts connections from clients
 *
 * This function accepts connections from clients, and creates a thread for each client.
 *
 * @return int The exit status of the program
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

        // Create thread for client
        pthread_t sniffThread;

        // Create new socket for client
        newSock = malloc(1);
        *newSock = clientsock;

        // Create thread for client and check for errors
        if (pthread_create(&sniffThread, NULL, clientThread, (void *)newSock) < 0)
        {
            printf("Error when creating thread\n");
            return -1;
        }
    }

    return 0;
}

/**
 * @brief handles client and server communication
 *
 * This function handles communication between the client and server,
 * and calls the appropriate functions based on the client's choice.
 *
 * @param clientsock The client socket
 * @return void* NULL
 */
void *clientThread(void *clientsock)
{
    // get client socket from void pointer
    int sock = *(int *)clientsock;

    // get client choice
    clientChoice(sock);

    return NULL;
}

/**
 * @brief recieves an array of integers from the client, sorts it, and sends it back
 *
 * This function recieves an array of integers from the client, sorts it, and sends
 * the sorted array back to the client.
 *
 * @param clientsock The client socket
 * @return void
 */
void recvIntArr(int clientsock)
{
    // size of array
    size_t size;

    // read size of array
    read(clientsock, &size, sizeof(size_t));
    size = ntohl(size);

    // read array
    long intArr[size];
    read(clientsock, intArr, sizeof(intArr));

    // sort array
    quickSort(intArr, 0, size - 1);

    // send sorted array back to client
    send(clientsock, intArr, sizeof(intArr), 0);

    // close client socket
    close(clientsock);
}

/**
 * @brief communicates with the client
 *
 * This function communicates with the client, printing the client's message and
 * sending a confirmation message back to the client.
 *
 * @param clientsock The client socket
 * @return void
 */
void commWithClient(int clientsock)
{
    // read client message
    char *message = malloc(2000);
    read(clientsock, message, 2000);

    // print client message
    printf("Client message: %s\n", message);

    // send confirmation message
    send(clientsock, "Message Recieved", 2000, 0);

    // close client socket
    close(clientsock);
}

/**
 * @brief gets the client's choice and calls the appropriate function
 *
 * This function gets the client's choice and calls the appropriate function.
 *
 * @param clientsock The client socket
 * @return void
 */
void clientChoice(int clientsock)
{
    // client choice
    int choice;

    // read client choice
    read(clientsock, &choice, sizeof(int));
    choice = ntohl(choice);

    // print client choice
    printf("Choice: %d\n", choice);

    // call appropriate function based on client choice
    switch (choice)
    {
    // if choice is 1, call commWithClient which communicates with the client
    case 1:
        commWithClient(clientsock);
        break;

    // if choice is 2, call recvIntArr which recieves an array of integers from the client,
    // sorts it, and sends it back
    case 2:
        recvIntArr(clientsock);
        break;

    // if any other choice, do nothing
    default:
        break;
    }
}