
#include "Message.h"
#ifndef USUARIO_H
#define USUARIO_H


class Usuario {
    std::string dni;
    std::string nombre;
    std::string contraseña;
public:
    Usuario();
    Usuario(const std::string &dni, const std::string &nombre, const std::string &contraseña);
    std::string getDni();
    std::string getNombre();
    std::string getContraseña();

    void setDni(const std::string &dni);
    void setNombre(const std::string &nombre);
    void setContraseña(const std::string &contraseña);

    void serializar(Message &m) const;
    static Usuario Deserializar(const Message &m);

};



#endif //USUARIO_H
