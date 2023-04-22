#include <stdio.h>
#include "util/clientio.h"

int main(int argc, char *argv[])
{
    char *text = inputFromTerminal();

    outputToTerminal(text);

    return 0;
}