#include "Protocol.h"
#include "Plato.h"

Plato::Plato() {
  this->descripcion = " ";
  this->disponible = 0;
  this->id = NULL;
  this->nombre = " ";
  this->precio = 0;
}
Plato::Plato(int id, string nombre, string descripcion, float precio,
             int disponible) {
  this->id = id;
  this->nombre = nombre;
  this->descripcion = descripcion;
  this->precio = precio;
  this->disponible = disponible;
}
int Plato::getId() { return this->id; }
string Plato::getNombre() { return this->nombre; }
string Plato::getDescp() { return this->descripcion; }
float Plato::getPrecio() { return this->precio; }
int Plato::getDisponibilidad() { return this->disponible; }

void Plato::serializar(Message &m) {
    m.add_param(to_string(this->id));
    m.add_param(this->nombre);
    m.add_param(this->descripcion);
    m.add_param(to_string(this->precio));
    m.add_param(to_string(this->disponible));
}
static Plato Deserializar(const Message &m) {
    auto params=m.get_params();
    if (params.size() == 5) {
        return Plato(stoi(params[0]), params[1],
            params[2],stof( params[3]),stoi(params[4]));
    }
    return Plato();
}