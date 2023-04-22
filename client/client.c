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

void runClient()
{
    int sock = connectToServer();
    sendToServer(sock, "Hello from client");
    char *clientmessage = malloc(2000);
    char *servermessage;

    while (strcmp(clientmessage, "exit") != 0)
    {
        printf("Send a message to the server: ");
        scanf("%s", clientmessage);
        sendToServer(sock, clientmessage);
        servermessage = readServerMessage(sock);
        printf("Server: %s\n", servermessage);
    }
}