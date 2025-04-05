#include <stdlib.h>
#include <stdio.h>
#include "bd_new.h"
#include "bd.h"
#include "../estructuras/usuario.h"


int eliminarUsuario(Usuario *usuario) {
    char *errMsg = 0;
    sqlite3_stmt *stmt;

    char sql[] = "DELETE FROM Usuario WHERE dni = ?";


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error preparing statement (DELETE)\n");
        return result;
    }


    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;

}
int insertarUsuario(Usuario usuario) {
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO Usuario (id, dni, username, password) VALUES (NULL, ?, ?, ?)";


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement\n");
        return result;
    }


    sqlite3_bind_text(stmt, 1, usuario.dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario.contraseña, -1, SQLITE_STATIC);


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        fprintf(stderr, "Error executing statement\n");
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;


}
