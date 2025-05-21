#include "MessageHandler.h"
#include "Socket.h"
#include <iostream>

void handle_socket_exception() {
  std::cerr << "¡Error inicializando el servidor!" << std::endl;
}

int main() {
  if (!Socket::initializeWinSock()) {
    handle_socket_exception();
    return 1;
  }

  Socket socket;
  socket.create(Socket::SERVER);
  if (!socket.bind_socket()) {
    handle_socket_exception();
    return 1;
  }

  std::cout << "Inicializado correctamente" << std::endl;
  while (true) {
    if (!socket.listen_on_socket()) {
      handle_socket_exception();
      return 1;
    }
    std::cout << "Esperando conexiones..." << std::endl;

    sockaddr_in sockaddr_in{};
    socket.accept_connection(sockaddr_in);

    std::cout << "Aceptado cliente desde " << inet_ntoa(sockaddr_in.sin_addr)
              << ":" << ntohs(sockaddr_in.sin_port) << std::endl;
    while (true) {
      std::string recvbuff;
      recvbuff.assign(512, '\0');

      int received = recv(socket.get_raw_socket(), recvbuff.data(),
                          static_cast<int>(recvbuff.capacity()), 0);
      if (received > 0) {
        recvbuff.resize(received);
        std::cout << "DEBUG: Received raw data: " << recvbuff << std::endl;
        handle_message_request(recvbuff);
      } else if (received == 0) {
        std::cout << "Connection closed by peer." << std::endl;
        break;
      } else {
        std::cout << "recv failed with error: " << WSAGetLastError()
                  << std::endl;
        break;
      }
    }
    closesocket(socket.get_raw_socket());
    //break;
  }
  socket.close();
  return 0;
}
