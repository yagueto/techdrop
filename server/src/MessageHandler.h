#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <winsock2.h> // For SOCKET type, if needed by other parts of the handler

// Forward declare if Protocol.h enums are used and to avoid circular dependencies if complex
// enum MessageType;

/**
 * @brief Handles a message received from the client.
 * @param message The raw message string received.
 * @return True if the server should continue processing messages, false if the connection should be closed (e.g., on a CLOSE command).
 */
bool handle_message_request(const std::string &message);

#endif // MESSAGE_HANDLER_H

