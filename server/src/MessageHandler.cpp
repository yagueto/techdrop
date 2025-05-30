#include "MessageHandler.h"

#include "Logger.h"
#include "Protocol.h"
#include "db/UserDAO.h"
#include "domain/Usuario.h"

#include <iostream>
#include <string>

Message handle_message_request(const std::string &message)
{
  Logger::get_logger().write(std::string() + "RECIBIDO: " + message);
  if (const size_t first_break = message.find_first_of(MESSAGE_DELIMITER);
      first_break == std::string::npos || first_break == 0) {
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
    {
      std::cout << "MessageHandler: Login received." << std::endl;
      response = Message(LOGIN, RESPONSE);
      const bool exists = UserDAO::user_exists(received.get_params().at(0),
                                               received.get_params().at(1));
      if (exists) {
        response.add_param("200"); // login correcto
      } else {
        response.add_param("401"); // unauthorised (usuario no existe)
      }
  } break;
  case REGISTER: {
    std::cout << "MessageHandler: Register received." << std::endl;
    response = Message(REGISTER, RESPONSE);

    if (Usuario usuario(received.get_params().at(0), "", "");
        UserDAO::select(usuario)) {
      response.add_param("401"); // user already exists
      response.add_param("El usuario ya existe");
      break;
    }
    Usuario usuario(received.get_params().at(0), received.get_params().at(1),
                    received.get_params().at(2));
    UserDAO::insert(usuario);
    response.add_param("200");
  } break;
  case CLOSE:
    std::cout << "MessageHandler: Close connection request received."
              << std::endl;
    break;

  case UPDATE_USERNAME:
    {
      response = Message(UPDATE_USERNAME, RESPONSE);
      const std::string dni = received.get_params().at(0);
      const std::string username_nuevo = received.get_params().at(1);
      Usuario u(dni, username_nuevo, "");
      UserDAO::update(u);
      response.add_param("200");
      break;
    }

  case UPDATE_PASSWORD:
    {
      response = Message(UPDATE_PASSWORD, RESPONSE);
      const std::string dni = received.get_params().at(0);
      const std::string password_nueva = received.get_params().at(1);

      Usuario u(dni, "", password_nueva);
      UserDAO::update(u);
      response.add_param("200");
      break;
    }
      case DELETE_USER: {
          response = Message(DELETE_USER, RESPONSE);
          const std::string dni = received.get_params().at(0);
          Usuario u(dni, "", "");
          UserDAO::del(u);
          response.add_param("200");
          break;
      }

      default:
        std::cout << "MessageHandler: Unknown message type (" << received.get_type()
                  << ") received." << std::endl;
      // std::cout << "Full message: " << message << std::endl;
      break;
  }
    Logger::get_logger().write(std::string() +
                               "RESPUESTA: " + response.serialize());
    return response; // Continue server loop, message is ignored
  }

