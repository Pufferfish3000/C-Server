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
#include <unistd.h>
void sendInt(int sock, int num);

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
    sendInt(sock, 1);
    // Send message to server and check for errors
    if (send(sock, message, strlen(message), 0) < 0)
    {
        printf("Unable to send\n");
    }
}

/**
 * @brief Sends an array of integers to the server
 *
 * This function sends an array of variable size integers to the server
 * and receives the sorted array back.
 *
 * @param sock The socket of the server
 * @param intarray The array of integers to send to the server
 * @param size The size of the array
 * @return void
 */
void sendintarray(int sock, long *intarray, size_t size)
{
    // Send int 2 to the server to signal that we are using the sort function
    sendInt(sock, 2);

    // create a new array to store the sorted array
    long newArray[size];
    // convert size to network byte order
    size_t sentsize = htonl(size);

    // send the size of the array and the array to the server
    send(sock, &sentsize, sizeof(size_t), 0);
    send(sock, intarray, sizeof(long) * size, 0);

    // read the sorted array from the server
    read(sock, newArray, sizeof(newArray));

    // print the sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%ld\n", newArray[i]);
    }
}

/**
 * @brief Sends an integer to the server
 *
 * This function sends an integer to the server.
 *
 * @param sock The socket of the server
 * @param num The integer to send to the server
 * @return void
 */
void sendInt(int sock, int num)
{
    // convert num to network byte order
    num = htonl(num);
    // send num to the server
    send(sock, &num, sizeof(int), 0);
}

/**
 * @brief Sends a message to the server and receives a message back
 *
 * This function sends a message to the server and receives a message back.
 *
 * @param sock The socket of the server
 * @return void
 */
void talkToServer(int sock)
{
    // send int 1 to the server to signal that we are using the talk function
    sendInt(sock, 1);

    // messge to send to the server
    char message[2000];
    // index of message
    int i = 0;

    // eat newline character in buffer
    char c = getchar();
    // prompt user for message
    printf("enter a message %c", c);

    // get message from user, stopping at newline character
    while ((message[i++] = getchar()) != '\n')
        ;

    printf("Sending: %s\n", message);
    // send message to server
    send(sock, message, strlen(message), 0);
    // read message from server
    read(sock, message, 2000);
    // print message from server
    printf("Server Message: %s\n", message);
}