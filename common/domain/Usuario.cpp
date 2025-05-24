
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

void Usuario::serializar(Message &m) {
    m.add_param(dni);
    m.add_param(nombre);
    m.add_param(contraseña);

}
static Usuario Deserializar(const Message &m) {
    auto params=m.get_params();
    if (params.size() == 3) {
        return Usuario(params[0], params[1], params[2]);
    }
    return Usuario();
}