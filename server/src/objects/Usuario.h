//
// Created by naia.martin on 15/05/2025.
//

#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
using namespace std;

class Usuario {
    string dni;
    string nombre;
    string contraseña;
public:
    Usuario();
    Usuario(string dni, string nombre, string contraseña);
    string getDni();
    string getNombre();
    string getContraseña();
};



#endif //USUARIO_H
