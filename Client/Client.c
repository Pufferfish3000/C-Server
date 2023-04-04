#include <stdio.h>

void fileOutput(char* filename, char* text);
void Output(char* text);
char* fileInput(char* filename);

int main(int argc, char *argv[])
{
    char* filename = "test.txt";
    char* text = "testing \n testing";
    fileOutput(filename, text);

    Output(fileInput(filename));
    return 0;
}

void fileOutput(char* filename, char* text)
{
    FILE *pF = fopen(filename, "w");

    fprintf(pF, text);

    fclose(pF);
}

char* fileInput(char* filename)
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
        text = (char*)malloc(size + 1);
        // Read file into string
        fread(text, 1, size, pF);
        // Add null terminator
        text[size] = '\0';
    }
    return text;
}

void Output(char* text)
{
    printf(text);
}