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
    Usuario(const string &dni, const string &nombre, const string &contraseña);
    string getDni();
    string getNombre();
    string getContraseña();

    string serialize() const;
    static Usuario deserialize(const string &str);
};



#endif //USUARIO_H
