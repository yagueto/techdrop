#include <stdlib.h>
#include <stdio.h>
#include "bd_new.h"
#include "models/pedido.h"

Pedido* get_pedido(int id) {
    sqlite3_stmt* stmt;
    char* sql = "SELECT id_pedido, id_usuario, direccion, fecha,estado FROM Pedido WHERE id_pedido=?";
    int result = execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error preparando la consulta: %s", sqlite3_errmsg(get_db()));
        return NULL;
    }

    result = sqlite3_bind_int(stmt, 1, id);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la bd: %s", sqlite3_errmsg(get_db()));
        return NULL;
    }

    result = sqlite3_step(stmt);

    if (result != SQLITE_ROW)
    {
        printf("No existe este pedido");
        return NULL;
    }
    //falta lista de platos(crear en bd_pedidoDetalle funcion para conseguir
    const int id_pedido = sqlite3_column_int(stmt, 0);
    const int id_usuario = sqlite3_column_int(stmt, 1);
    char* direccion = (char*)sqlite3_column_text(stmt, 2);
    char* f = (char*)sqlite3_column_text(stmt, 3);
    const time_t fecha = string_a_time(f);
    const int estado = sqlite3_column_int(stmt, 4);
    Pedido* pedido = crearPedido(0,id_usuario, direccion, fecha, estado);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK)
    {
        printf("Error finalizando el statement: %s \n", sqlite3_errmsg(get_db()));
    }

    return pedido;
}
int pedidoCola() {
    sqlite3_stmt* stmt;
    char *sql = "SELECT id_pedido FROM Pedido WHERE estado = 0 ORDER BY id_pedido ASC;";
    int id = -1;

    if (sqlite3_prepare_v2(get_db(), sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf( "Error preparando consulta: %s\n", sqlite3_errmsg(get_db()));
        return -1;
    }


    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    return id;
}
int actualizarEstadoPedido(Pedido* pedido, int estado) {
    if (estado <0 || estado > 2) {
        printf("Estado invalido\n");
    }

    pedido->estado = estado;
    sqlite3_stmt *stmt;
    char *sql = "UPDATE Pedido SET estado = ? WHERE id_pedido = ?;";

    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(get_db()));
        return result;
    }

    sqlite3_bind_int(stmt, 1, estado);
    sqlite3_bind_int(stmt, 2, pedido->id);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error actualizando pedido: %s\n", sqlite3_errmsg(get_db()));
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;

}