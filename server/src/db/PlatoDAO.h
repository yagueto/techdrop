//
// Created by maddi.esparta on 30/05/2025.
//

#ifndef PLATODAO_H
#define PLATODAO_H

#include "BD.h"
#include "domain/Plato.h"

class PlatoDAO {
    static BD &db;
    PlatoDAO();
public:
    static void insert(const Plato &plato);
    static void del(const Plato &plato);
    static std::vector<Plato> getPlatos();
    static Plato get_plato_por_id(int id);
};



#endif //PLATODAO_H
