//
// Created by naia.martin on 15/05/2025.
//
#include "Message.h"
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
    Usuario(const string &dni, const string &nombre, const string &contraseña);
    string getDni();
    string getNombre();
    string getContraseña();

    void serializar(Message &m) const;
    static Usuario Deserializar(const Message &m);

};



#endif //USUARIO_H
