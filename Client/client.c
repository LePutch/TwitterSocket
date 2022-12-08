#include "client.h"

void start_client(char* ip, int port){
    printf("\n\nBonjour ! Bienvenue sur SocketTwitter !\n\n\n\n");
    menu();
    SOCKET socket_client = init_client(ip, port);
    char buffer[MAX_BUFFER_SIZE];

    fd_set readfds;
    int maxFD = socket_client;

    while(1){
        FD_ZERO(&readfds);
        FD_SET(socket_client, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int resultSelect = select(maxFD + 1, &readfds, NULL, NULL, NULL);
        check_error(resultSelect, "error in select()\n")

        if (FD_ISSET(STDIN_FILENO,&readfds)){
            if (!request_server(socket_client, buffer)){
                break;
            }
        }
        else if(FD_ISSET(socket_client, &readfds)){
            if (!receive_server(socket_client, buffer)){
                break;
            }
        }
    }
    end_client(socket_client);
}

void menu(){
    printf("MENU\n");
    printf("1. Se connecter\n");
    printf("2. S'inscrire\n");
    printf("3. Quitter\n");
}

int request_server(SOCKET client_socket, char* buffer){
    return 1;
}

int receive_server(SOCKET client_socket, char* buffer){
    return 1;
}

void end_client(SOCKET client_socket){
    printf("Closing client socket\n");
    close(client_socket);
}

int init_client(char* ip, int port){
    SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    socklen_t taille = sizeof(struct sockaddr);

    check_error(socketClient, "error in initialization socket()\n")

    sin.sin_addr.s_addr = inet_addr(ip); 
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET; 
    int connectionResult = connect(socketClient,(struct sockaddr*) &sin, taille); 
    check_error(connectionResult, "error in connect()\n")

    return socketClient; 
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        return EXIT_FAILURE;
    }

    start_client(argv[1], atoi(argv[2]));
    return EXIT_SUCCESS;
}