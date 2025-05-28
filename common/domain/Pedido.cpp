
#include "Pedido.h"

#include "Protocol.h"
#include <utility>

Pedido::Pedido() {
  this->direccion = " ";
  this->estado = 0;
  this->fecha = 0;
  this->id_pedido = 0;
  this->id_usuario = 0;
}
Pedido::Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha,
               int estado) {
  this->id_pedido = id_pedido;
  this->id_usuario = id_usuario;
  this->direccion = std::move(direccion);
  this->fecha = fecha;
  this->estado = estado;
}
int Pedido::getIdPedido() const { return this->id_pedido; }
int Pedido::getIdUsuario() const { return this->id_usuario; }
string Pedido::getDireccion() { return this->direccion; }
time_t Pedido::getFecha() const { return this->fecha; }
int Pedido::getEstado() const { return this->estado; }
map<int, int> Pedido::getMapa() { return this->mapa_pedido; }
void Pedido::agregarPlato(int id_plato, int cantidad) {
  if (cantidad <= 0) {
    cout << "La cantidad no es valida" << endl;
  } else {
    mapa_pedido[id_plato] = cantidad;
  }
}
void Pedido::serializar(Message &m) const {
  m.add_param(to_string(this->id_pedido));
  m.add_param(to_string(this->id_usuario));
  m.add_param(this->direccion);

  tm *ptm = localtime(&this->fecha);
  char buffer[32];
  strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
  m.add_param(buffer);
  m.add_param(to_string(this->estado));

  if (!this->mapa_pedido.empty()) {
    for (const auto &i : this->mapa_pedido) {
      m.add_param(to_string(i.first));
      m.add_param(to_string(i.second));
    }
  }
}

Pedido Pedido::deserializar(const Message &m) {
  auto params = m.get_params();
  if (params.size() >= 5) {
    Pedido pedido(stoi(params[0]), stoi(params[1]), params[2], stol(params[3]),
                  stoi(params[4]));

    for (int i = 5; i < params.size(); i += 2) {
      pedido.agregarPlato(stoi(params[i]), stol(params[i + 1]));
    }
    return pedido;
  }
  return {};
}