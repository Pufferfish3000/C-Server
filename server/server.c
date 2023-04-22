#include <stdio.h>
#include <string.h>
#include "util/serverfunctions.h"
#include "util/servernetworking.h"

void runServer();

int main(int argc, char *argv[])
{
    runServer();
    return 0;
}

void runServer()
{
    int clientsock = acceptConnections();
    char *message;
    message = readClientMessage(clientsock);
    while (strcmp(message, "exit") != 0)
    {
        message = readClientMessage(clientsock);
        printf("Client: %s\n", message);
        sendToClient(clientsock, "Hello from server");
    }
}