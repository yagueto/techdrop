#ifndef MENU_H
#define MENU_H

#include "Socket.h"

#include <functional>
#include <iostream>
#include <string>

using namespace std;

#define OPCIONES_MAX 10

class Menu {
  string titulo;
  string opciones[OPCIONES_MAX];
  int numOpciones;
  bool esMenuPrincipal;

protected:
  Socket server_socket;

public:
  Menu(const Socket &server_socket, string titulo, bool principal = false);
  virtual ~Menu();

  void anadirOpcion(const string &texto);
  virtual void gestionarOpcion(int opcion) = 0;
  void display();
};

#endif // MENU_H
