
#include "Pedido.h"
#include "Protocol.h"

Pedido::Pedido() {
  this->direccion = " ";
  this->estado = 0;
  this->fecha = NULL;
  this->id_pedido = NULL;
  this->id_usuario = NULL;
}
Pedido::Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha,
               int estado) {
  this->id_pedido = id_pedido;
  this->id_usuario = id_usuario;
  this->direccion = direccion;
  this->fecha = fecha;
  this->estado = estado;
}
int Pedido::getIdPedido() { return this->id_pedido; }
int Pedido::getIdUsuario() { return this->id_usuario; }
string Pedido::getDireccion() { return this->direccion; }
time_t Pedido::getFecha() { return this->fecha; }
int Pedido::getEstado() { return this->estado; }
map<int, int> Pedido::getMapa() { return this->mapa_pedido; }
void Pedido::agregarPlato(int id_plato, int cantidad) {
    if (cantidad <=0) {
        cout << "La cantidad no es valida" <<endl;
    }else {
        mapa_pedido[id_plato] =cantidad;
    }

}
string Pedido::serialize() const {
    string serialized_pedido;
    serialized_pedido += to_string(this->id_pedido) + MESSAGE_DELIMITER;
    serialized_pedido += to_string(this->id_usuario) + MESSAGE_DELIMITER;
    serialized_pedido += this->direccion + MESSAGE_DELIMITER;

    tm * ptm = localtime(&this->fecha);
    char buffer[32];
    strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
    serialized_pedido += string(buffer) + MESSAGE_DELIMITER;
    serialized_pedido += to_string(this->estado) + MESSAGE_DELIMITER;

    for (auto const& [id_plato,cantidad] : this->mapa_pedido) {
        serialized_pedido += to_string(id_plato) + MESSAGE_DELIMITER;
        serialized_pedido += to_string(cantidad) + MESSAGE_DELIMITER;
    }
    return serialized_pedido;
}
static Pedido deserialize(const string& str) {
    int pos;
    int sig_pos;
    try {
        sig_pos = str.find(MESSAGE_DELIMITER, pos);
        if (sig_pos == string::npos) return Pedido();
        int id_pedido = stoi(str.substr(pos, sig_pos - pos));
        pos = sig_pos + 1;

        sig_pos = str.find(MESSAGE_DELIMITER, pos);
        if (sig_pos == string::npos) return Pedido();
        int id_usuario = stoi(str.substr(pos, sig_pos - pos));
        pos = sig_pos + 1;

        sig_pos = str.find(MESSAGE_DELIMITER, pos);
        if (sig_pos == string::npos) return Pedido();
        string direccion = str.substr(pos, sig_pos - pos);
        pos = sig_pos + 1;

        sig_pos = str.find(MESSAGE_DELIMITER, pos);
        if (sig_pos == string::npos) return Pedido();
        time_t fecha = stol(str.substr(pos, sig_pos - pos));
        pos = sig_pos + 1;

        sig_pos = str.find(MESSAGE_DELIMITER, pos);
        if (sig_pos == string::npos) return Pedido();
        int estado = stoi(str.substr(pos, sig_pos - pos));
        pos = sig_pos + 1;
        Pedido p(id_pedido,id_usuario,direccion,fecha,estado);

        while (pos < str.length()) {
            sig_pos = str.find(MESSAGE_DELIMITER, pos);
            if (sig_pos == string::npos) break;
            int id_plato = stoi(str.substr(pos, sig_pos - pos));
            pos = sig_pos + 1;

            sig_pos = str.find(MESSAGE_DELIMITER, pos);
            if (sig_pos == string::npos) break;
            int cantidad = stoi(str.substr(pos, sig_pos - pos));
            pos = sig_pos + 1;
            p.agregarPlato(id_plato,cantidad);
        }
        return p;
    }catch(const exception& e) {
        return Pedido();
    }

}
