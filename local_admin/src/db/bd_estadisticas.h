#ifndef BD_ESTADISTICAS_C_H
#define BD_ESTADISTICAS_C_H

#include <sqlite3.h>

int obtenerTotalPedidosPorDia(sqlite3 *db, const char *fecha);
int obtenerZonasPopulares(sqlite3 *db, char zonas[][100], int *contadores, int numZonas);
int obtenerHoraPico(sqlite3 *db);
int obtenerPlatosMasVendidos(sqlite3 *db, int *ids_platos, int *cantidades, int numplatos);
int obtenerClientesRecurrentes(sqlite3 *db, int *ids_usuarios, int *total_pedidos, int numUsuarios);
double obtenerValorMedioPedido(sqlite3 *db);
int obtenerRobotsActivos(sqlite3 *db);

#endif //BD_ESTADISTICAS_C_H