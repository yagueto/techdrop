//
// Created by maddi.esparta on 29/05/2025.
//

#include "bd.h"
#include <iostream>



bd* bd::instance=nullptr;


bd::bd():   db(NULL) {}

bd::~bd() {
    cerrar_conexion();
}
bd* bd::get_instance() {
    if (!instance) {
        instance = new bd();
    }
    return instance;
}

void bd::abrir_conexion(const std::string&ruta) { //config.getPath
    if (db != NULL) return;

    if (sqlite3_open(ruta.c_str(), &db) != SQLITE_OK) {
        std::cout << "Error abriendo la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        db=NULL;

    }else {
        std::cout << "Base de datos abierta correctamente." << std::endl;
    }
}
sqlite3 *bd::get_db() {
    return db;
}
void bd::cerrar_conexion() {
    if (db) {
        sqlite3_close(db);
        db=NULL;
        std::cout << "Base de datos cerrada correctamente." << std::endl;
    }
}


int bd::execute_query(const std::string&sql) {
   char* zErrMsg = 0;
    int rc=sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error SQL: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    return rc;
}
sqlite3_stmt* bd::preparar_consulta(const std::string&sql) {
    sqlite3_stmt* stmt = NULL;
    int rc = sqlite3_prepare_v2(db,sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cout << "Error en preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return NULL;

    }
    return stmt;
}