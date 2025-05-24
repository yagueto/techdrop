
#ifndef PLATO_H
#define PLATO_H

#include "Message.h"
using namespace std;

class Plato {
  int id;
  string nombre;
  string descripcion;
  float precio;
  int disponible;

public:
  Plato();
  Plato(int id, const string &nombre, const string &descripcion, float precio,
        int disponible);
  int getId() const;
  string getNombre() const;
  string getDescp() const;
  float getPrecio() const;
  int getDisponibilidad() const;

  void serializar(Message &m) const;
  static Plato Deserializar(const Message &m);
};

#endif // PLATO_H
