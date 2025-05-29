#include "MenuPrincipal.h"

#include "MenuInicio.h"
#include "domain/utils.h"

MenuPrincipal::MenuPrincipal(): Menu("BIENVENIDO", true)
{
    anadirOpcion("Log in");
    anadirOpcion("Registrar cuenta");
}

void MenuPrincipal::gestionarOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        {
            string username, password;
            clrscr();
            cout << "Username: ";
            cin >> username;
            clearInputBuffer();
            cout << "Password: ";
            cin >> password;
            clearInputBuffer();

            if (username == "user" && password == "pass")
            {
                cout << "Login exitoso." << endl;
                clrscr();
                waitForEnter();
                MenuInicio inicio;
                inicio.display();
            }
            else
            {
                cout << "Usuario o contraseña incorrectos" << endl;
            }
        }
        break;
    case 2:
        {
            clrscr();

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

            cout << "Usuario registrado" << endl;
        }
        break;
    default:
        cout << "Opcion no valida." << endl;
        break;
    }
}
