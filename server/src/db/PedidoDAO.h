//
// Created by termi on 30/05/2025.
//

#ifndef PEDIDODAO_H
#define PEDIDODAO_H
#include <domain/Pedido.h>

#include "bd.h"


class PedidoDAO {
    static bd &db;
    PedidoDAO();
public:
    static void insert(Pedido &pedido);
    static void del(Pedido &pedido);
    static Pedido* select(Pedido &pedido);
};



#endif //PEDIDODAO_H
