#include <stdio.h>
#include "util/serverfunctions.h"
#include "util/servernetworking.h"

void runServer();

/**
 * @brief Main function
 * 
 *  This function is the main function, which is called when the program is run.
 * 
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return int The exit status of the program
 */
int main(int argc, char *argv[])
{
    // Run the runServer function, which runs the server
    acceptConnections();
    return 0;
}