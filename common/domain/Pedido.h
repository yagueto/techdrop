
#ifndef PEDIDO_H
#define PEDIDO_H

#include "Plato.h"
#include <iostream>
#include <map>

using namespace std;

class Pedido {

  int id_pedido;
  int id_usuario;
  string direccion;
  time_t fecha;
  int estado;
  map<int, int> mapa_pedido;

public:
  Pedido();
  Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha, int estado);
  int getIdPedido();
  int getIdUsuario();
  string getDireccion();
  time_t getFecha();
  int getEstado();
  void agregarPlato(int id_plato, int cantidad);
  map<int, int> getMapa();

  string serialize() const;
  static Pedido deserialize(const string& str);
};

#endif // PEDIDO_H
