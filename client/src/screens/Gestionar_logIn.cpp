#include "Gestionar_logIn.h"
#include <iostream>

#include "Gestionar_inicio.h"
#include "Gestionar_registro.h"
#include "Menu.h"
#include "../../../local_admin/src/utils.h"
using namespace std;

void Gestionar_logIn::gestionarOpcion(int  opcion)
{
    string username, password;
    clrscr(); //Limpia la pantalla
    cout<<"Username: ";
    cin >> username;
    clearInputBuffer();
    cout<<"Password: ";
    cin>>password;
    clearInputBuffer();

    if (username == "user" && password == "pass")
    {
        cout<<"Login exitoso."<<endl;
        Gestionar_inicio* gestiona_inicio = new Gestionar_inicio();
        clrscr();
        Menu inicio("INICIO", 0, gestiona_inicio);
        inicio.anadirOpcion("Gestionar pedidos");
        inicio.anadirOpcion("Configuración usuario");
        inicio.display();
        delete gestiona_inicio;
        cout<<endl;
    }else
    {
        cout<<"Credenciales no validas."<<endl;
    }

}