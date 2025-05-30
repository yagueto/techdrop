//
// Created by termi on 30/05/2025.
//

#ifndef PEDIDODAO_H
#define PEDIDODAO_H
#include <domain/Pedido.h>
#include <domain/Usuario.h>

#include "BD.h"


class PedidoDAO {
    static BD &db;
    PedidoDAO();
public:
    static void insert(Pedido &pedido);
    static void del(Pedido &pedido);
    static Pedido* select(Pedido &pedido);
    static std::vector<Pedido> historial(Usuario &usuario);
};



#endif //PEDIDODAO_H
