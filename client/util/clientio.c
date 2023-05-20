/**
 * @file clientio.c
 * @brief Contains functions for input and output
 *
 * This contains functions for input and output for the client,
 * including input from a file and output to a file.
 *
 * @author Braden Byrnes
 * @bug no known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include "clientio.h"

struct node
{
    char *data;
    struct node *next;
};

typedef struct node node_t;

node_t *head = NULL;

void startLog()
{
    node_t *startLog = (node_t *)malloc(sizeof(node_t));
    startLog->data = "---Start of Log---";
    startLog->next = head;
    head = startLog;
}

void addLog(char *text)
{
    printf("1\n");
    node_t *newLog = (node_t *)malloc(sizeof(node_t));
    printf("2\n");
    newLog->data = text;
    printf("3\n");
    node_t *log = head;
    printf("4\n");
    while (log->next != NULL)
    {
        printf("5\n");
        log = log->next;
        printf("6\n");
    }
    printf("7\n");
    log->next = newLog;

    printf("8\n");
}

void printLogs()
{
    node_t *log = head;
    while (log != NULL)
    {
        printf("%s\n", log->data);
        log = log->next;
    }
}
/**
 * @brief Outputs text to a file
 *
 * This function takes a filename and text and outputs the text to the file.
 *
 * @param filename The name of the file to output to
 * @param text The text to output to the file
 * @return void
 */
void outputToFile(char *filename, char *text)
{
    FILE *pF = fopen(filename, "w");
    // Check if file exists
    if (NULL == pF)
    {
        printf("Error opening file\n");
    }
    else
    {
        // Write to file
        fprintf(pF, "%s", text);
    }
}

/**
 * @brief Inputs text from a file
 *
 * This function takes a filename and returns the text from the file.
 *
 * @param filename The name of the file to input from
 * @return char* The text from the file
 */
char *inputFromFile(char *filename)
{
    FILE *pF = fopen(filename, "r");
    char *text;

    // Check if file exists
    if (NULL == pF)
    {
        printf("Error opening file\n");
    }
    else
    {
        // Get file size
        fseek(pF, 0, SEEK_END);
        long size = ftell(pF);
        // Reset file pointer
        rewind(pF);
        // Allocate memory for string
        text = (char *)malloc(size + 1);
        // Read file into string
        fread(text, 1, size, pF);
        // Add null terminator
        text[size] = '\0';
    }
    return text;
}