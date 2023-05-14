#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/clientio.h"
#include "util/clientnetworking.h"

void sortInts();
void makeChoice();
void commWithServer();

int main(int argc, char *argv[])
{
    makeChoice();

    return 0;
}

void makeChoice()
{
    printf("choose a function to run\n");
    printf("1: send a message to the server\n");
    printf("2: sort an array of integers\n");
    printf("3: exit\n");

    int choice;
    scanf("%d", &choice);


    switch (choice)
    {
    case 1:
        commWithServer();
        break;

    case 2:
        sortInts();
        break;

    case 3:
        exit(0);
        break;
    default:
        printf("Invalid choice\n");
        makeChoice();
    }
}

void sortInts()
{
    // Connect to server and send initial message
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

    int sock = connectToServer();
    sendintarray(sock, arr, size);
    makeChoice();
}

void commWithServer()
{
    int sock = connectToServer();
    talkToServer(sock);

    makeChoice();
}