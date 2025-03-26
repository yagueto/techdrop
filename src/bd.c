//
// Created by maddi.esparta on 25/03/2025.
//
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include "bd.h"
#include "estructuras.h"
#include "estadisticas.h"
int crearTablas(sqlite3* db) {

   char *zErrMsg = 0;

   const char * crearUsuario = "CREATE TABLE IF NOT EXISTS Usuario ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "dni TEXT NOT NULL UNIQUE,"
                   "nombre TEXT NOT NULL,"
                   "apellido TEXT NOT NULL,"
                   "direccion TEXT NOT NULL,"
                   "municipio TEXT NOT NULL,"
                   "mail TEXT NOT NULL,"
                   "fecha_nac TEXT NOT NULL,"
                   "username TEXT NOT NULL UNIQUE,"
                   "password TEXT NOT NULL);";


   int rc = sqlite3_exec(db, crearUsuario, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Usuario: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
   const char * crearPlato = "CREATE TABLE IF NOT EXISTS Plato ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "nombre TEXT UNIQUE NOT NULL,"
                   "descripcion TEXT,"
                   "precio REAL NOT NULL CHECK(precio>0),"
                   "disponible INTEGER NOT NULL DEFAULT 1 CHECK(disponible IN (0, 1)));";  // 1 no disponible, 0 disponible


   rc = sqlite3_exec(db, crearPlato, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Plato: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
   const char * crearPedido = "CREATE TABLE IF NOT EXISTS Pedido ("
                   "id_pedido INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "id_usuario INTEGER NOT NULL,"
                   "direccion TEXT NOT NULL,"
                   "fecha TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                   "estado TEXT NOT NULL,"
                   "FOREIGN KEY(id_usuario) REFERENCES Usuario(id));";

   rc = sqlite3_exec(db, crearPedido, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Pedido: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
   const char * crearRobot = "CREATE TABLE IF NOT EXISTS Robot ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "estado TEXT NOT NULL CHECK(estado IN ('Disponible', 'Ocupado', 'Siesta')),"
                   "descripcion TEXT,"
                   "pedido_actual INTEGER NOT NULL,"
                   "FOREIGN KEY(pedido_actual) REFERENCES Pedido(id_pedido) ON DELETE CASCADE);";


   rc = sqlite3_exec(db, crearRobot, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Robot: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
   const char * crearPedidoDetalle = "CREATE TABLE IF NOT EXISTS PedidoDetalle ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "id_pedido INTEGER NOT NULL,"
                   "id_plato INTEGER NOT NULL,"
                   "cantidad INTEGER NOT NULL,"
                   "precio_unitario REAL NOT NULL,"
                   "FOREIGN KEY(id_pedido) REFERENCES Pedido(id_pedido),"
                   "FOREIGN KEY(id_plato) REFERENCES Plato(id));";
   rc = sqlite3_exec(db, crearPedidoDetalle, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Pedido Detalle: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }


   printf("Tablas creadas\n") ;
   return 0;
}

Pedido* cargarPedidos(sqlite3 *db, int *total)
{
    const char *sql = "SELECT * FROM Pedido;";
    sqlite3_stmt *stmt;
    *total = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    //Calcular capacidad
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        (*total)++;
    };

    if (*total == 0) {
        sqlite3_finalize(stmt);
        return NULL; //No hay pedidos
    }
    sqlite3_reset(stmt);

    //Crear array en memoria
    Pedido *pedidos = crearArrayPedidos(*total);
    if (!pedidos) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    //Cargar datos
    for (int i = 0; sqlite3_step(stmt) == SQLITE_ROW; i++) {
        pedidos[i].id_pedido = sqlite3_column_int(stmt, 0);
        pedidos[i].id_usuario = sqlite3_column_int(stmt, 1);
        strncpy(pedidos[i].direccion, (const char*)sqlite3_column_text(stmt, 2), sizeof(pedidos[i].direccion) - 1);//strncpy para seguridad
        strncpy(pedidos[i].fecha, (const char*)sqlite3_column_text(stmt, 3), sizeof(pedidos[i].fecha) - 1);
        strncpy(pedidos[i].estado, (const char*)sqlite3_column_text(stmt, 4),sizeof(pedidos[i].estado) - 1);
        //Que acaben en nulo
        pedidos[i].direccion[sizeof(pedidos[i].direccion) - 1] = '\0';
        pedidos[i].fecha[sizeof(pedidos[i].fecha) - 1] = '\0';
        pedidos[i].estado[sizeof(pedidos[i].estado) - 1] = '\0';
    }
    sqlite3_finalize(stmt);
    return pedidos;
}
Plato* cargarPlatos(sqlite3 *db, int *total)
{
    const char *sql = "SELECT * FROM Plato;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Error en la consulta de platos: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    //Calcular capacidad
    *total = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        (*total)++;
    }
    sqlite3_reset(stmt);

    //Crear array en memoria
    Plato *platos = crearArrayPlatos(*total);
    if (!platos) return NULL;

    //Cargar datos
    for (int i = 0; sqlite3_step(stmt) == SQLITE_ROW; i++)
    {
        platos[i].id_plato = sqlite3_column_int(stmt, 0);
        strncpy(platos[i].nombre, (const char*)sqlite3_column_text(stmt, 1), 50);
        platos[i].precio = sqlite3_column_double(stmt, 3);
    }
    sqlite3_finalize(stmt);
    return platos;
}
Robot* cargarRobots(sqlite3 *db, int *total)
{
    const char *sql = "SELECT * FROM Robot;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Error en la consulta de robots: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    //Calcular capacidad
    *total = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        (*total)++;
    }
    sqlite3_reset(stmt);

    //Crear array en memoria
    Robot *robots = crearArrayRobots(*total);
    if (!robots) return NULL;

    //Cargar datos
    for (int i = 0; sqlite3_step(stmt) == SQLITE_ROW; i++)
    {
        robots[i].id_robot = sqlite3_column_int(stmt, 0);
        strncpy(robots[i].estado, (const char*)sqlite3_column_text(stmt, 1), 20);
        robots[i].pedido_actual = sqlite3_column_int(stmt, 3);
    }
    sqlite3_finalize(stmt);
    return robots;
}

void datosPruebaPedido(sqlite3 *db) {
    char *sql = "INSERT INTO Pedido (id_usuario, direccion, estado) VALUES "
                "(1, 'Abando 123', 'Entregado'), "
                "(2, 'Gran Via 456', 'En proceso');";
    char *errMsg;
    if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Error insertando datos: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}
