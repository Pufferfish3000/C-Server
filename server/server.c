#include <stdio.h>
#include "util/serverfunctions.h"
#include "util/servernetworking.h"

void runServer();

int main(int argc, char *argv[])
{
    runServer();
    return 0;
}

/**
 * @brief Runs the server
 *
 * This function runs the server and manages data sent to and from clients.
 *
 * @return void
 */
void runServer()
{
    // Create socket and accept connections from clients
    int clientsock = acceptConnections();
    char *message;
    while (1)
    {
        // Read messages from clients
        message = readClientMessage(clientsock);
        printf("Client: %s\n", message);
        // Send messages to clients
        sendToClient(clientsock, "Hello from server");
    }
}