#ifndef CODE_CLIENT_H
#define CODE_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

typedef int SOCKET;

#define BUFFER_SIZE 1024 
#define TAILLE_PSEUDO 6
