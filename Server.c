#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

int main() {
  int sockfd, nsock;
  struct sockaddr_in server_addr, client_addr;
  
  char buffer[256];
  int rand_num;
  int n;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    perror ("Error opening socket");
    
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8080);
  
  if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    perror ("Error on binding");
    
  listen (sockfd, 5);
  socklen_t client_length = sizeof(client_addr);
  nsock = accept(sockfd, (struct sockaddr *) &client_addr, &client_length);
  
  if (nsock < 0)
    perror ("Error on accept");
    
  srand (time(NULL));
  rand_num = (rand() % 900) + 100;
  sprintf(buffer, "%d", rand_num);
  n = write (nsock, buffer, sizeof(buffer));
  
  if (n < 0)
    perror ("Error writing to socket");
    
  close(nsock);
  close(sockfd);
  return0;
}

void error (constchar *msg) {
  perror(msg);
  exit(1); }
