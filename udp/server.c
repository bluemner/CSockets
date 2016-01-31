#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main ( int argc, char ** argv )
{
    int udpSocket = 0,
        numberOfBytes = 0,
        port = 9999;
    char buffer[1024];
    char ipstr[INET6_ADDRSTRLEN];
    struct sockaddr_in serverAddress;//, clientAddress;
    struct sockaddr_storage serverStorage;
    socklen_t address_size;//, client_address_size;
 
  
    //Create UDP socket
    udpSocket = socket( PF_INET, SOCK_DGRAM, 0);
  
    //Configure settings in address struct
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset( serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero );  
  
    //Bind socket with address struct
    bind( udpSocket, ( struct sockaddr *) &serverAddress, sizeof(serverAddress) );
  
    //Initialize size variable to be used later on*/
    address_size = sizeof ( serverStorage );
  
    int i;
    int clientPort = 0;
    while (1)
    {
      // Try to receive any incoming UDP datagram. Address and port of 
      // requesting client will be stored on serverStorage variable 
      numberOfBytes = recvfrom( udpSocket, buffer, 1024, 0, (struct sockaddr *) &serverStorage, &address_size);
      
    
     getpeername(udpSocket, (struct sockaddr*)&serverStorage, &address_size);
     // deal with both IPv4 and IPv6:
      if (serverStorage.ss_family == AF_INET) {
          struct sockaddr_in *socket = (struct sockaddr_in *)&serverStorage;
          clientPort = ntohs(socket->sin_port);
          inet_ntop(AF_INET, &socket->sin_addr, ipstr, sizeof ipstr);
      } else { // AF_INET6
          struct sockaddr_in6 *socket = (struct sockaddr_in6 *)&serverStorage;
          clientPort = ntohs(socket->sin6_port);
          inet_ntop(AF_INET6, &socket->sin6_addr, ipstr, sizeof ipstr);
      }
     printf("Peer IP address: %s\n", ipstr);
     printf("Peer port      : %d\n", clientPort);
     printf("%s:%d sent : %s\n", ipstr,clientPort, buffer);

      //Convert message received to uppercase
      for( i = 0; i < numberOfBytes - 1 ; i++ )
      {
          buffer[i] = toupper(buffer[i]);
      }
      //Send uppercase message back to client, using serverStorage as the address
      sendto( udpSocket, buffer, numberOfBytes, 0, ( struct sockaddr *) &serverStorage, address_size);
    }

  return 0;
}