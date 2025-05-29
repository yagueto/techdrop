#include "MenuInicio.h"
#include "MenuPedidos.h"
#include "MenuUsuario.h"

MenuInicio::MenuInicio() : Menu("INICIO")
{
    anadirOpcion("Gestionar pedidos");
    anadirOpcion("Configuracion usuario");
}

void MenuInicio::gestionarOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        {
            MenuPedidos pedidos;
            pedidos.display();
            break;
        }
    case 2:
        {
            MenuUsuario usuario;
            usuario.display();
            break;
        }
    default:
        cout << "Opcion no valida." <<endl;
    }
}
