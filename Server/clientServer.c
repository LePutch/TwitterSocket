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
    if (temp == NULL){
        messageList = createMessageList(message, destinataires);
        return;
    }
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
clientList *createClientList(ClientServer *cl){
    clientList *list = malloc(sizeof(clientList));
    list->client = cl;
    list->next = NULL;
    return list;
}

void addClientList(clientList *list, ClientServer *client){
    clientList *temp = list;
    if (temp == NULL){
        list = createClientList(client);
        return;
    }
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

int messageList_lenght(MessageList *messList){
    int i = 0;
    MessageList *temp = messList;
    while(temp != NULL){
        i++;
        temp = temp->next;
    }
    return i;
}

char* convertIntToString(int i){
    char *str = malloc(sizeof(char)*10);
    sprintf(str,"%d",i);
    return str;
}

char* messageList_to_string(MessageList *messList){
    char *mess = malloc(sizeof(char)*1000);
    MessageList *temp = messList;
    strcat(mess,strcat(convertIntToString(messageList_lenght(temp)),"\n"));
    while(temp != NULL){
        mess = strcat(strcat(mess,temp->message),"\n");
        mess = strcat(mess,clientList_to_string(temp->destinataires));
        mess = strcat(mess,"\n");
        temp = temp->next;
    }
    return mess;
}

char* clientList_to_string(clientList *cList){
    char *mess = malloc(sizeof(char)*1000);
    clientList *temp = cList;
    while(temp != NULL){
        ClientServer* current = temp->client;
        if (current ==NULL){
            temp = temp->next;
            continue;
        }
        mess = strcat(mess,current->pseudo);
        mess = strcat(mess," ");
        temp = temp->next;
    }
    
    return mess;
}

char* client_to_string(ClientServer *client){
    char *mess = malloc(sizeof(char)*1000);
    mess = strcat(client->pseudo,"\n");
    mess = strcat(mess,clientList_to_string(client->abonnements));
    mess = strcat(mess,"\n");
    mess = strcat(mess,messageList_to_string(client->messages));
    mess = strcat(mess,"\n");
    return mess;
}

char* clients_to_string(clientList *cList){
    char *mess = malloc(sizeof(char)*10000);
    clientList *temp = cList;
    while(temp != NULL){
        mess = strcat(mess,client_to_string(temp->client));
        temp = temp->next;
    }
    return mess;
}
