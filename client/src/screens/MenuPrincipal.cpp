#include "MenuPrincipal.h"

#include "Globals.h"
#include "MenuInicio.h"
#include "domain/Message.h"
#include "domain/Usuario.h"
#include "domain/utils.h"

MenuPrincipal::MenuPrincipal(const Socket &socket)
    : Menu(socket, "BIENVENIDO", true) {
  anadirOpcion("Log in");
  anadirOpcion("Registrar cuenta");
}

void MenuPrincipal::gestionarOpcion(const int opcion) {
  switch (opcion) {
  case 1: {
    //     server_socket.send_message("ole");
    //     prueba enviar socket

    string username, password;
    clrscr();
    cout << "Username: ";
    cin >> username;
    clearInputBuffer();
    cout << "Password: ";
    cin >> password;
    clearInputBuffer();

    Message login_message(LOGIN, REQUEST);
    login_message.add_param(username);
    login_message.add_param(password);
    if (server_socket.send_message(login_message.serialize()) < 0) {
      break;
    }
    auto [status, message, error_code] = server_socket.receive_message();
    if (status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code
           << " - " << status;
    }

    if (const Message result_message = Message::deserialize(message);
        result_message.get_params().front() == "200") {
      cout << "Login exitoso." << endl;
      Globals::usuario_actual.setNombre(username);
      Globals::usuario_actual.setContraseña(password);
      clrscr();
      waitForEnter();
      MenuInicio inicio(server_socket);
      inicio.display();
    } else {
      cout << "Usuario o contraseña incorrectos" << endl;
    }
  } break;
  case 2: {
    clrscr();

    string dni, username, password;
    cout << "DNI: ";
    cin >> dni;
    clearInputBuffer();
    cout << "Username: ";
    cin >> username;
    clearInputBuffer();
    cout << "Password: ";
    cin >> password;
    clearInputBuffer();

    Usuario usuario(dni, username, password);
    Message register_request(REGISTER, REQUEST);
    usuario.serializar(register_request);

    if (server_socket.send_message(register_request.serialize()) < 0) {
      break;
    }

    auto [status, message, error_code] = server_socket.receive_message();
    if (status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code
           << " - " << status;
    }

    if (Message result_message = Message::deserialize(message);
        result_message.get_params().front() == "200") {
      cout << "Usuario registrado" << endl;
    } else {
      cout << "No se ha podido registrar: " << result_message.get_params().at(1)
           << endl;
    }
  } break;
  default:
    cout << "Opcion no valida." << endl;
    break;
  }
}
