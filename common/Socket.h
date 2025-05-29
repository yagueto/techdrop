#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <winsock2.h>

class Socket {
  SOCKET conn_socket;
  SOCKET listen_socket;

public:
  enum MODE { SERVER, CLIENT };
  Socket();
  virtual ~Socket();

  static void setup_address(const std::string &ipAddress, int port,
                            sockaddr_in &addr);
  bool create(MODE mode);
  bool bind_socket();
  [[nodiscard]] bool listen_on_socket() const;
  bool accept_connection(sockaddr_in &clientAddr);
  [[nodiscard]] bool connect_to_server(const std::string &ipAddress,
                                       int port) const;
  static bool initializeWinSock();
  void close();
  [[nodiscard]] bool is_valid() const;
  static void cleanupWinSock();
  [[nodiscard]] SOCKET get_raw_socket() const;
  int send_message(const std::string &message) const;

  struct MessageResult {
    enum Status { SUCESS, CONNECTION_CLOSED, RECV_ERROR };
    Status status;
    std::string message;
    int error_code;
  };
  [[nodiscard]] MessageResult receive_message() const;
};

#endif // SOCKET_H
