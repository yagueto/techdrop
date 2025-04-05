//
// Created by maddi.esparta on 05/04/2025.
//
#include "models/pedido.h"
#ifndef BD_PEDIDO_H
#define BD_PEDIDO_H

int pedidoCola();
Pedido* get_pedido(int id);
int actualizarEstadoPedido(Pedido* pedido, int estado);

#endif //BD_PEDIDO_H
