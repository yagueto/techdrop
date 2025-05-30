
#ifndef PEDIDO_H
#define PEDIDO_H

#include "Message.h"
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
  Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha,
         int estado);
    Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha,
         int estado, map<int,int> mapa_pedido);
  int getIdPedido() const;
    void setIdPedido(int id_pedido);
    int getIdUsuario() const;
    string getDireccion() const;
    time_t getFecha() const;
    int getEstado() const;
  void agregarPlato(int id_plato, int cantidad);
  map<int, int> getMapa();

  void serializar(Message &m) const;
  static Pedido deserializar(const Message &m);
};

#endif // PEDIDO_H
