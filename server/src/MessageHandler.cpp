#include "MessageHandler.h"
#include "Protocol.h"

#include <iostream>
#include <string>

Message handle_message_request(const std::string &message) {
  const size_t first_break = message.find_first_of(MESSAGE_DELIMITER);
  if (first_break == std::string::npos || first_break == 0) {
    std::cerr << "Warning: Invalid message format. Delimiter missing or at "
                 "start. Message: \""
              << message << "\"." << std::endl;
    return {INVALID_TYPE,
            INVALID_STATUS}; // Continue server loop, message is ignored
  }

  const Message received(Message::deserialize(message));
  Message response(INVALID_TYPE, INVALID_STATUS);

  switch (received.get_type()) {
  case LOGIN:
    std::cout << "MessageHandler: Login received." << std::endl;
    response = Message(LOGIN, RESPONSE);
    response.add_param("200");
    return response;
  case REGISTER:
    std::cout << "MessageHandler: Register received." << std::endl;
    response = Message(REGISTER, RESPONSE);
    response.add_param("200");
    return response;
  case CLOSE:
    std::cout << "MessageHandler: Close connection request received."
              << std::endl;
    break;
  default:
    std::cout << "MessageHandler: Unknown message type (" << received.get_type()
              << ") received." << std::endl;
    // std::cout << "Full message: " << message << std::endl;
    break;
  }
  return {INVALID_TYPE,
          INVALID_STATUS}; // Continue server loop, message is ignored
}
