
#ifndef PEDIDO_H
#define PEDIDO_H
#include <pthread_time.h>

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
    map<Plato, int> mapa_pedido;
public:
    Pedido();
    Pedido(int id_pedido, int id_usuario, string direccion, time_t fecha, int estado);
    int getIdPedido();
    int getIdUsuario();
    string getDireccion();
    time_t getFecha();
    int getEstado();
    map<Plato,int> getMapa();


};



#endif //PEDIDO_H
