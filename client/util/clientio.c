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

void outputToFile(char *filename, char *text);
char *inputFromFile(char *filename);

// node struct for linked list
struct node
{
    char *data;
    struct node *next;
};

// typedef for easier reading when using node struct
typedef struct node node_t;

// head of linked list
node_t *head = NULL;

/**
 * @brief Starts the log
 * 
 * This function starts the log by adding a node to the beginning of the linked list,
 * containing the text "---Start of Log---"
 * 
 * @return void
*/
void startLog()
{
    // allocate memory for node
    node_t *startLog = (node_t *)malloc(sizeof(node_t));
    // set data and next
    startLog->data = "---Start of Log---\n";
    startLog->next = head;
    // set startLog as first node
    head = startLog;
}

/**
 * @brief Adds a log to the linked list
 * 
 * This function adds a log to the linked list by adding a node to the end of the linked list,
 * 
 * @param text The text to add to the log
 * @return void
*/
void addLog(char *text)
{
    // allocate memory for node
    node_t *newLog = (node_t *)malloc(sizeof(node_t));
    // set data and next
    newLog->data = text;
    node_t *log = head;

    // iterate through linked list to find last node
    while (log->next != NULL)
    {
        log = log->next;
    }
    // set last node's next to new node
    log->next = newLog;
}

/**
 * @brief Exports the logs to a file
 * 
 * This function exports the logs to a file by iterating through the linked list and
 * outputting each node to a file.
 * 
 * @return void
*/
void exportLogs()
{
    // iterate through linked list
    node_t *log = head;
    while (log != NULL)
    {
        // append log to file "client.log"
        outputToFile("client.log", log->data);
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
    FILE *pF = fopen(filename, "a");
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
    fclose(pF);
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