#include "Message.h"

#include <iostream>

Message::Message(const MESSAGE_TYPE message_type,
                 const MESSAGE_STATUS message_status)
    : message_type(message_type), message_status(message_status) {}

void Message::add_param(const std::string &param) {
  this->params.push_back(param);
}

std::string Message::serialize() const {
  std::string serialized_str;
  serialized_str += std::to_string(this->message_type);
  serialized_str += MESSAGE_DELIMITER;
  serialized_str += std::to_string(this->message_status);

  for (const auto &param : this->params) {
    serialized_str += MESSAGE_DELIMITER;
    serialized_str += param;
  }
  serialized_str +=
      MESSAGE_DELIMITER; // must end with the delimiter so it recognises the end
  return serialized_str;
}

Message Message::deserialize(const std::string &message) {
  MESSAGE_TYPE type = INVALID_TYPE;
  MESSAGE_STATUS status = INVALID_STATUS;
  std::vector<std::string> parsed_params;

  if (message.empty()) {
    return {type, status}; // Return invalid message if input is empty
  }

  int i = 0, last_value = 0, value_number = 0;
  while ((i = message.find(MESSAGE_DELIMITER, i + 1)) != std::string::npos) {
    std::string param = message.substr(last_value, i - last_value);
    if (value_number == 0) {
      type = static_cast<MESSAGE_TYPE>(std::stoi(param));
    } else if (value_number == 1) {
      status = static_cast<MESSAGE_STATUS>(std::stoi(param));
    } else {
      parsed_params.push_back(param);
    }
    value_number++;
    last_value = i + 1;
  }

  Message m(type, status);
  for (const std::string &param : parsed_params) {
    m.add_param(param);
  }

  return m;
}

std::vector<std::string> Message::get_params() const { return this->params; }

MESSAGE_STATUS Message::get_status() const { return this->message_status; }
MESSAGE_TYPE Message::get_type() const { return this->message_type; }

Message::~Message() = default;
