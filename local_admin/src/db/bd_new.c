#include "bd_new.h"
#include <stdio.h>

#include "config.h"

static sqlite3* db = NULL;

int init_db(void)
{
    if (db != NULL)
    {
        // Already initialized
        return SQLITE_OK;
    }

    if (sqlite3_open("../bd.db", &db) != SQLITE_OK)
    {
        printf("Error abriendo la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        db = NULL;
        return 1;
    }

    if (create_db_if_not_exists())
    {
        crear_tablas();
        generar_datos_prueba();
    }

    return SQLITE_OK;
}

void close_db(void)
{
    if (sqlite3_close(db) != SQLITE_OK)
    {
        printf("¡Error cerrando la base de datos!\n");
    }
}

sqlite3* get_db(void)
{
    if (db == NULL)
    {
        init_db();
    }
    return db;
}

// Ejemplo de función auxiliar
int execute_query(const char* sql, sqlite3_stmt** stmt) {
    if (db == NULL) {
        init_db();
    }

    int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    return 0;
}

int crear_tablas()
{
    char* zErrMsg = 0;

    const char* crearUsuario = "CREATE TABLE IF NOT EXISTS Usuario ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "dni TEXT NOT NULL UNIQUE,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL);";


    int rc = sqlite3_exec(db, crearUsuario, NULL, NULL, &zErrMsg);
    //Ejecuta el statement y si se ejecuta correctamente rc resulta en 0 (SQLITE_OK)
    if (rc != SQLITE_OK)
    {
        printf("Error SQL tabla Usuario: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    const char* crearPlato = "CREATE TABLE IF NOT EXISTS Plato ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nombre TEXT UNIQUE NOT NULL,"
        "descripcion TEXT,"
        "precio REAL NOT NULL CHECK(precio>0),"
        "disponible INTEGER NOT NULL DEFAULT 1 CHECK(disponible IN (0, 1)));"; // 1 no disponible, 0 disponible

    rc = sqlite3_exec(db, crearPlato, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf("Error SQL tabla Plato: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    const char* crearPedido = "CREATE TABLE IF NOT EXISTS Pedido ("
        "id_pedido INTEGER PRIMARY KEY AUTOINCREMENT,"
        "id_usuario INTEGER NOT NULL,"
        "direccion TEXT NOT NULL,"
        "fecha TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "estado INT NOT NULL CHECK(estado IN (0,1,2))," //0->En cola, 1->En camino, 2->entregado
        "FOREIGN KEY(id_usuario) REFERENCES Usuario(id) ON DELETE CASCADE);";

    rc = sqlite3_exec(db, crearPedido, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf("Error SQL tabla Pedido: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    const char* crearRobot = "CREATE TABLE IF NOT EXISTS Robot ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nombre TEXT NOT NULL,"
        "estado INTEGER NOT NULL CHECK(estado IN (0,1,2)) DEFAULT 2," //0->Ocupado, 1->Mantenimiento, 2->Disponible
        "pedido_actual INTEGER DEFAULT -1," //al crearse no tiene pedido asignado
        "FOREIGN KEY(pedido_actual) REFERENCES Pedido(id_pedido) ON DELETE CASCADE);";

    rc = sqlite3_exec(db, crearRobot, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf("Error SQL tabla Robot: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    const char* crearPedidoDetalle = "CREATE TABLE IF NOT EXISTS PedidoDetalle ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "id_pedido INTEGER NOT NULL,"
        "id_plato INTEGER NOT NULL,"
        "cantidad INTEGER NOT NULL,"
        "precio_unitario REAL NOT NULL,"
        "FOREIGN KEY(id_pedido) REFERENCES Pedido(id_pedido) ON DELETE CASCADE,"
        "FOREIGN KEY(id_plato) REFERENCES Plato(id));";

    rc = sqlite3_exec(db, crearPedidoDetalle, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        printf("Error SQL tabla Pedido Detalle: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }


    printf("Tablas creadas\n");
    return 0;
}

int generar_datos_prueba() {
    char* zErrMsg = 0;
    sqlite3* db = get_db();

    // Insertar usuarios de prueba
    const char* usuarios =
        "INSERT OR IGNORE INTO Usuario (dni, username, password) VALUES "
        "('12345678A', 'usuario1', 'pass123'), "
        "('87654321B', 'usuario2', 'pass456'), "
        "('11111111C', 'admin', 'admin123');";

    // Insertar platos de prueba
    const char* platos =
        "INSERT OR IGNORE INTO Plato (nombre, descripcion, precio, disponible) VALUES "
        "('Paella', 'Arroz con mariscos y verduras', 15.99, 1), "
        "('Pizza Margherita', 'Pizza con tomate y mozzarella', 12.50, 1), "
        "('Hamburguesa', 'Carne de ternera con queso', 9.99, 1);";

    // Insertar robots de prueba
    const char* robots =
        "INSERT OR IGNORE INTO Robot (nombre, estado) VALUES "
        "('R2D2', 2), "
        "('C3PO', 2), "
        "('BB8', 1);";

    // Insertar pedidos de prueba
    const char* pedidos =
        "INSERT OR IGNORE INTO Pedido (id_usuario, direccion, estado) VALUES "
        "(1, 'Calle Mayor 1', 0), "
        "(2, 'Plaza España 2', 1);";

    // Insertar detalles de pedidos
    const char* detalles =
        "INSERT OR IGNORE INTO PedidoDetalle (id_pedido, id_plato, cantidad, precio_unitario) VALUES "
        "(1, 1, 2, 15.99), "
        "(1, 2, 1, 12.50), "
        "(2, 3, 3, 9.99);";

    // Ejecutar las inserciones
    int rc = sqlite3_exec(db, usuarios, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        printf("Error insertando usuarios: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return rc;
    }

    rc = sqlite3_exec(db, platos, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        printf("Error insertando platos: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return rc;
    }

    rc = sqlite3_exec(db, robots, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        printf("Error insertando robots: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return rc;
    }

    rc = sqlite3_exec(db, pedidos, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        printf("Error insertando pedidos: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return rc;
    }

    rc = sqlite3_exec(db, detalles, NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        printf("Error insertando detalles de pedidos: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return rc;
    }

    printf("Datos de prueba generados correctamente\n");
    return SQLITE_OK;
}