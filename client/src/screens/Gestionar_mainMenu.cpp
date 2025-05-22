//
// Created by naia.martin on 21/05/2025.
//

#include "Gestionar_mainMenu.h"
#include "Menu.h"
#include "Gestionar_logIn.h"
#include "Gestionar_registro.h"
#include <iostream>
using namespace std;

void Gestionar_mainMenu::gestionarOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        {
            Gestionar_logIn* gestiona_logIn = new Gestionar_logIn();
            gestiona_logIn->gestionarOpcion(1);
            delete gestiona_logIn;
            break;
        }
    case 2:
        {
            Gestionar_registro* gestiona_registro = new Gestionar_registro();
            gestiona_registro->gestionarOpcion(1);
            delete gestiona_registro;
            break;
        }
    case 3:
        cout << "Saliendo del programa..."<<endl;
        exit(0);
    default:
        cout<<"Opcion no valida."<<endl;
    }
}
