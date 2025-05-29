#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <functional>

class Handler;

using namespace std;

#define OPCIONES_MAX 10

class Menu
{
    string titulo;
    string opciones[OPCIONES_MAX];
    function<void()> acciones[OPCIONES_MAX];
    int numOpciones;
    bool esMenuPrincipal;

public:
    Menu(string titulo, bool principal = false);
    virtual ~Menu();

    void anadirOpcion(const string& texto, function<void()> accion);
    void display() const;;

};

void inicializarMenus();
void crearMenuPrincipal();
void crearMenuLogin();
void crearMenuInicio();
void crearMenuPedidos();
void crearMenuRegistro();
void crearMenuUsuario();

#endif //MENU_H
