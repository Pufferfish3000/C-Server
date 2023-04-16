#include <stdio.h>
#include "ClientFunctions/ClientIO.h"

int main(int argc, char *argv[])
{
    char *filename = "test.txt";
    char *text = "testing\ntesting";
    fileOutput(filename, text);
    char *out = fileInput(filename);
    Output(out);

    return 0;
}