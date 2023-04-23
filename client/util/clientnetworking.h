#ifndef CLIENTNETWORKING_H
#define CLIENTNETWORKING_H

int connectToServer();
char *readServerMessage(int sock);
void sendToServer(int sock, char *message);

#endif