#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bd_new.h"
#include <models/usuario.h>


Usuario* obtenerUsuario(char* param, char* type)
{
    sqlite3_stmt* stmt;

    char* sql;
    if (strcmp(type, "dni") == 0)
    {
        sql = "SELECT * FROM Usuario WHERE dni = ?;";
    }
    else if (strcmp(type, "username") == 0)
    {
        sql = "SELECT * FROM Usuario WHERE username = ?;";
    }
    else
    {
        printf("Tipo de dato erroneo\n");
        return NULL;
    }


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        printf("Error preparing satement (SELECT)\n");
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, param, -1, SQLITE_STATIC);
    result = sqlite3_step(stmt);

    if (result != SQLITE_ROW)
    {
        if (result != SQLITE_DONE)
        {
            printf("Error ejecutando consulta: %s\n", sqlite3_errmsg(get_db()));
        }
        sqlite3_finalize(stmt);
        return NULL;
    }

    Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
    usuario->dni = strdup((const char*)sqlite3_column_text(stmt, 1));
    usuario->nombre = strdup((const char*)sqlite3_column_text(stmt, 2));
    usuario->contraseña = strdup((const char*)sqlite3_column_text(stmt, 3));

    sqlite3_finalize(stmt);
    return usuario;
}

int eliminarUsuario(Usuario* usuario)
{
    sqlite3_stmt* stmt;

    char sql[] = "DELETE FROM Usuario WHERE dni = ?;";


    int result = execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

int insertarUsuario(Usuario* usuario)
{
    sqlite3_stmt* stmt;
    char sql[] = "INSERT INTO Usuario (id, dni, username, password) VALUES (NULL, ?, ?, ?);";


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "Error executing statement\n");
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->contraseña, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE\n");
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

Usuario* listaUsuarios() {
    sqlite3_stmt* stmt;
    char sql[] = "SELECT * FROM Usuario;";
    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK) {
        printf("Error ejecutando SELECT\n");
        return NULL;
    }

    int capacity = 10;
    int count = 0;
    Usuario* usuarios = (Usuario*)malloc(capacity * sizeof(Usuario));

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        if (count >= capacity) {
            capacity *= 2;
            usuarios = (Usuario*)realloc(usuarios, capacity * sizeof(Usuario));
        }
        usuarios[count].dni = strdup((const char*)sqlite3_column_text(stmt, 1));
        usuarios[count].nombre = strdup((const char*)sqlite3_column_text(stmt, 2));
        usuarios[count].contraseña = strdup((const char*)sqlite3_column_text(stmt, 3));
        count++;
    }

    if (result != SQLITE_DONE) {
        printf("Error iterando sobre los resultados: %s\n", sqlite3_errmsg(get_db()));
    }

    sqlite3_finalize(stmt);

    usuarios[count].dni = NULL;
    return usuarios;
}
