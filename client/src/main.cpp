#include "Socket.h"
#include <iostream>
#include "screens/MenuPrincipal.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8000

int main() {
  MenuPrincipal menu;
  menu.display();

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
  int result = socket.send_message("1\\2\\yoquese");
  if (result <= 0) {
    std::cerr << "Error al enviar el mensaje: " << WSAGetLastError()
              << std::endl;
  } else {
    std::cout << "Mensaje enviado correctamente" << std::endl;
  }

  auto ignore = socket.receive_message();
  socket.close();

  return 0;
}
