#include "Server.h"

#include <iostream>

int main() {
  if (server_initialize() != 0) {
    std::cerr << "¡Error inicializando el servidor!" << std::endl;
    return 1;
  }

  while (true) {
    SOCKET client_socket = listen_for_connections();
    if (client_socket == INVALID_SOCKET) {
      std::cerr << "ERROR" << std::endl;
      return 1;
    }
    server_loop(client_socket);
  }

}
