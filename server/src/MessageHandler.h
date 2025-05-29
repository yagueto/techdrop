#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "domain/Message.h"
#include <string>

/**
 * @brief Handles a message received from the client.
 * @param message The raw message string received.
 * @return Message with the data received
 */
Message handle_message_request(const std::string &message);

#endif // MESSAGE_HANDLER_H
