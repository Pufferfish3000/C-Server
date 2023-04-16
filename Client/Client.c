#include <stdio.h>
#include "ClientFunctions/ClientIO.h"

int main(int argc, char *argv[])
{
    char *text = inputFromTerminal();

    outputToTerminal(text);

    return 0;
}