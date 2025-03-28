//
// Created by maddi.esparta on 25/03/2025.
//
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include "bd.h"

#include <stdlib.h>

#include "estructuras/estructuras.h"
#include "estadisticas.h"
int crearTablas(sqlite3* db) {

   char *zErrMsg = 0;

   const char * crearUsuario = "CREATE TABLE IF NOT EXISTS Usuario ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "dni TEXT NOT NULL UNIQUE,"
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
                   "estado INT NOT NULL CHECK(estado IN (0,1,2))," //0->En cola, 1->En camino, 2->entregado
                   "FOREIGN KEY(id_usuario) REFERENCES Usuario(id));";

   rc = sqlite3_exec(db, crearPedido, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
       printf("Error SQL tabla Pedido: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }
   const char * crearRobot = "CREATE TABLE IF NOT EXISTS Robot ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "estado INTEGER NOT NULL CHECK(estado IN (0,1,2)) DEFAULT 2," //0->Ocupado, 1->Mantenimiento, 2->Disponible
                   "pedido_actual INTEGER DEFAULT -1," //al crearse no tiene pedido asignado
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

//Funciones para cargar datos de la bd a un array
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
        strncpy(pedidos[i].direccion, (const char*)sqlite3_column_text(stmt, 2), sizeof(pedidos[i].direccion) - 1);
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
        robots[i].estado = sqlite3_column_int(stmt, 1);
        robots[i].pedido_actual = sqlite3_column_int(stmt, 3);
    }
    sqlite3_finalize(stmt);
    return robots;
}

//Actualizar el pedido en la bd
int actualizarPedido(sqlite3 *db, const Pedido *pedido)
{
    const char *sql = "UPDATE Pedido SET id_usuario = ?, direccion = ?, fecha = ?, estado = ? WHERE id_pedido = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar actualizacion: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    //Parametros
    sqlite3_bind_int(stmt, 1, pedido->id_usuario);
    sqlite3_bind_text(stmt, 2, pedido->direccion, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, pedido->fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, pedido->estado, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, pedido->id_pedido);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        fprintf(stderr, "Error al actualizar pedido: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    return 0;
}

int actualizarArrayPedidos(sqlite3 *db, const Pedido *pedidos, int total)
{
    if (!pedidos || total <= 0) {
        fprintf(stderr, "Array de pedidos vacio.\n");
        return -1;
    }

    int pedidosCargados = 0;
    for (int i = 0; i < total; i++) {
        if (actualizarPedido(db, &pedidos[i]) == 0) {
            pedidosCargados++;
        } else {
            fprintf(stderr, "Error al actualizar pedido con ID: %d\n", pedidos[i].id_pedido);
        }
    }

    if (pedidosCargados == total) {
        printf("Pedidos actualizados.\n");
        return 0;
    } else {
        fprintf(stderr, "Se han actualizado %d de %d pedidos.\n", pedidosCargados, total);
        return -1;
    }
}

void datosPrueba(sqlite3 *db) {
    char *errMsg = 0;
    int rc;

    rc = sqlite3_exec(db, "BEGIN IMMEDIATE TRANSACTION;", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "BEGIN TRANSACTION failed: %s\n", errMsg);
        sqlite3_free(errMsg);
        return;
    }

    //Limpiamos
    const char *cleanup[] = {
        "DELETE FROM PedidoDetalle",
        "DELETE FROM Pedido",
        "DELETE FROM Robot",
        "DELETE FROM Plato",
        "DELETE FROM Usuario"
    };

    for (int i = 0; i < 5; i++) {
        rc = sqlite3_exec(db, cleanup[i], NULL, NULL, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cleanup fallado para %s: %s\n",
                    (const char*[]){"PedidoDetalle","Pedido","Robot","Plato","Usuario"}[i],
                    errMsg);
            sqlite3_free(errMsg);
            sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
            return;
        }
    }

    //Datos usuarios
    const char *sqlUsuarios =
        "INSERT INTO Usuario (dni, username, password) VALUES "
        "('12345678A', 'cliente1', 'cliente1pass'), "
        "('87654321B', 'cliente2', 'cliente2pass'), "
        "('11111111C', 'admin', 'adminpass');";

    //Datos platos
    const char *sqlPlatos =
        "INSERT INTO Plato (nombre, descripcion, precio, disponible) VALUES "
        "('Paella', 'Paella valenciana tradicional', 12.50, 1), "
        "('Hamburguesa', 'Con queso y bacon', 8.90, 1), "
        "('Ensalada César', 'Con pollo y aderezo especial', 7.20, 1), "
        "('Tarta de chocolate', 'Postre casero', 4.50, 1), "
        "('Agua mineral', 'Botella 50cl', 1.80, 1), "
        "('Coca-Cola', 'Lata 33cl', 2.00, 0);";

    //Datios robots
    const char *sqlRobots =
        "INSERT INTO Robot (estado, pedido_actual) VALUES "
        "(2, -1), "  // 2 = Disponible
        "(0, 1), "   // 0 = Ocupado
        "(2, -1), "  // 2 = Disponible
        "(1, -1);";  // 1 = Mantenimiento

    //Datos pedidos
    const char *sqlPedidos =
        "INSERT INTO Pedido (id_usuario, direccion, estado) VALUES "
        "(1, 'Calle Mayor 5, 3ºB', 2), "
        "(2, 'Avenida Libertad 12', 1), "
        "(1, 'Plaza España 7', 0);";

    //Datos detalles de pedidos
    const char *sqlDetalles =
        "INSERT INTO PedidoDetalle (id_pedido, id_plato, cantidad, precio_unitario) VALUES "
        "(1, 1, 2, 12.50), "  // 2 paellas en pedido 1
        "(1, 5, 3, 1.80), "    // 3 aguas en pedido 1
        "(2, 2, 1, 8.90), "    // 1 hamburguesa en pedido 2
        "(2, 3, 1, 7.20), "    // 1 ensalada en pedido 2
        "(3, 4, 4, 4.50);";    // 4 tartas en pedido 3

    //Ejecutar
    const char *inserciones[] = {sqlUsuarios, sqlPlatos, sqlRobots, sqlPedidos, sqlDetalles};
    const char *nombresTablas[] = {"Usuario", "Plato", "Robot", "Pedido", "PedidoDetalle"};

    for (int i = 0; i < 5; i++) {
        if (sqlite3_exec(db, inserciones[i], NULL, NULL, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Error insertando datos en %s: %s\n", nombresTablas[i], errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Datos de prueba insertados en %s\n", nombresTablas[i]);
        }
    }

    rc = sqlite3_exec(db, "COMMIT;", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "COMMIT failed: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("All data committed successfully!\n");
    }
}

