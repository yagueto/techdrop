#include "Plato.h"
#include "Protocol.h"

Plato::Plato() {
  this->descripcion = " ";
  this->disponible = 0;
  this->id = NULL;
  this->nombre = " ";
  this->precio = 0;
}
Plato::Plato(const int id, const string &nombre, const string &descripcion,
             const float precio, const int disponible) {
  this->id = id;
  this->nombre = nombre;
  this->descripcion = descripcion;
  this->precio = precio;
  this->disponible = disponible;
}
int Plato::getId() const { return this->id; }
string Plato::getNombre() const { return this->nombre; }
string Plato::getDescp() const { return this->descripcion; }
float Plato::getPrecio() const { return this->precio; }
int Plato::getDisponibilidad() const { return this->disponible; }

void Plato::serializar(Message &m) const {
  m.add_param(to_string(this->id));
  m.add_param(this->nombre);
  m.add_param(this->descripcion);
  m.add_param(to_string(this->precio));
  m.add_param(to_string(this->disponible));
}
Plato Plato::Deserializar(const Message &m) {
  auto params = m.get_params();
  if (params.size() == 5) {
    return {stoi(params[0]), params[1], params[2], stof(params[3]),
            stoi(params[4])};
  }
  return {};
}