#include "clientServer.h"


//Création d'un clientServer 
ClientServer* createClientServer(SOCKET socket, char* pseudo,MessageList *messages,clientList *abonnement){
    ClientServer *client = malloc(sizeof(ClientServer));
    client->socket = socket;
    strcpy(client->pseudo, pseudo);
    client->messages = messages;
    client->abonnements = abonnement;
    client->isConnected = false;
    return client;
}

void deleteClientServer(ClientServer *client){
    deleteMessageList(client->messages);
    deleteClientList(client->abonnements);
    free(client);
}

void clientServerSubs(ClientServer *client, ClientServer *toSubs){
    addClientList(client->abonnements, toSubs);
}

//Fonctions d'abonnements/désabonnements
void clientServerUnsubs(ClientServer *client, ClientServer *toUnsubs){
    removeClientList(client->abonnements, toUnsubs);
}


//Création d'un message (les messages de chaque serverClient)
MessageList *createMessageList(char *message, clientList *destinataires){
    MessageList *msg = malloc(sizeof(MessageList));
    msg->message = message;
    msg->destinataires = destinataires;
    msg->next = NULL;
    return msg;
}

void addMessage(MessageList *messageList, char *message, clientList *destinataires){
    MessageList *temp = messageList;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createMessageList(message, destinataires);
}

void removeMessage(MessageList *messageList, char *message){
    MessageList *temp = messageList;
    if (temp->message == message){
        MessageList *next = temp->next;
        free(temp);
        messageList = next;
        return;
    }
    while(temp->next != NULL){
        if(temp->next->message == message){
            MessageList *next = temp->next->next;
            free(temp->next);
            temp->next = next;
            return;
        }
        temp = temp->next;
    }
}

void deleteMessageList(MessageList *messages){
    MessageList *temp = messages;
    while(temp != NULL){
        MessageList * next = temp->next;
        deleteClientList(temp->destinataires);
        free(temp);
        temp = next;
    }
}


//Création d'une liste de clients (les abonnements de chaque serverClient)
clientList *createClientList(ClientServer *client){
    clientList *list = malloc(sizeof(clientList));
    list->client = client;
    list->next = NULL;
    return list;
}

void addClientList(clientList *list, ClientServer *client){
    clientList *temp = list;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createClientList(client);
}

void removeClientList(clientList *list, ClientServer *client){
    clientList *temp = list;
    if (temp->client == client){
        clientList *next = temp->next;
        free(temp);
        list = next;
        return;
    }
    while(temp->next != NULL){
        if(temp->next->client == client){
            clientList *next = temp->next->next;
            free(temp->next);
            temp->next = next;
            return;
        }
        temp = temp->next;
    }
}

void deleteClientList(clientList *list){
    clientList *temp = list;
    while(temp != NULL){
        clientList * next = temp->next;
        deleteClientServer(temp->client);
        free(temp);
        temp = next;
    }
}

