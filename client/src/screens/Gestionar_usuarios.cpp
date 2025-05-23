#include "Gestionar_usuarios.h"
#include <iostream>
using namespace std;

void Gestionar_usuarios::gestionarOpcion(int opcion) {
    switch (opcion) {
    case 1:
        cout << "Cambiar username"<<endl;
        break;
    case 2:
        cout << "Cambiar contraseña"<<endl;
        break;
    case 3:
        cout << "Borrar cuenta"<<endl;
        break;
    default:
        cout << "Opcion no valida."<<endl;
    }
}