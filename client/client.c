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
    long arr [5]= {1, 0, 1, -2, 3};
    size_t size = sizeof(arr)/ sizeof(arr[0]);
    sendintarray(sock, arr, size);
}