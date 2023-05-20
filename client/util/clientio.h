#ifndef CLIENTIO_H
#define CLIENTIO_H

void outputToFile(char *filename, char *text);
char *inputFromFile(char *filename);
void startLog();
void printLogs();
void addLog(char *text);

#endif