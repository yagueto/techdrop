#include <stdio.h>
#include "bd.h"
#include "menu.h"
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    // abrir o crear base de datos
    if (sqlite3_open("bd.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la BD: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // crear tablas si no existen
    if (crearTablas(db) != 0) {
        fprintf(stderr, "Error al crear tablas\n");
        sqlite3_close(db);
        return 1;
    }

    crearTablas(db);
    //datosPruebaPedido(db);
    initializeMenus();
    sqlite3_close(db);
    return 0;
}
