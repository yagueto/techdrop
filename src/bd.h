//
// Created by maddi.esparta on 26/03/2025.
//
#include "sqlite3.h"
#include "estructuras/estructuras.h"
#ifndef BD_H
#define BD_H

int crearTablas(sqlite3* db);
void datosPrueba(sqlite3* db);

//Funciones para cargar datos de la BD
Pedido* cargarPedidos(sqlite3 *db, int *total);
Plato* cargarPlatos(sqlite3 *db, int *total);
Robot* cargarRobots(sqlite3 *db, int *total);

int actualizarPedido(sqlite3 *db, const Pedido *pedido);
int actualizarArrayPedidos(sqlite3 *db, const Pedido *pedidos, int total);

//Funciones para calcular estadisticas
int obtenerTotalPedidosPorDia(sqlite3 *db, const char *fecha);
int obtenerTotalPedidosPorMes(sqlite3 *db, const char *mes);
int obtenerZonasPopulares(sqlite3 *db, char zonas[][100], int *contadores, int numZonas);
int obtenerHoraPico(sqlite3 *db);
int obtenerPlatosMasVendidos(sqlite3 *db, int *ids_platos, int *cantidades, int numPlatos);
int obtenerClientesRecurrentes(sqlite3 *db, int *ids_usuarios, int *total_pedidos, int numUsuarios);
double obtenerValorMedioPedido(sqlite3 *db);
int obtenerPedidosPorRobot(sqlite3 *db, int *ids_robots, int *total_pedidos, int numRobots);
int obtenerRobotsActivos(sqlite3 *db);

#endif //BD_H
