#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define PORT "7060" // Port to listen on 

//Get which ipv type
void *get_in_addr(struct sockaddr *sa)
{
  if(sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)))
  }
}



