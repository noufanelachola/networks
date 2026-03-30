#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

int main(){

        int clientSocket;
        char buffer[1024];
        struct sockaddr_in serverAddr;
        socklen_t addrSize;

        clientSocket = socket(AF_INET,SOCK_STREAM,0);

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = inet_addr("172.18.100.10");

        memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

        addrSize = sizeof serverAddr;
        connect(clientSocket, (struct sockaddr *) &serverAddr, addrSize);

        while(true){
                printf("Enter the message : ");
                fgets(buffer,1024,stdin);

                printf("You entered : %s",buffer);
                send(clientSocket,buffer,1024,0);
        }
        return 0;
}