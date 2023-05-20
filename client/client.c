#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/clientio.h"
#include "util/clientnetworking.h"

void sortInts();
void makeChoice();
void commWithServer();
void resartClient();

/**
 * @brief Main function
 *
 * This function is the main function, which is called when the program is run.
 *
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return int The exit status of the program
 */
int main(int argc, char *argv[])
{
    // Runs the makeChoice function, prompting the user to choose a function
    startLog();
    makeChoice();
    return 0;
}

void resartClient()
{
    getchar();
    makeChoice();
}

/**
 * @brief Prompts the user to choose a function
 *
 * This function prompts the user to choose a function to run,
 * and then runs that function.
 *
 * @return void
 */
void makeChoice()
{
    // Prompt user to choose a function
    printf("choose a function to run\n");
    printf("1: send a message to the server\n");
    printf("2: sort an array of integers\n");
    printf("3: exit\n");

    // Get user choice
    int choice;
    scanf("%d", &choice);

    // Run function based on user choice
    switch (choice)
    {
    // if the user chooses 1, run the commWithServer function,
    // which sends a message to the server
    case 1:
        addLog("User Communicates with Server\n");
        commWithServer();
        break;
    // if the user chooses 2, run the sortInts function,
    // which sorts an array of integers
    case 2:
        addLog("User Sorts Integers\n");
        sortInts();
        break;
    // if the user chooses 3, exit the program
    case 3:
        addLog("User Exits Program\n");
        exportLogs();
        exit(0);
        break;
    // if the user chooses anything else, prompt them to choose again
    default:
        addLog("User Chooses Invalid Option\n");
        printf("Invalid choice\n");
        resartClient();
    }
}

/**
 * @brief Sorts an array of integers
 *
 * This function prompts the user to enter an array of integers,
 * and then sends that array to the server to be sorted, then it
 * receives the sorted array back from the server and prints it.
 *
 * @return void
 */
void sortInts()
{
    // Get array size from user
    size_t size;
    printf("how many numbers are in your array?\n");
    scanf("%ld", &size);
    // Get array from user
    long arr[size];
    printf("Enter %ld numbers:\n", size);
    for (int i = 0; i < size; i++)
    {
        scanf("%ld", &arr[i]);
    }

    // connect to the server
    int sock = connectToServer();
    // send the array to the server to be sorted
    sendintarray(sock, arr, size);

    // prompt the user to choose a function again
    resartClient();
}

/**
 * @brief Sends a message to the server
 *
 * This function prompts the user to enter a message,
 * and then sends that message to the server.
 *
 * @return void
 */
void commWithServer()
{
    // connect to the server
    int sock = connectToServer();
    // talk to the server
    talkToServer(sock);

    // prompt the user to choose a function again
    resartClient();
}