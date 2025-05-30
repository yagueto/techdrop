#include "Logger.h"
#include "MessageHandler.h"
#include "Socket.h"
#include "Config.h"
#include <iostream>
#include <domain/Usuario.h>

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

    Logger::get_logger().write(
        std::string() + "ACCEPTED CLIENT: " + inet_ntoa(sockaddr_in.sin_addr));

    while (true) {
      Socket::MessageResult result = socket.receive_message();
      if (result.status == Socket::MessageResult::CONNECTION_CLOSED ||
          result.status == Socket::MessageResult::RECV_ERROR) {
        break;
      }
      Message response = handle_message_request(result.message);

      if (response.get_type() == INVALID_TYPE ||
          response.get_status() == INVALID_STATUS) {
        continue; // ignore the message
      }
      if (response.get_type() == CLOSE) {
        break; // close connection
      }

      socket.send_message(response.serialize());
    }
    closesocket(socket.get_raw_socket());
    // break;
  }
  socket.close();
  Logger::get_logger().close();
  return 0;
}
