#include "Menu.h"
#include "Handler.h"
#include <iostream>

#include "domain/utils.h"
#include "screens/Gestionar_mainMenu.h"


using namespace std;

Menu::Menu(string titulo, int numOpciones, Handler* handler, bool esPrincipal) {
    this->titulo = titulo;
    this->numOpciones = numOpciones;
    this->handler = handler;
    this->esMenuPrincipal = esPrincipal;
}

void Menu::anadirOpcion(const string &texto) {
    if (numOpciones < OPCIONES_MAX) {
        opciones[numOpciones++] = texto;
    } else {
        cout << "No se pueden añadir más opciones, se alcanzó el límite." << endl;
    }
}

Menu::~Menu() {}

string Menu::getTitulo() {
    return this->titulo;
}

int Menu::getNumOpciones() {
    return this->numOpciones;
}

void Menu::setNumOpciones(int numero) {
    this->numOpciones = numero;
}

Handler* Menu::getHandler() {
    return this->handler;
}
void Menu::display()
{
    int opcion = -1;
    do
    {
        clrscr();
        // Cabecera del programa
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
        clearInputBuffer();

        if (opcion == 0){
            if (esMenuPrincipal)
            {
                cout << "\n¡Hasta pronto!\n";
                exit(0);
            }
        } else {
            break;
        }

        if (opcion > 0 && opcion <= numOpciones) {
            handler->gestionarOpcion(opcion);
            waitForEnter();
            clrscr();
        } else {
            cout << "Opción no valida." << endl;
            waitForEnter();
            clrscr();
        }
    }while (true);
}
void inicializarMenus() {
    Menu* menu = new Menu("BIENVENIDO", 0, new Gestionar_mainMenu(), true);
    menu->anadirOpcion("Log in");
    menu->anadirOpcion("Registrar cuenta");
    menu->display();
}
