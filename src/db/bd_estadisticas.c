#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <models/robot.h>
#include <db/bd_new.h>
#include "bd_estadisticas.h"

int obtenerTotalPedidosPorDia(sqlite3 *db, const char *fecha) {
    if (!fecha) {
        fprintf(stderr, "Parametros invalidos\n");
        return -1;
    }

    const char *sql = "SELECT COUNT(*) FROM Pedido WHERE DATE(fecha) = ?;";
    sqlite3_stmt *stmt = NULL;
    int total = -1;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error preparando consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    //Vincular el parametro de fecha
    rc = sqlite3_bind_text(stmt, 1, fecha, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error vinculando fecha: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    //Ejecutar
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        //si tiene otra fila
        total = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error ejecutando consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return total;
}

int obtenerZonasPopulares(sqlite3 *db, char zonas[][100], int *contadores, int numZonas) {
    const char *sql = "SELECT direccion, COUNT(*) FROM Pedido GROUP BY direccion ORDER BY COUNT(*) DESC;";
    sqlite3_stmt *stmt;
    int zonasHalladas = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_int(stmt, 1, numZonas);
    while (sqlite3_step(stmt) == SQLITE_ROW && zonasHalladas < numZonas) {
        const char *direccion = (const char *)sqlite3_column_text(stmt, 0);
        strncpy(zonas[zonasHalladas], direccion, 100);
        contadores[zonasHalladas] = sqlite3_column_int(stmt, 1);
        zonasHalladas++;
    }

    sqlite3_finalize(stmt);
    return zonasHalladas;
}


int obtenerHoraPico(sqlite3 *db) {
    const char *sql = "SELECT strftime('%H', fecha), COUNT(*) FROM Pedido GROUP BY strftime('%H', fecha) ORDER BY COUNT(*) DESC LIMIT 1;";
    sqlite3_stmt *stmt;
    int hora_pico = -1;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        hora_pico = atoi((const char *)sqlite3_column_text(stmt, 0)); //atoi: de str a int
    }

    sqlite3_finalize(stmt);
    return hora_pico;
}

int obtenerPlatosMasVendidos(sqlite3 *db, int *ids_platos, int *cantidades, int numplatos) {
    const char *sql = "SELECT id_plato, SUM(cantidad) FROM PedidoDetalle GROUP BY id_plato ORDER BY SUM(cantidad);";
    sqlite3_stmt *stmt;
    int platos_obtenidos = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_int(stmt, 1, numplatos);
    while (sqlite3_step(stmt) == SQLITE_ROW && platos_obtenidos < numplatos) {
        ids_platos[platos_obtenidos] = sqlite3_column_int(stmt, 0);
        cantidades[platos_obtenidos] = sqlite3_column_int(stmt, 1);
        platos_obtenidos++;
    }

    sqlite3_finalize(stmt);
    return platos_obtenidos;
}



int obtenerClientesRecurrentes(sqlite3 *db, int *ids_usuarios, int *total_pedidos, int numUsuarios)
{
    const char *sql = "SELECT id_usuario, COUNT(*) FROM Pedido GROUP BY id_usuario ORDER BY COUNT(*) DESC;";
    sqlite3_stmt *stmt;
    int usuarios = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_int(stmt, 1, numUsuarios);

    while (sqlite3_step(stmt) == SQLITE_ROW && usuarios < numUsuarios)
    {
        ids_usuarios[usuarios] = sqlite3_column_int(stmt, 0);
        total_pedidos[usuarios] = sqlite3_column_int(stmt,1);
        usuarios++;
    }
    sqlite3_finalize(stmt);
    return usuarios;

}

double obtenerValorMedioPedido(sqlite3 *db)
{
    const char *sql = "SELECT AVG(total) FROM (SELECT SUM(PD.cantidad * PD.precio_unitario) as total FROM PedidoDetalle PD GROUP BY PD.id_pedido);";
    sqlite3_stmt *stmt;
    double valor = -1;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        valor = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return valor;
}

int obtenerRobotsActivos(sqlite3 *db) {
    const char *sql = "SELECT COUNT(*) FROM Robot WHERE estado = 2;"; //2 = Disponible
    sqlite3_stmt *stmt;
    int disponibles = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        disponibles = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return disponibles;
}
