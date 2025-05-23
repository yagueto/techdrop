
#include "Protocol.h"
#include "Usuario.h"
using namespace std;
Usuario::Usuario()
{
    this->nombre = " ";
    this->contraseña = " ";
    this->dni = " ";
}
Usuario::Usuario(const string &dni, const string &nombre,
                 const string &contraseña)
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

string Usuario::serialize() const {
    string serialized_usuario;
    serialized_usuario+= this->nombre;
    serialized_usuario+= MESSAGE_DELIMITER;
    serialized_usuario+= this->contraseña;
    serialized_usuario+= MESSAGE_DELIMITER;
    serialized_usuario+= this->dni;
    serialized_usuario+= MESSAGE_DELIMITER;
    return serialized_usuario;
}
static Usuario deserialize(const string &str) {
    int pos=0;
    int sig_pos;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Usuario();
    string dni = str.substr(pos, sig_pos - pos);
    pos = sig_pos + 1;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Usuario();
    string nombre = str.substr(pos, sig_pos - pos);
    pos = sig_pos + 1;

    string contraseña = str.substr(pos);

    return Usuario(dni,nombre,contraseña);
}