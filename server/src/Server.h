#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

enum MESSAGE_TYPE {
  LOGIN,
  REGISTER,
  PEDIDO_MENU,
  PEDIDO_CREATE,
  PEDIDO_STATE,
  PEDIDO_LIST,
  PEDIDO_CANCEL,
  CLOSE
};



SOCKET listen_for_connections();
void server_loop(const SOCKET &client_socket);
void handle_message(const std::string &message);
void close_connection(SOCKET &client_socket);

#endif // SERVER_H
