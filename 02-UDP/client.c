#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char* argv[]){
	int sockfd;
	struct sockaddr_in server;
        char buffer[100];

	if(argc!=3){
		printf("Usage: %s <server_ip> <port>\n", argv[0]);
		return 1;
	}
			
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	if (sockfd < 0){
	        printf("Error in socket creation\n");
       		return 1;
	}


	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
        server.sin_addr.s_addr = inet_addr(argv[1]);

	printf("Enter message to send: ");
	fgets(buffer, sizeof(buffer), stdin);

	if (sendto(sockfd, buffer, strlen(buffer), 0,(struct sockaddr *)&server, sizeof(server)) < 0){
	        printf("Error in sendto()\n");
        	return 1;
  	}

	printf("Message sent successfully\n");
    	return 0;
}