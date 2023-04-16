/**
 * @file ClientIO.c
 * @brief Contains functions for input and output
 *
 * This contains functions for input and output for the client,
 * including input from the terminal and output to the terminal,
 * as well as input from a file and output to a file.
 *
 * @author Braden Byrnes
 * @bug no known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include "ClientIO.h"

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
        printf("Error opening file");
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
        printf("Error opening file");
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

/**
 * @brief Outputs text to the terminal
 *
 * This function takes text and outputs it to the terminal.
 *
 * @param text The text to output to the terminal
 * @return void
 */
void outputToTerminal(char *text)
{
    printf("%s", text);
}

/**
 * @brief Inputs text from the terminal
 *
 * This function takes no parameters and returns the text input from the terminal.
 *
 * @return char* The text input from the terminal
 */
char *inputFromTerminal()
{
    // Allocate memory for string
    char *text = (char *)malloc(100);
    // Check if memory was allocated
    if (text == NULL)
    {
        // Exit with error code 1
        printf("Unable to allocate memory");
        exit(1);
    }
    // Get input from terminal
    int len = scanf("%s", text);
    // Check if input was read
    if (len == EOF)
    {
        // Exit with error code 2
        printf("Unable to read from terminal");
        exit(2);
    }
    return text;
}