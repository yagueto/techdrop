#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


int server_initialize();
SOCKET listen_for_connections();
void server_loop(const SOCKET &client_socket);
void close_connection(SOCKET &client_socket);

#endif // SERVER_H
