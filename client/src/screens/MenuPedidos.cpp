#include "MenuPedidos.h"

#include <domain/Pedido.h>
#include <domain/Plato.h>
#include <map>

#include "Globals.h"
#include "domain/utils.h"

#include <ctime>

// Helper function to format time_t
std::string format_time_for_display(time_t raw_time) {
  std::tm *ptm = std::localtime(&raw_time);
  if (ptm == nullptr) {
    return "Invalid time";
  }
  char buffer[32];
  // Format: YYYY-MM-DD HH:MM:SS
  std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
  return buffer;
}

// Helper function to convert estado to string (optional)
std::string estado_to_string(int estado) {
  switch (estado) {
  case 0:
    return "En cola";
  case 1:
    return "En camino";
  case 2:
    return "Entregado";
  default:
    return "Desconocido";
  }
}

MenuPedidos::MenuPedidos(const Socket &socket) : Menu(socket, "PEDIDOS") {
  anadirOpcion("Hacer pedido");
  anadirOpcion("Borrar pedido");
  anadirOpcion("Ver todos los pedidos"); // pasar Usuario
}

void MenuPedidos::gestionarOpcion(int opcion) {
  int id = Globals::usuario_actual.getId();

  switch (opcion) {
  case 1: {
    clrscr();

    cout << "ATENCIÓN: las siguientes incidencias pueden retrasar su pedido:"
         << endl;
    for (StatusEntry statu : Globals::status) {
      cout << "- " << statu.titulo << endl;
    }

    cout << endl << "¿Deseas continuar aún así? (S/n)";
    std::string response;
    cin >> response;
    if (response == "n") {
      return;
    }

    Message pedidos_message(PEDIDO_MENU, REQUEST);
    if (server_socket.send_message(pedidos_message.serialize()) < 0) {
      break;
    }
    auto [status, message, error_code] = server_socket.receive_message();
    if (status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code
           << " - " << status;
      return;
    }
    const Message result_message = Message::deserialize(message);
    auto params = result_message.get_params();
    if (result_message.get_params().front() != "200") {
      cout << "No hay platos disponibles." << endl;
      waitForEnter();
      return;
    }
    vector<Plato> platos;
    for (size_t i = 1; i + 4 < params.size(); i += 5) {
      Message m(PEDIDO_MENU, RESPONSE);
      for (int j = 0; j < 5; j++) {
        m.add_param(params[i + j]);
      }
      platos.push_back(Plato::Deserializar(m));
    }

    cout << "Platos disponibles: \n";
    for (const auto &plato : platos) {
      cout << plato.getId() << ":" << plato.getNombre() << "," << "-"
           << plato.getPrecio() << "€\n";
    }
    map<int, int> platosSeleccionados;

    cout << "Ingrese el IDs de los platos que quieras pedir (0 para "
            "terminar)\n: "
         << endl;
    while (true) {
      int Id, cant;
      cout << "ID plato: ";
      cin >> Id;
      clearInputBuffer();

      if (Id == 0)
        break;

      cout << "\nCantidad: ";
      cin >> cant;

      auto it = find_if(platos.begin(), platos.end(), [Id](const Plato &plato) {
        return plato.getId() == Id;
      });
      if (it != platos.end()) {
        auto t = platosSeleccionados.find(Id);
        if (t != platosSeleccionados.end()) {
          t->second += cant;
        } else {
          platosSeleccionados.insert({Id, cant});
          cout << "Añadido: " << it->getNombre() << "," << cant << endl;
        }
      } else {
        cout << "ID no valido" << endl;
      }
    }
    if (platosSeleccionados.empty()) {
      cout << "No se han seleccionado platos" << endl;
      waitForEnter();
      break;
    }

    string direccion;
    cout << "Introduce direccion de entrega: ";
    cin >> direccion;

    time_t fecha = time(nullptr);
    int estado = 0; // default en cola ponemos
    Message pedido_create(PEDIDO_CREATE, REQUEST);
    Pedido p(0, id, direccion, fecha, estado, platosSeleccionados);
    p.serializar(pedido_create);
    if (server_socket.send_message(pedido_create.serialize()) < 0) {
      cout << "Error al enviar pedido" << endl;
      waitForEnter();
      break;
    }
    auto [status_pedido, message_pedido, error_code_pedido] =
        server_socket.receive_message();
    if (status_pedido != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code_pedido
           << " - " << status_pedido;
    }
    const Message pedido_respuesta = Message::deserialize(message_pedido);
    if (pedido_respuesta.get_params().front() == "200") {
      cout << "Pedido creado exitosamente" << endl;
    } else {
      cout << "Error en la creacion del pedido" << endl;
    }
    waitForEnter();

  } break;
  case 2: {
    clrscr();
    Message pedidos_req(PEDIDO_LIST, REQUEST);
    Globals::usuario_actual.serializar(pedidos_req);

    if (server_socket.send_message(pedidos_req.serialize()) < 0) {
      cout << "Error al solicitar pedidos." << endl;
      waitForEnter();
      break;
    }
    auto [status, message, error_code] = server_socket.receive_message();
    if (status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code
           << " - " << status;
      waitForEnter();
      break;
    }
    const Message pedidos_respuesta = Message::deserialize(message);
    auto parametros = pedidos_respuesta.get_params();
    if (pedidos_respuesta.get_params().front() != "200" ||
        pedidos_respuesta.get_params().empty()) {
      cout << "No tienes pedidos" << endl;
      waitForEnter();
      break;
    }
    vector<Pedido> pedidos;
    for (size_t i = 1; i + 4 < parametros.size(); i += 5) {
      Message mes(PEDIDO_LIST, RESPONSE);
      for (int j = 0; j < 5; j++) {
        mes.add_param(parametros[i + j]);
      }
      pedidos.push_back(Pedido::deserializar(mes));
    }
    cout << "Tus pedidos:\n ";
    for (const auto &pedido : pedidos) {
      cout << "ID: " << pedido.getIdPedido() << endl
           << "- Fecha: " << format_time_for_display(pedido.getFecha()) << endl
           << "- Estado: " << estado_to_string(pedido.getEstado()) << endl
           << "- Direccion: " << pedido.getDireccion() << "\n\n";
    }
    int iD;
    cout << "Introduce el id del pedido a borrar(0 para cancelar): ";
    cin >> iD;
    clearInputBuffer();
    if (iD == 0)
      break;
    bool valido = false;
    for (const auto &ped : pedidos) {
      if (ped.getIdPedido() == iD) {
        valido = true;
        break;
      }
    }
    if (!valido) {
      cout << "ID no valido" << endl;
      waitForEnter();
      break;
    }
    Message borrar_request(PEDIDO_CANCEL, REQUEST);
    borrar_request.add_param(to_string(iD));
    if (server_socket.send_message(borrar_request.serialize()) < 0) {
      cout << "Error al enviar solicitud de borrado" << endl;
      waitForEnter();
      break;
    }

    auto [borrar_status, borrar_mssg, borrar_error_code] =
        server_socket.receive_message();
    if (borrar_status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << borrar_error_code
           << " - " << borrar_status;
      waitForEnter();
      break;
    }
    const Message borrar_respuesta = Message::deserialize(borrar_mssg);
    if (borrar_respuesta.get_params().front() == "200") {
      cout << "Pedido borrado exitosamente" << endl;
    } else {
      cout << "Error borrando pedido" << endl;
    }
    waitForEnter();
  } break;
  case 3: {
    clrscr();
    Message pedidos_req(PEDIDO_LIST, REQUEST);
    Globals::usuario_actual.serializar(pedidos_req);

    if (server_socket.send_message(pedidos_req.serialize()) < 0) {
      cout << "Error al solicitar pedidos." << endl;
      waitForEnter();
      break;
    }
    auto [status, message, error_code] = server_socket.receive_message();
    if (status != Socket::MessageResult::SUCESS) {
      cout << "Error en la comunicación con el servidor: " << error_code
           << " - " << status;
      waitForEnter();
      break;
    }
    const Message pedidos_respuesta = Message::deserialize(message);
    auto parametros = pedidos_respuesta.get_params();
    if (pedidos_respuesta.get_params().front() != "200" ||
        pedidos_respuesta.get_params().empty()) {
      cout << "No tienes pedidos" << endl;
      waitForEnter();
      break;
    }
    vector<Pedido> pedidos;
    for (size_t i = 1; i + 4 < parametros.size(); i += 5) {
      Message mes(PEDIDO_LIST, RESPONSE);
      for (int j = 0; j < 5; j++) {
        mes.add_param(parametros[i + j]);
      }
      pedidos.push_back(Pedido::deserializar(mes));
    }
    cout << "Tus pedidos:\n ";
    for (const auto &pedido : pedidos) {
      cout << "ID: " << pedido.getIdPedido() << endl
           << "- Fecha: " << format_time_for_display(pedido.getFecha()) << endl
           << "- Estado: " << estado_to_string(pedido.getEstado()) << endl
           << "- Direccion: " << pedido.getDireccion() << "\n\n";
    }
  } break;
  default:
    cout << "Opcion no valida." << endl;
  }
}
