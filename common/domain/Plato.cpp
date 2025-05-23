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

string Plato::serialize() const {
    string serialized_plato;
    serialized_plato += to_string(this->id) + MESSAGE_DELIMITER;
    serialized_plato += this->nombre + MESSAGE_DELIMITER;
    serialized_plato += this->descripcion + MESSAGE_DELIMITER;
    serialized_plato += to_string(this->precio) + MESSAGE_DELIMITER;
    serialized_plato += to_string(this->disponible)+ MESSAGE_DELIMITER;

    return serialized_plato;
}
static Plato deserialize(const string &str) {
    int pos=0;
    int sig_pos;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Plato();
    int id= stoi(str.substr(pos, sig_pos - pos));
    pos=sig_pos + 1;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Plato();
    string nombre = str.substr(pos, sig_pos - pos);
    pos=sig_pos + 1;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Plato();
    string descripcion = str.substr(pos, sig_pos - pos);
    pos=sig_pos + 1;

    sig_pos = str.find(MESSAGE_DELIMITER, pos);
    if (sig_pos == string::npos) return Plato();
    float precio = stof(str.substr(pos, sig_pos - pos));
    pos=sig_pos + 1;

    int disponible = stoi(str.substr(pos));

    return Plato(id,nombre,descripcion,precio,disponible);
}