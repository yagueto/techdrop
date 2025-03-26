//
// Created by maddi.esparta on 25/03/2025.
//
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include "bd.h"
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
   sqlite3_close(db);
   return 0;
}
