#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bd_new.h"
#include "bd.h"
#include <models/usuario.h>


Usuario* obtenerUsuario(char *param, char* type) {
    sqlite3_stmt *stmt;

    char *sql;
    if (strcmp(type, "dni") == 0) {
        sql = "SELECT * FROM Usuario WHERE dni = ?";
    } else if (strcmp(type, "username") == 0) {
        sql = "SELECT * FROM Usuario WHERE username = ?";
    } else {
        printf("Tipo de dato erroneo\n");
        return NULL;
    }


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error preparing satement (SELECT)\n");
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, param, -1, SQLITE_STATIC);
    result = sqlite3_step(stmt);

    if (result != SQLITE_ROW) {
        if (result == SQLITE_DONE) {
            printf("Usuario no encontrado en la base de datos\n");
        } else {
            printf("Error ejecutando consulta: %s\n", sqlite3_errmsg(get_db()));
        }
        sqlite3_finalize(stmt);
        return NULL;
    }

    Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
    usuario->dni = strdup((const char*)sqlite3_column_text(stmt, 0));
    usuario->nombre = strdup((const char*)sqlite3_column_text(stmt, 1));
    usuario->contraseña = strdup((const char*)sqlite3_column_text(stmt, 2));

    sqlite3_finalize(stmt);
    return usuario;
}

int eliminarUsuario(char *dni) {
    sqlite3_stmt *stmt;

    char sql[] = "DELETE FROM Usuario WHERE dni = ?";


    int result = execute_query(sql, &stmt);

    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);

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
