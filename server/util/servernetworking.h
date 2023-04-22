#ifndef SERVERNETWORKING_H
#define SERVERNETWORKING_H

int acceptConnections();
char *readClientMessage(int clientsock);
void sendToClient(int clientsock, char *message);

#endif