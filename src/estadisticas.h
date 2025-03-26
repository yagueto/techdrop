//
// Created by naia.martin on 26/03/2025.
//
#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "sqlite3.h"
#include "estructuras.h"

//Funciones para las estadisticas de negocio
void calcularPedidosPorDia(sqlite3 *db);
void calcularPedidosPorMes(sqlite3 *db);
void calcularZonasPopulares(sqlite3 *db);
void calcularHoraPico(sqlite3 *db);
void calcularPlatosMasVendidos(sqlite3 *db);
void calcularClientesRecurrentes(sqlite3 *db);
void calcularValorMedioPedido(sqlite3 *db);

//Funciones para las estadisticas de robots
void calcularPedidosPorRobot(sqlite3 *db);
void calcularRobotsActivos(sqlite3 *db);

#endif //ESTADISTICAS_H
