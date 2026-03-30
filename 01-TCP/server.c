#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>

int main() {
        int welcomeSocket, newSocket;

        char buffer[1024];

        struct sockaddr_in serverAddr;
        struct sockaddr_storage serverStorage;

        socklen_t addr_size;

        welcomeSocket = socket(AF_INET,SOCK_STREAM,0);
        if(welcomeSocket < 0){
                printf("Socket creation failed! \n");
                return 1;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = inet_addr("172.18.100.10");

        memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

        bind(welcomeSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr));


        if(listen(welcomeSocket,5) == 0 ){
                printf("Listening \n");
        } else {
                printf("Error\n");
        }


        addr_size = sizeof serverStorage;
        newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

        while(true){
                recv(newSocket,buffer,1024,0);
                printf("\nThe data we received : %s",buffer);
                memset(buffer,0,1024);
        }

        return 0;
}