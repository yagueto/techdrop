//
// Created by naia.martin on 21/05/2025.
//

#include "Menu.h"
#include "Handler.h"
#include <iostream>
#include "screens/Gestionar_mainMenu.h"
#include "../../local_admin/src/utils.h" //para importar el clrsrc(). No se si deberia comunicar local admin con cliente asi
#include "screens/Gestionar_mainMenu.h"
using namespace std;

Menu::Menu(string titulo, int numOpciones, Handler* handler)
{
    this->titulo = titulo;
    this->numOpciones = numOpciones;
    this->handler = handler;
}
Menu::Menu()
{
    this->titulo = "";
    this->numOpciones = 0;
    this->handler = nullptr;
}
Menu::~Menu()
{

}

string Menu::getTitulo()
{
    return this->titulo;
}
int Menu::getNumOpciones()
{
    return this->numOpciones;
}
void Menu::setNumOpciones(int numero)
{
    this->numOpciones = numero;
}
Handler* Menu::getHandler()
{
    return this->handler;
}

void Menu::anadirOpcion(const string& string)
{
    if (numOpciones<OPCIONES_MAX)
    {
        opciones[numOpciones++] = string;
    }else
    {
        cout<<"No se pueden añadir mas opciones.";
    }
}
void Menu::display()
{
    int opcion = -1;
    do
    {
        clrscr();
        cout << " _            _         _                 \n"
             << "| |_ ___  ___| |__   __| |_ __ ___  _ __  \n"
             << "| __/ _ \\/ __| '_ \\ / _` | '__/ _ \\| '_ \\ \n"
             << "| ||  __/ (__| | | | (_| | | | (_) | |_) |\n"
             << " \\__\\___|\\___| |_|_|\\__,_|_|  \\___/| .__/ \n"
             << "                                   |_|    \n" << endl;
        cout << "-----" << this->titulo << "----\n" << endl;
        for (int i = 0; i < numOpciones; ++i) {
            cout << (i + 1) << ". " << opciones[i] << endl;
        }
        cout << "0. Volver" << endl;
        cout << "------------------------------" << endl;
        cout << "Elige una opción: ";
        cin >> opcion;

        if (opcion == 0) break;

        if (opcion > 0 && opcion <= numOpciones) {
            handler->gestionarOpcion(opcion);
        } else {
            cout << "Opción no válida." << endl;
        }

        cout << "Presiona ENTER para continuar...";
        cin.ignore();
        cin.get();
    } while (true);
}

void inicializarMenus()
{
    Gestionar_mainMenu* gestiona_mainMenu = new Gestionar_mainMenu();
    Menu menuPrincipal("BIENVENIDO", 0, gestiona_mainMenu);
    menuPrincipal.anadirOpcion("Log in");
    menuPrincipal.anadirOpcion("Registrarse");
    menuPrincipal.anadirOpcion("Salir");
    menuPrincipal.display();
    delete gestiona_mainMenu;
}



