#include "Server.h"
#include <iostream>

using namespace std;

SOCKET listen_for_connections() {
  WSADATA wsaData;
  SOCKET connection_socket;
  SOCKET client_socket;
  sockaddr_in server{};
  sockaddr_in client{};

  if (int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); iResult != 0) {
    cout << "Error al inicializar el servidor: " << WSAGetLastError() << endl;
    return INVALID_SOCKET;
  }
  cout << "Servidor inicializado" << endl;

  if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    cout << "Error creando el socket : " << WSAGetLastError << endl;
    WSACleanup();
    return INVALID_SOCKET;
  }
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT);

  if (bind(connection_socket, reinterpret_cast<sockaddr *>(&server),
           sizeof(server)) == SOCKET_ERROR) {
    cout << "Error en bind: " << WSAGetLastError() << endl;
    closesocket(connection_socket);
    WSACleanup();
    return INVALID_SOCKET;
  }

  if (listen(connection_socket, 1) ==
      SOCKET_ERROR) // backlog = 1 para rechazar más de una conexión
  {
    cout << "Error escuchando :  " << WSAGetLastError() << endl;
    closesocket(connection_socket);
    WSACleanup();
    return INVALID_SOCKET;
  }

  cout << "Esperando conexiones..." << endl;

  int client_size = sizeof(client);
  client_socket = accept(connection_socket,
                         reinterpret_cast<sockaddr *>(&client), &client_size);
  if (client_socket == INVALID_SOCKET) {
    cout << "Error al aceptar al cliente : " << WSAGetLastError() << endl;
    closesocket(connection_socket);
    WSACleanup();
    return INVALID_SOCKET;
  }
  printf("Aceptado cliente desde %s:%d\n\n", inet_ntoa(client.sin_addr),
         client.sin_port);
  closesocket(connection_socket); // TODO: si se hace un bucle esto no tiene que
                                  // estar aquí

  return client_socket;
}

void server_loop(const SOCKET &client_socket) {
  std::string sendbuff, recvbuff;
  do {
    sendbuff.resize(512);
    recvbuff.resize(512);

    int received = recv(client_socket, recvbuff.data(),
                        static_cast<int>(recvbuff.size()), 0);
    if (received > 0) {
      recvbuff.resize(received);
    } else if (received == 0) {
      std::cout << "Connection closed" << std::endl;
      break;
    } else {
      std::cout << "Error: " << WSAGetLastError() << std::endl;
      break;
    }

    handle_message(recvbuff);

    // sendbuff = "PONG: " + recvbuff;
    // if (send(client_socket, sendbuff.c_str(),
    // static_cast<int>(sendbuff.size()),
    //          0) == SOCKET_ERROR) {
    //   std::cerr << "Error enviando: " << WSAGetLastError() << std::endl;
    //   break;
    // }
  } while (true);
}

void handle_message(const std::string &message) {
  size_t first_break = message.find_first_of('\\');
  if (first_break == std::string::npos ||
      first_break ==
          0) { // break character not found; invalid message; disregard
    return;
  }

  int type_value;
  try {
    type_value = std::stoi(message.substr(0, first_break));
  } catch (const std::exception &) {
    return;
  }
  switch (type_value) {
  case (LOGIN):
    cout << "Login received" << endl;
    break;
  case (REGISTER):
    cout << "Register received" << endl;
    break;
  default: // type not implemented
    cout << "Recibido: " << message << endl;
  }
}
