#include "Gestionar_registro.h"
#include <string>
#include <iostream>

#include "domain/utils.h"
using namespace std;

void Gestionar_registro::gestionarOpcion(int  opcion)
{
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

    //Anadir lo de base de datos, logica para registrar
    cout << "Usuario registrado con éxito."<<endl;
}