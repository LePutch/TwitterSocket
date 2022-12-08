#ifndef CODE_CLIENT_H
#define CODE_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef int SOCKET;
#define MAX_BUFFER_SIZE 1024

enum requestType {
    SUBSCRIBE=0,
    UNSUBSCRIBE=1,
    PUBLISH=2,
    LIST=3,
    QUIT=4,
    NEW_CLIENT=5,
    LOGIN=6,
};

#define check_error(expr, userMsg)\
    do {\
        if (expr==-1) {\
            perror(userMsg);\
            exit(errno);\
        }\
    } while (0);



void menu();

void start_client(char* ip, int port);
int init_client(char* ip, int port);
void end_client(SOCKET client_socket);

int request_server(SOCKET client_socket, char* buffer);
int receive_server(SOCKET client_socket, char* buffer);

#endif