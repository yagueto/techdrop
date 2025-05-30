
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
Pedido::Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha,
               int estado, map<int, int> mapa) {
  this->id_pedido = id_pedido;
  this->id_usuario = id_usuario;
  this->direccion = std::move(direccion);
  this->fecha = fecha;
  this->estado = estado;
  this->mapa_pedido = std::move(mapa);
}
int Pedido::getIdPedido() const { return this->id_pedido; }
int Pedido::getIdUsuario() const { return this->id_usuario; }
string Pedido::getDireccion() const { return this->direccion; }
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

  m.add_param(std::to_string(this->fecha));

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
    try {
      int id_pedido_val = std::stoi(params[0]);
      int id_usuario_val = std::stoi(params[1]);
      std::string direccion_val = params[2];

      time_t fecha_val = std::stoll(params[3]);

      int estado_val = std::stoi(params[4]);

      Pedido pedido(id_pedido_val, id_usuario_val, direccion_val, fecha_val,
                    estado_val);

      if ((params.size() - 5) % 2 == 0) {
        for (size_t i = 5; i + 1 < params.size(); i += 2) {
          pedido.agregarPlato(std::stoi(params[i]), std::stoi(params[i + 1]));
        }
      }
      return pedido;
    } catch (const std::invalid_argument &ia) {
      return {};
    } catch (const std::out_of_range &oor) {
      std::cerr << "Error deserializing Pedido: Out of range for stoi/stoll. "
                << oor.what() << std::endl;
      return {};
    }
  }
  std::cerr << "Error deserializing Pedido: Not enough parameters. Expected at "
               "least 5, got "
            << params.size() << std::endl;
  return {};
}
