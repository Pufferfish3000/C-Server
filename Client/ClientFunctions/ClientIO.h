#ifndef CLIENTIO_H
#define CLIENTIO_H

void outputToFile(char *filename, char *text);
char *inputFromFile(char *filename);
void outputToTerminal(char *text);
char *inputFromTerminal();

#endif