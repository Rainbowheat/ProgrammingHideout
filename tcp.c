#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int errHnd(int value, char *message, int errorVal) {
  if (value == errorVal) {
    printf("%s\n", message);
    return 1;
  }
  return 0;
}

int main(void) {
  printf("configuring local address\n");

  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;

  if (getaddrinfo(0, "8080", &hints, &bind_address) == -1) {
    printf("getaddrinfo failed");
    return 1;
  };

  printf("CREATING SOCKET");
  int socket_listen;
  socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                         bind_address->ai_protocol);

  errHnd(socket_listen, "socket creation failed", -1);

  printf("Binding socket to local address");

  if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen) !=
      0) {
    printf("binding failed");
  }

  freeaddrinfo(bind_address);

  printf("listening");

  errHnd(listen(socket_listen, 10), "Socket fail to listen", -1);

  printf("Waiting for connections");

    struct sockaddr_storage client_addresses;

    socklen_t client_len = sizeof(client_addresses);

    int socket_client = accept(
        socket_listen, (struct sockaddr *)&client_addresses, &client_len);

    errHnd(socket_client, "Sock Client Failed", -1);

    printf("client connected");

    char address_buffer[100];
    getnameinfo((struct sockaddr *)&client_addresses, client_len,
                address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

    printf("%s\n", address_buffer);

    printf("reading a request");

    char request[1024];

    int bytesRecieved = recv(socket_client, request, 1024, 0);

    printf("%.*s\n", bytesRecieved, request);

    time_t timer;
    time(&timer);
    char *time_message = ctime(&timer);

    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Connection: close\r\n"
                           "Content-Type: text/plain\r\n\r\n"
                           "Local time is: ";

    int byte_sent = send(socket_client, response, strlen(response), 0);
    byte_sent = send(socket_client, time_message, strlen(time_message), 0);

    close(socket_client);
    close(socket_listen);
  
  return 0;
}
