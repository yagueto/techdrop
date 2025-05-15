
#include "Pedido.h"

Pedido::Pedido()
{
   this->direccion = " ";
   this->estado = 0;
   this->fecha = NULL;
   this->id_pedido = NULL;
   this->id_usuario = NULL;

}
Pedido::Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha, int estado)
{
   this->id_pedido = id_pedido;
   this->id_usuario =  id_usuario;
   this->direccion = direccion;
   this->fecha = fecha;
   this->estado = estado;
}
int Pedido::getIdPedido()
{
   return this->id_pedido;
}
int Pedido::getIdUsuario()
{
   return this->id_usuario;
}
string Pedido::getDireccion()
{
   return this->direccion;
}
time_t Pedido::getFecha()
{
   return this->fecha;
}
int Pedido::getEstado()
{
   return this->estado
}
map<Plato,int> Pedido::getMapa()
{
   return this->mapa_pedido;
}