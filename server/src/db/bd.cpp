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
bd& bd::get_instance() {
    static bd instance;
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

void bd::cerrar_conexion() {
    if (db) {
        sqlite3_close(db);
        db=NULL;
        std::cout << "Base de datos cerrada correctamente." << std::endl;
    }
}

int bd::execute_query(const std::string sql, sqlite3_stmt** stmt) {
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    return 0;
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