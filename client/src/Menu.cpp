#include "Menu.h"
#include <iostream>
#include <utility>

#include "domain/utils.h"

using namespace std;

Menu::Menu(const Socket &server_socket, string titulo, const bool principal) {
  this->titulo = move(titulo); // para evitar copias innecesarias
  this->esMenuPrincipal = principal;
  this->numOpciones = 0;
  this->server_socket = server_socket;
}

Menu::~Menu() = default;

void Menu::anadirOpcion(const string &texto) {
  if (numOpciones < OPCIONES_MAX) {
    opciones[numOpciones++] = texto;
  } else {
    cout << "Maximo de opciones alcanzado." << endl;
  }
}

void Menu::display() {
  int opcion = -1;
  do {
    clrscr();
    cout << " _            _         _                 \n"
         << "| |_ ___  ___| |__   __| |_ __ ___  _ __  \n"
         << "| __/ _ \\/ __| '_ \\ / _` | '__/ _ \\| '_ \\ \n"
         << "| ||  __/ (__| | | | (_| | | | (_) | |_) |\n"
         << " \\__\\___|\\___| |_|_|\\__,_|_|  \\___/| .__/ \n"
         << "                                   |_|    \n"
         << endl;
    cout << "----- " << this->titulo << " -----\n" << endl;
    for (int i = 0; i < numOpciones; ++i) {
      cout << (i + 1) << ". " << opciones[i] << endl;
    }
    cout << "0. Volver" << endl;
    cout << "------------------------------" << endl;
    cout << "Elige una opción: ";
    cin >> opcion;
    clearInputBuffer();
    if (opcion == 0) {
      if (esMenuPrincipal) {
        cout << "\n¡Hasta pronto!\n";
        exit(0);
      } else {
        break;
      }
    }
    if (opcion > 0 && opcion <= numOpciones) {
      gestionarOpcion(opcion);
      waitForEnter();
    } else {
      cout << "Opción no válida." << endl;
      waitForEnter();
    }

  } while (true);
}
