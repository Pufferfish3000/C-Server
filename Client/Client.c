#include <stdio.h>

void fileOutput(char* filename, char* text);

int main(int argc, char *argv[])
{
    char* filename = "test.txt";
    char* text = "test";
    fileOutput(filename, text);

    return 0;
}

void fileOutput(char* filename, char* text)
{
    FILE *pF = fopen(filename, "w");

    fprintf(pF, text);

    fclose(pF);
}