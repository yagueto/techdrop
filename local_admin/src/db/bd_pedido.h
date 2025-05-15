#ifndef BD_PEDIDO_H
#define BD_PEDIDO_H
#include "models/pedido.h"

int pedidoCola();
Pedido* get_pedido(int id);
int actualizarEstadoPedido(Pedido* pedido, int estado);

#endif //BD_PEDIDO_H
