#include "Menu.h"
#include <iostream>
#include <utility>

#include "domain/utils.h"


using namespace std;

Menu::Menu(string titulo, bool esPrincipal) {
    this->titulo = move(titulo); //para evitar copias innecesarias
    this->esMenuPrincipal = esPrincipal;
    this->numOpciones = 0;
}

void Menu::anadirOpcion(const string &texto, function<void()> accion) {
    if (numOpciones < OPCIONES_MAX) {
        opciones[numOpciones] = texto;
        acciones[numOpciones] = move(accion);
        numOpciones++;
    } else {
        cout << "No se pueden añadir mas opciones." << endl;
    }
}

Menu::~Menu()= default;

void Menu::display() const
{
    int opcion = -1;
    do {
        clrscr();
        cout << " _            _         _                 \n"
             << "| |_ ___  ___| |__   __| |_ __ ___  _ __  \n"
             << "| __/ _ \\/ __| '_ \\ / _` | '__/ _ \\| '_ \\ \n"
             << "| ||  __/ (__| | | | (_| | | | (_) | |_) |\n"
             << " \\__\\___|\\___| |_|_|\\__,_|_|  \\___/| .__/ \n"
             << "                                   |_|    \n" << endl;
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
            acciones[opcion - 1]();
            clrscr();
            waitForEnter();
        } else {
            cout << "Opción no válida." << endl;
            clrscr();
            waitForEnter();
        }
    } while (true);
}

void crearMenuPrincipal() {
    Menu menu("BIENVENIDO", true);
    menu.anadirOpcion("Log in", []() {
        crearMenuLogin();
    });
    menu.anadirOpcion("Registrar cuenta", []() {
        crearMenuRegistro();
    });
    menu.display();
}

void crearMenuLogin() {
    clrscr();
    string username, password;

    cout << "Username: ";
    cin >> username;
    clearInputBuffer();
    cout << "Password: ";
    cin >> password;
    clearInputBuffer();

    if (username == "user" && password == "pass") {
        cout << "Login exitoso." << endl;
        clrscr();
        waitForEnter();
        crearMenuInicio();
    } else {
        cout << "Credenciales no válidas." << endl;
        clrscr();
        waitForEnter();
    }
}

void crearMenuInicio() {
    Menu menu("INICIO");

    menu.anadirOpcion("Gestionar pedidos", []() {
        crearMenuPedidos();
    });

    menu.anadirOpcion("Configuración usuario", []() {
        crearMenuUsuario();
    });

    menu.display();
}

void crearMenuPedidos() {
    Menu menu("PEDIDOS");

    menu.anadirOpcion("Hacer pedido", []() {
        cout << "Hace pedido" << endl;
    });

    menu.anadirOpcion("Borrar pedido", []() {
        cout << "Borra pedido" << endl;
    });

    menu.anadirOpcion("Ver todos los pedidos", []() {
        cout << "Muestra historial de pedidos" << endl;
    });

    menu.display();
}

void crearMenuUsuario() {
    Menu menu("CONFIGURACION USUARIO");

    menu.anadirOpcion("Cambiar username", []() {
        cout << "Cambiar username" << endl;
    });

    menu.anadirOpcion("Cambiar contraseña", []() {
        cout << "Cambiar contraseña" << endl;
    });

    menu.anadirOpcion("Borrar cuenta", []() {
        cout << "Borrar cuenta" << endl;
    });

    menu.display();
}

void crearMenuRegistro() {
    string dni, username, password;

    cout << "DNI: ";
    cin >> dni;
    clearInputBuffer();

    cout << "Username: ";
    cin >> username;
    clearInputBuffer();

    cout << "Password: ";
    cin >> password;
    clearInputBuffer();

    // aqui la logica bd
    cout << "Usuario registrado con éxito." << endl;
    clrscr();
    waitForEnter();
}