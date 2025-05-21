#include "Socket.h"
#include <iostream>

using namespace std;

Socket::Socket() {
  this->listen_socket = INVALID_SOCKET;
  this->conn_socket = INVALID_SOCKET;
};

Socket::~Socket() {
  this->close();
}

bool Socket::create(const MODE mode) {
  SOCKET s;
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    cout << "Error creando el socket : " << WSAGetLastError() << endl;
    WSACleanup();
    return false;
  }

  if (mode == SERVER) {
    this->listen_socket = s;
  } else {
    this->conn_socket = s;
  }
  return true;
}

void Socket::setup_address(const std::string &ipAddress, int port,
                             sockaddr_in &addr) {
  addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
}

bool Socket::bind_socket() {
  sockaddr_in server{};

  setup_address("0.0.0.0", 8000, server);
  if (bind(listen_socket, reinterpret_cast<sockaddr *>(&server),
           sizeof(server)) == SOCKET_ERROR) {
    cout << "Error en bind: " << WSAGetLastError() << endl;
    this->close();
    return false;
  }
  return true;
}

bool Socket::listen_on_socket() const {
  if (listen(listen_socket, 1) ==
      SOCKET_ERROR) // backlog = 1 para rechazar más de una conexión
  {
    cout << "Error escuchando :  " << WSAGetLastError() << endl;
    closesocket(conn_socket);
    WSACleanup();
    return false;
  }
  return true;
}

bool Socket::accept_connection(sockaddr_in &clientAddr) {
  int client_size = sizeof(clientAddr);
  this->conn_socket = accept(
      listen_socket, reinterpret_cast<sockaddr *>(&clientAddr), &client_size);
  if (conn_socket == INVALID_SOCKET) {
    cout << "Error al aceptar al cliente : " << WSAGetLastError() << endl;
    closesocket(listen_socket);
    WSACleanup();
    return false;
  }
  return true;
}

bool Socket::connect_to_server(const std::string &ipAddress,
                                 const int port) const {
  sockaddr_in serverAddr{};

  setup_address(ipAddress, port, serverAddr);
  if (connect(conn_socket, reinterpret_cast<sockaddr *>(&serverAddr),
              sizeof(serverAddr)) == SOCKET_ERROR) {
    printf("Connection error: %d", WSAGetLastError());
    closesocket(conn_socket);
    WSACleanup();
    return false;
  }
  return true;
}

bool Socket::initializeWinSock() {
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    cout << "Failed. Error Code : " << WSAGetLastError();
    return false;
  }
  return true;
}

// Cleanup all connections
void Socket::close() {
  if (this->is_valid()) {
    closesocket(this->conn_socket);
    this->conn_socket = INVALID_SOCKET;
  }
  if (this->listen_socket != INVALID_SOCKET) {
    closesocket(this->listen_socket);
    this->listen_socket = INVALID_SOCKET;
  }
  cleanupWinSock();
}

// Returns false if connection socket is invalid
bool Socket::is_valid() const { return this->conn_socket != INVALID_SOCKET; }

void Socket::cleanupWinSock() { WSACleanup(); }

SOCKET Socket::get_raw_socket() const { return this->conn_socket; }

int Socket::send_message(const std::string &message) const {
  return send(this->conn_socket, message.c_str(),
              static_cast<int>(message.size()), 0);
}
