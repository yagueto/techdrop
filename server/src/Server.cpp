#include "Server.h"
#include "MessageHandler.h" // Include the new message handler
#include <iostream>

using namespace std;

int server_initialize() {
  WSADATA wsaData;
  if (int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); iResult != 0) {
    cout << "Error al inicializar el servidor: " << WSAGetLastError() << endl;
    return 1;
  }
  cout << "Servidor inicializado" << endl;
  return 0;
}

SOCKET listen_for_connections() {
  SOCKET connection_socket;
  SOCKET client_socket;
  sockaddr_in server{};
  sockaddr_in client{};

  if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    cout << "Error creando el socket : " << WSAGetLastError() << endl; // Corrected: WSAGetLastError is a function
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
  cout << "Aceptado cliente desde " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << endl; // Added : and ntohs for port, and endl
  closesocket(connection_socket); // Close listening socket, keep client socket

  return client_socket;
}

void server_loop(const SOCKET &client_socket) {
  std::string recvbuff;
  do {
    recvbuff.assign(512, '\0');

    int received = recv(client_socket, recvbuff.data(),
                        static_cast<int>(recvbuff.capacity()), 0);
    if (received > 0) {
      recvbuff.resize(received); // Resize to actual data received
      // std::cout << "DEBUG: Received raw data: " << recvbuff << std::endl; // For debugging
    } else if (received == 0) {
      std::cout << "Connection closed by peer." << std::endl;
      break;
    } else {
      std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
      break;
    }

    if (!handle_message_request(recvbuff)) { // Pass recvbuff directly
      std::cout << "Server loop: handle_message_request signaled to close." << std::endl;
      break;
    }
    // sendbuff = "PONG: " + recvbuff;
    // if (send(client_socket, sendbuff.c_str(),
    // static_cast<int>(sendbuff.size()),
    //          0) == SOCKET_ERROR) {
    //   std::cerr << "Error enviando: " << WSAGetLastError() << std::endl;
    //   break;
    // }
  } while (true);
}

