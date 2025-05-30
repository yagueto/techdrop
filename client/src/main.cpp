#include "Socket.h"
#include "road_status.h"
#include "screens/MenuPrincipal.h"
#include <iostream>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000

int main() {
  if (!Socket::initializeWinSock()) {
    std::cerr << "¡Error inicializando el cliente!" << std::endl;
    return 1;
  }

  Socket socket;
  if (!socket.create(Socket::CLIENT)) {
    std::cerr << "¡Error inicializando el socket!" << std::endl;
    return 1;
  };
  if (!socket.connect_to_server(SERVER_IP, SERVER_PORT)) {
    std::cerr << "¡Error conectando al servidor!" << std::endl;
    return 1;
  }
  MenuPrincipal menu(socket);
  menu.display();

  auto ignore = socket.receive_message();
  socket.close();

  return 0;
}
