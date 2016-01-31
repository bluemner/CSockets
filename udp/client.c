#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main ( int argc, char ** argv )
{
	int clientSocket = 0,
	    portNumber = 9999,
		numberOfBytes = 0;
	char buffer[1024];
	struct sockaddr_in serverAddress;
	socklen_t address_size;
	
	//Create UDP socket
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
	
	//Configure settings in address struct
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);  
	
	//Initialize size variable to be used later on
	address_size = sizeof serverAddress;
	
	while (1)
	{
		printf("Type a sentence to send to server:\n");
		fgets(buffer,1024,stdin);
		if ( strcmp(buffer, "exit\n\0") == 0 || strcmp(buffer, "Exit\n\0") == 0 )
		{
			break;
		}
		printf("You typed: %s",buffer);
		
		numberOfBytes = strlen(buffer) + 1;
		
		//Send message to server
		sendto(clientSocket,buffer,numberOfBytes,0,(struct sockaddr *)&serverAddress,address_size);
		
		//Receive message from server
		numberOfBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
		
		printf("Received from server: %s\n",buffer);
	}
	return 0;
}