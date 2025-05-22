#ifndef MESSAGE_H
#define MESSAGE_H
#include "Protocol.h"
#include <string>
#include <vector>

class Message {
  MESSAGE_TYPE message_type;
  MESSAGE_STATUS message_status;
  std::vector<std::string> params;

public:
  Message(MESSAGE_TYPE message_type, MESSAGE_STATUS message_status);
  void add_param(const std::string &param);
  [[nodiscard]] std::string serialize() const;
  static Message deserialize(const std::string &message);
  [[nodiscard]] std::vector<std::string> get_params() const;
  ~Message();
};

#endif // MESSAGE_H
