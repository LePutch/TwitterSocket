#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int SOCKET;

#define TAILLE_PSEUDO 6


//Structure d'un message
typedef struct MessageList
{
    char* message;
    struct clientList *destinataires;
    struct MessageList *next;
}MessageList;

//Structure d'un abonné/abonnement
typedef struct clientList
{
    struct ClientServer *client;
    struct clientList *next;
}clientList;

//Structure d'un client coté serveur 
//Avec le pseudo, la socket, un tableau dynamique de ses abonnés
// et un tableau dynamique de ses messages
typedef struct ClientServer
{
    SOCKET socket;
    char* pseudo;
    struct clientList *abonnements;
    struct MessageList *messages;
    bool isConnected;
}ClientServer;


//Fonction des clients coté serveur
ClientServer* createClientServer(SOCKET socket, char* pseudo,MessageList *messages,clientList *abonnement);
void deleteClientServer(ClientServer *client);
void clientServerSubs(ClientServer *client, ClientServer *toSubs);
void clientServerUnsubs(ClientServer *client, ClientServer *toUnsubs);

MessageList *createMessageList(char *message, clientList *destinataires);
void addMessage(MessageList *messageList, char *message, clientList *destinataires);
void removeMessage(MessageList *messageList, char *message);
void deleteMessageList(MessageList *message);
int messageList_lenght(MessageList *messList);

clientList *createClientList(ClientServer *client);
void addClientList(clientList *list, ClientServer *client);
void removeClientList(clientList *list, ClientServer *client);
void deleteClientList(clientList *list);


char* client_to_string(ClientServer *client);
char* clients_to_string(clientList *cList);
char* clientList_to_string(clientList *cList);
char* messageList_to_string(MessageList *messList);
char* convertIntToString(int i);


#endif