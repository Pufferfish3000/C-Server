#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/clientio.h"
#include "util/clientnetworking.h"

void runClient();

int main(int argc, char *argv[])
{
    runClient();

    return 0;
}


/**
 * @brief Runs the client
 *
 * This function runs the client and manages data sent to and from the server.
 * 
 * @return void
 */
void runClient()
{
    // Connect to server and send initial message
    int sock = connectToServer();
    sendToServer(sock, "Hello from client");
    // Allocate memory for messages
    char *clientmessage = malloc(2000);
    char *servermessage;

    // Read messages from server and send messages to server until exit
    while (strcmp(clientmessage, "exit") != 0)
    {
        printf("Send a message to the server: ");
        scanf("%s", clientmessage);
        sendToServer(sock, clientmessage);
        servermessage = readServerMessage(sock);
        printf("Server: %s\n", servermessage);
    }
}