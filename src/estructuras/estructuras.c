//
// Created by naia.martin on 26/03/2025.
//
#include "estructuras.h"
#include <stdlib.h>

Pedido* crearArrayPedidos(int capacidad)
{
    return (Pedido*)malloc(capacidad * sizeof(Pedido));
}
Plato* crearArrayPlatos(int capacidad)
{
    return (Plato*)malloc(capacidad * sizeof(Plato));
}
PedidoDetalle* crearArrayPedidoDetalle(int capacidad)
{
    return (PedidoDetalle*)malloc(capacidad * sizeof(PedidoDetalle));
}
Robot* crearArrayRobots(int capacidad)
{
    return (Robot*)malloc(capacidad * sizeof(Robot));
}