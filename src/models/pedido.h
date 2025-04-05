#ifndef PEDIDO_H
#define PEDIDO_H
#include <time.h>

#include "plato.h"

#define ESTADO_PEDIDO_RECIBIDO 0;
#define ESTADO_PEDIDO_EN_PROCESO 1;
#define ESTADO_PEDIDO_EN_REPARTO 2;
#define ESTADO_PEDIDO_ENTREGADO 3;

typedef struct
{
    Plato* plato;
    int cantidad;
} ElementoPedido;  // Plato en el pedido y cantidad

typedef struct
{
    int id;
    // Usuario usuario; // TODO: crear usuario
    char* direccion;
    time_t fecha;
    int estado;
    ElementoPedido** platos; // Lista de elementos en el pedido
} Pedido;

time_t string_a_time(char* s);
#endif //PEDIDO_H
