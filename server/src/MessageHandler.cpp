#include "MessageHandler.h"
#include "Protocol.h"
#include <iostream>
#include <stdexcept>
#include <string>

bool handle_message_request(const std::string &message) {
  const size_t first_break = message.find_first_of(MESSAGE_DELIMITER);
  if (first_break == std::string::npos || first_break == 0) {
    std::cerr << "Warning: Invalid message format. Delimiter missing or at "
                 "start. Message: \""
              << message << "\"." << std::endl;
    return true; // Continue server loop, message is ignored
  }

  int type_value;
  std::string type_str = message.substr(0, first_break); // get message type
  try {
    type_value = std::stoi(type_str);
  } catch (const std::invalid_argument &ia) {
    std::cerr << "Warning: Invalid message type. Not a number: '" << type_str
              << "'. " << ia.what() << std::endl;
    return true; // Continue server loop, message is ignored
  } catch (const std::out_of_range &oor) {
    std::cerr << "Warning: Invalid message type. Number out of range: '"
              << type_str << "'. " << oor.what() << std::endl;
    return true; // Continue server loop, message is ignored
  }

  switch (static_cast<MESSAGE_TYPE>(type_value)) {
  case LOGIN:
    std::cout << "MessageHandler: Login received." << std::endl;
    break;
  case REGISTER:
    std::cout << "MessageHandler: Register received." << std::endl;
    break;
  case CLOSE:
    std::cout << "MessageHandler: Close connection request received."
              << std::endl;
    return false; // Signal server_loop to close connection
  default:
    std::cout << "MessageHandler: Unknown message type (" << type_value
              << ") received." << std::endl;
    // std::cout << "Full message: " << message << std::endl;
    break;
  }
  return true; // Continue server loop
}
