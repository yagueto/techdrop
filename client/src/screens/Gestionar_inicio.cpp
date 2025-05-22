//
// Created by naia.martin on 21/05/2025.
//

#include "Gestionar_inicio.h"

#include "Gestionar_pedidos.h"
#include "Gestionar_usuarios.h"

void Gestionar_inicio::gestionarOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        {
            Gestionar_pedidos* gestiona_pedidos = new Gestionar_pedidos();
            Menu pedidosMenu("PEDIDOS", 0, gestiona_pedidos);
            pedidosMenu.anadirOpcion("Hacer pedido");
            pedidosMenu.anadirOpcion("Borrar pedido");
            pedidosMenu.anadirOpcion("Ver todos los pedidos");
            pedidosMenu.display();
            delete gestiona_pedidos;
            break;
        }
    case 2:
        {
            Gestionar_usuarios* gestiona_usuarios = new Gestionar_usuarios();
            Menu configMenu("CONFIGURACION USUARIO", 0, gestiona_usuarios);
            configMenu.anadirOpcion("Cambiar username");
            configMenu.anadirOpcion("Cambiar contraseña");
            configMenu.anadirOpcion("Borrar cuenta");
            configMenu.display();
            delete gestiona_usuarios;
            break;
        }
    case 3:
        return;
    default:
        cout<<"Opcion no valida"<<endl;
    }
}
