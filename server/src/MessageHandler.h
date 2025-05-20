#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>

/**
 * @brief Handles a message received from the client.
 * @param message The raw message string received.
 * @return True if the server should continue processing messages, false if the connection should be closed (e.g., on a CLOSE command).
 */
bool handle_message_request(const std::string &message);

#endif // MESSAGE_HANDLER_H

