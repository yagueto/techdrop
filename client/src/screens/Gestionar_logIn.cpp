//
// Created by naia.martin on 21/05/2025.
//

#include "Gestionar_logIn.h"
#include <iostream>

#include "Gestionar_inicio.h"
#include "Gestionar_registro.h"
#include "../../../local_admin/src/utils.h"
using namespace std;

void Gestionar_logIn::gestionarOpcion(int  opcion)
{
    string username, password;
    cout<<"Username: ";
    cin.ignore(); //para limpiar
    cin >> username;
    cout<<"Password: ";
    cin>>password;
    cin.ignore();

    if (username == "user" && password == "pass")
    {
        cout<<"Login exitoso."<<endl;
        Gestionar_inicio* gestiona_inicio = new Gestionar_inicio();
        Menu inicio("INICIO", 0, gestiona_inicio);
        inicio.anadirOpcion("Gestionar pedidos");
        inicio.anadirOpcion("Configuración usuario");
        inicio.anadirOpcion("Volver");
        inicio.display();
        delete gestiona_inicio;
        cout<<endl;
    }else
    {
        cout<<"Credenciales no validas."<<endl;
    }

}