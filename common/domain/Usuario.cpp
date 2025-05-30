
#include "Usuario.h"
#include "Protocol.h"
using namespace std;
Usuario::Usuario() {
  this->nombre = " ";
  this->contraseña = " ";
  this->dni = " ";
}
Usuario::Usuario(const string &dni, const string &nombre,
                 const string &contraseña) {
  this->nombre = nombre;
  this->dni = dni;
  this->contraseña = contraseña;
}
string Usuario::getDni() { return this->dni; }
string Usuario::getNombre() { return this->nombre; }
string Usuario::getContraseña() { return this->contraseña; }

void Usuario::serializar(Message &m) const {
  m.add_param(dni);
  m.add_param(nombre);
  m.add_param(contraseña);
}
Usuario Usuario::Deserializar(const Message &m) {
  if (vector<string> params = m.get_params(); params.size() == 3) {
    return {params[0], params[1], params[2]};
  }
  return {};
}