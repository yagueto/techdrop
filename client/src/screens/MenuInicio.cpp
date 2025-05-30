#include "MenuInicio.h"

#include "Globals.h"
#include "MenuPedidos.h"
#include "MenuUsuario.h"

MenuInicio::MenuInicio(const Socket &server_socket)
    : Menu(server_socket, "INICIO") {
  anadirOpcion("Gestionar pedidos");
  anadirOpcion("Configuracion usuario");
}

void MenuInicio::gestionarOpcion(int opcion) {
  switch (opcion) {
  case 1: {
    MenuPedidos pedidos(server_socket);
    pedidos.display();
    break;
  }
  case 2: {
    MenuUsuario usuario(server_socket);
    usuario.display();
    break;
  }
  default:
    cout << "Opcion no valida." << endl;
  }
}
