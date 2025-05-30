#include "MenuUsuario.h"

MenuUsuario::MenuUsuario(const Socket &socket)
    : Menu(socket, "CONFIGURACION USUARIO") {
    anadirOpcion("Cambiar username");
    anadirOpcion("Cambiar contraseña");
    anadirOpcion("Borrar cuenta");
}

void MenuUsuario::gestionarOpcion(const int opcion)
{
    switch (opcion)
    {
    case 1:
        cout << "Cambiar username" << endl;
        break;
    case 2:
        cout << "Cambiar contraseña" << endl;
        break;
    case 3:
        cout << "Borrar cuenta" << endl;
        break;
    default:
        cout << "Opcion no valida." << endl;
    }
}

