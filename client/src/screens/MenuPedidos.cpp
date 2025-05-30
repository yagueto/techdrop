#include "MenuPedidos.h"

#include "domain/utils.h"

MenuPedidos::MenuPedidos(const Socket &socket) : Menu(socket, "PEDIDOS") {
    anadirOpcion("Hacer pedido");
    anadirOpcion("Borrar pedido");
    anadirOpcion("Ver todos los pedidos");
}

void MenuPedidos::gestionarOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        cout <<"Hace pedido" << endl;
        break;
    case 2:
        cout <<"Borra pedido" << endl;
        break;
    case 3:
        cout <<"Muestra historial de pedidos" << endl;
        break;
    default:
        cout <<"Opcion no valida." << endl;
    }
}
