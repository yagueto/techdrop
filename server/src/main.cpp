#include "Server.h"

#include <iostream>

int main() {
  SOCKET client_socket = listen_for_connections();
  if (client_socket == INVALID_SOCKET) {
    std::cerr << "ERROR" << std::endl;
  }
  server_loop(client_socket);
}
