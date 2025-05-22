//
// Created by naia.martin on 21/05/2025.
//

#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
class Handler;
using namespace std;

#define OPCIONES_MAX 10

class Menu
{
    string titulo;
    int numOpciones;
    Handler* handler;
    string opciones[10];

public:
    Menu(string titulo, int numOpciones, Handler* handler);
    Menu();
    virtual ~Menu();

    string getTitulo();
    int getNumOpciones();
    void setNumOpciones(int numero);
    Handler* getHandler();

    void anadirOpcion(const string& string);
    void display();
};

void inicializarMenus();

#endif //MENU_H
