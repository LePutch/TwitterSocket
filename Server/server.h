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


static clientList *clients;

void save_as_txt(char* file_path,char* data);
void load_from_txt(char* file_path);

void start_server(int port);
int init_server(int port);
void end_server(int server_socket);

void handle_request(fd_set readfds, int server_socket);

void handle_subscribe(char *buffer ,int client_socket);
void handle_unsubscribe(char *buffer, int client_socket);
void handle_publish(char *buffer, int client_socket);
void handle_list(char *buffer, int client_socket);
void handle_quit(char *buffer, int client_socket);
void handle_new_client(char *buffer, int client_socket);
void handle_login(char *buffer, int client_socket);

void send_message(int client_socket, char* message);
void send_message_to_clientList(int client_socket, char* message, clientList *list);

void test_dataBase();


/*

DATA FORMAT:

pseudo1
subbedto pseudo list
n-messages
message1
receiver1 receiver2 receiver3...
message2
receiver1 receiver2 receiver3...
...
pseudo2
...

*/