//
// Created by maddi.esparta on 26/03/2025.
//
#include "sqlite3.h"
#include "estructuras/estructuras.h"
#ifndef BD_H
#define BD_H

int crearTablas(sqlite3* db);
void datosPruebaPedido(sqlite3* db);

//Funciones para cargar datos de la BD
Pedido* cargarPedidos(sqlite3 *db, int *total);
Plato* cargarPlatos(sqlite3 *db, int *total);
Robot* cargarRobots(sqlite3 *db, int *total);

#endif //BD_H
