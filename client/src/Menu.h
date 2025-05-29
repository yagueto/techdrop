#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <functional>

using namespace std;

#define OPCIONES_MAX 10

class Menu
{
    string titulo;
    string opciones[OPCIONES_MAX];
    int numOpciones;
    bool esMenuPrincipal;

public:
    Menu(string titulo, bool principal = false);
    virtual ~Menu();

    void anadirOpcion(const string& texto);
    virtual void gestionarOpcion(int opcion) = 0;
    void display();

};

#endif //MENU_H
