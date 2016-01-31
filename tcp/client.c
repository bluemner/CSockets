// =====================================
// Description: simple tcp Client 
// Author: Brandon Bluemner
// =====================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int socketFileDescriptor,
       portNumber,
	   resultNumber;
   struct sockaddr_in server_address;
   struct hostent *server;
   
   char buffer[256];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
   portNumber = atoi(argv[2]);
   server = gethostbyname(argv[1]);
   
   //Create a socket point
   socketFileDescriptor = socket( AF_INET, SOCK_STREAM, 0 );
   
   if ( socketFileDescriptor < 0  ) 
   {
      perror("ERROR opening socket");
      exit( EXIT_FAILURE );
   }
	
   
   
   if ( server == NULL ) {
      fprintf(stderr,"ERROR, no such host\n");
      exit( EXIT_FAILURE );
   }
   
   bzero( (char *) &server_address, sizeof(server_address) );
   server_address.sin_family = AF_INET;
   bcopy( (char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length );
   server_address.sin_port = htons(portNumber);
   
   // Now connect to the server 
   if ( connect(socketFileDescriptor, (struct sockaddr*)&server_address, sizeof(server_address)) < 0 ) 
   {
      perror("ERROR connecting");
      exit( EXIT_FAILURE );
   }
   
    while( 1 )
    {   
		// Now ask for a message from the user, this message
		// will be read by server
		printf("Please enter the message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		
		if( strcmp( "exit\n" , buffer ) == 0 )
		{
		    resultNumber = write( socketFileDescriptor, "^c\n", strlen(buffer) );
			break;			
		}
		
		// Send message to the server 
		resultNumber = write( socketFileDescriptor, buffer, strlen(buffer) );
		
		if ( resultNumber < 0 ) {
			perror("ERROR writing to socket");
			exit( EXIT_FAILURE );
		}	
		
		// Now read server response 
		bzero(buffer,256);
		resultNumber = read(socketFileDescriptor, buffer, 255);
		
		if ( resultNumber < 0 ) 
		{
			perror("ERROR reading from socket");
			exit( EXIT_FAILURE );
		}
	    printf("%s\n",buffer);
    }

   return 0;
}