//Funciones para las estadisticas(SQL)
int obtenerTotalPedidosPorDia(sqlite3 *db, const char *fecha) {
    if (!db || !fecha) {
        fprintf(stderr, "Parámetros inválidos\n");
        return -1;
    }

    const char *sql = "SELECT COUNT(*) FROM Pedido WHERE date(fecha) = date(?);";
    sqlite3_stmt *stmt = NULL;
    int total = -1;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error preparando consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    rc = sqlite3_bind_text(stmt, 1, fecha, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error vinculando parámetro: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    //Ejecutar
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        total = sqlite3_column_int(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error ejecutando consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return total;
}

int obtenerZonasPopulares(sqlite3 *db, char zonas[][100], int *contadores, int numZonas) {
    const char *sql = "SELECT direccion, COUNT(*) FROM Pedido GROUP BY direccion ORDER BY COUNT(*) DESC LIMIT ?;";
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
        hora_pico = atoi((const char *)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return hora_pico;
}

int obtenerPlatosMasVendidos(sqlite3 *db, int *ids_platos, int *cantidades, int numplatos) {
    const char *sql = "SELECT id_plato, SUM(cantidad) FROM PedidoDetalle GROUP BY id_plato ORDER BY SUM(cantidad) DESC LIMIT ?;";
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