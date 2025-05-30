#include "MessageHandler.h"

#include "Logger.h"
#include "Protocol.h"
#include "db/UserDAO.h"
#include "domain/Usuario.h"

#include <iostream>
#include <string>

#include "db/PedidoDAO.h"
#include "db/PlatoDAO.h"

Message handle_message_request(const std::string &message) {
    Logger::get_logger().write(std::string() + "RECIBIDO: " + message);
    if (const size_t first_break = message.find_first_of(MESSAGE_DELIMITER);
        first_break == std::string::npos || first_break == 0) {
        std::cerr << "Warning: Invalid message format. Delimiter missing or at "
                "start. Message: \""
                << message << "\"." << std::endl;
        return {
            INVALID_TYPE,
            INVALID_STATUS
        }; // Continue server loop, message is ignored
    }

    const Message received(Message::deserialize(message));
    Message response(INVALID_TYPE, INVALID_STATUS);

  switch (received.get_type()) {
  case LOGIN: {
    std::cout << "MessageHandler: Login received." << std::endl;
    response = Message(LOGIN, RESPONSE);
    const bool exists = UserDAO::user_exists(received.get_params().at(0),
                                             received.get_params().at(1));
    if (exists) {
      response.add_param("200"); // login correcto
      response.add_param(
          UserDAO::select_username(received.get_params().at(0)).getDni());
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

  case UPDATE_USERNAME: {
    response = Message(UPDATE_USERNAME, RESPONSE);
    const std::string dni = received.get_params().at(0);
    Usuario u(dni, "", "");
    UserDAO::select(u);
    u.setNombre(received.get_params().at(1));
    UserDAO::update(u);
    response.add_param("200");
    std::cout << "Update hecho exitosamente.";
    break;
  }

  case UPDATE_PASSWORD: {
    response = Message(UPDATE_PASSWORD, RESPONSE);
    const std::string dni = received.get_params().at(0);
    const std::string password_nueva = received.get_params().at(1);

    Usuario u(dni, "", "");
    UserDAO::select(u);
    u.setContraseña(password_nueva);
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
        case PEDIDO_MENU: {
            std::cout << "MessageHandler: Pedido menu request received." << std::endl;
            for (const Plato &plato: PlatoDAO::getPlatos()) {
                plato.serializar(response);
            }
            response = Message(PEDIDO_MENU, RESPONSE);
            response.add_param("200");
        }
        break;
        case PEDIDO_CREATE: {
            std::cout << "MessageHandler: Pedido create request received." << std::endl;
            response = Message(PEDIDO_CREATE, RESPONSE);
            Pedido pedido = Pedido::deserializar(received);
            PedidoDAO::insert(pedido);
            response.add_param("200");
        }
        break;
        case PEDIDO_STATE: {
            std::cout << "MessageHandler: Pedido state request received." << std::endl;
            response = Message(PEDIDO_STATE, RESPONSE);
            Pedido pedido = Pedido::deserializar(received);
            Pedido *pedido_db = PedidoDAO::select(pedido);
            if (pedido_db) {
                response.add_param(std::to_string(pedido_db->getEstado()));
                response.add_param("200"); // Pedido encontrado
            } else {
                response.add_param("404"); // Pedido no encontrado
            }
        }
        break;
        case PEDIDO_LIST: {
            std::cout << "MessageHandler: Pedido list request received." << std::endl;
            response = Message(PEDIDO_LIST, RESPONSE);
            Usuario usuario = Usuario::Deserializar(received);
            for (const Pedido &pedido: PedidoDAO::historial(usuario)) {
                //TODO: borrar esto
                cout << pedido.getIdPedido() << endl;
                pedido.serializar(response);
            }
            response.add_param("200");
        }
        break;
        case PEDIDO_CANCEL: {
            std::cout << "MessageHandler: Pedido cancel request received." << std::endl;
            response = Message(PEDIDO_CANCEL, RESPONSE);
            Pedido pedido = Pedido::deserializar(received);
            PedidoDAO::del(pedido);
            response.add_param("200");
        }
        break;

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
