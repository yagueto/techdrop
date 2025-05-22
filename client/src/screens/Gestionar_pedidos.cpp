#include "Gestionar_pedidos.h"
#include <iostream>
using namespace std;

void Gestionar_pedidos::gestionarOpcion(int opcion) {
    switch (opcion) {
    case 1:
        cout << "Hace pedido"<<endl;
        break;
    case 2:
        cout << "Borra pedido"<<endl;
        break;
    case 3:
        cout << "Muestra historial de pedidos"<<endl;
        break;
    default:
        cout << "Opción no valida"<<endl;
    }
}