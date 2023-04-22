#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "servernetworking.h"

int acceptConnections()
{
    int sock, clientsock, c;
    struct sockaddr_in server, client;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Unable to create socket\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4735); // Random high port

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error when binding\n");
        return -1;
    }

    listen(sock, 3);

    printf("Server listening\n");
    c = sizeof(struct sockaddr_in);

    clientsock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
    if (clientsock < 0)
    {
        printf("Error when accepting\n");
        return -1;
    }

    return clientsock;
}

char *readClientMessage(int clientsock)
{
    char *message;
    int read_size;

    message = malloc(2000);
    read_size = recv(clientsock, message, 2000, 0);
    if (read_size == 0)
    {
        printf("Client disconnected\n");
        fflush(stdout);
        return "exit";
    }
    else if (read_size == -1)
    {
        printf("Error when receiving\n");
    }

    return message;
}

void sendToClient(int clientsock, char *message)
{
    if (send(clientsock, message, strlen(message), 0) < 0)
    {
        printf("Error when sending\n");
    }
}
