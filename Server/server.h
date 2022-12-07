#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "clientServer.h"

#define PORT 5000
#define MAX_CLIENTS 10
#define MAX_MSG_SIZE 1024

enum requestType {
    SUBSCRIBE,
    UNSUBSCRIBE,
    PUBLISH,
    LIST,
    QUIT
};

#define check_error(expr, userMsg)\
    do {\
        if (expr==-1) {\
            perror(userMsg);\
            exit(errno);\
        }\
    } while (0);


static clientList *clients;

void save_as_dat(char* file_path);
void load_from_dat(char* file_path);

void start_server(int port);
int init_server(int port);
void end_server(int server_socket);

void handle_request(fd_set readfds, int server_socket);

void handle_subscribe(int client_socket);
void handle_unsubscribe(int client_socket);
void handle_publish(int client_socket);
void handle_list(int client_socket);
void handle_quit(int client_socket);

void send_message(int client_socket, char* message);
void send_message_to_clientList(int client_socket, char* message, clientList *list);