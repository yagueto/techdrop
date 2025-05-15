//
// Created by naia.martin on 15/05/2025.
//

#include "Usuario.h"
Usuario::Usuario()
{
    this->nombre = " ";
    this->contraseña = " ";
    this->dni = " ";
}
Usuario::Usuario(string dni, string nombre, string contraseña)
{
    this->nombre = nombre;
    this->dni = dni;
    this->contraseña = contraseña;
}
string Usuario::getDni()
{
    return this->dni;
}
string Usuario::getNombre()
{
    return this->nombre;
}
string Usuario::getContraseña()
{
    return this->contraseña;
}