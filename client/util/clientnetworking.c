#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int connectToServer()
{
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Unable to create socket\n");
        return -1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
    server.sin_family = AF_INET;
    server.sin_port = htons(4735); // Server port

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Unable to connect\n");
        return -1;
    }

    printf("Connected\n");

    return sock;
}

char *readServerMessage(int sock)
{
    char *message = malloc(2000);
    if (recv(sock, message, 2000, 0) < 0)
    {
        printf("Unable to receive\n");
        return "exit";
    }
    return message;
}

void sendToServer(int sock, char *message)
{
    if (send(sock, message, strlen(message), 0) < 0)
    {
        printf("Unable to send\n");
    }
}