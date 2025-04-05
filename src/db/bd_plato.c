#include <stdlib.h>
#include "bd_plato.h"

#include <stdio.h>

#include "bd.h"
#include "bd_new.h"

PlatoResult get_platos()
{
    PlatoResult plato_result;
    plato_result.count = 0;
    int capacity = 2;

    sqlite3_stmt* stmt;
    Plato** platos = malloc(capacity * sizeof(Plato*));

    plato_result.platos = platos;

    const char* sql = "SELECT * FROM Plato;";
    int result = execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        return plato_result;
    }
    do
    {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW)
        {
            if (plato_result.count >= capacity)
            {
                capacity *= 2;
                Plato** temp = realloc(platos, capacity * sizeof(Plato*));
                if (temp == NULL)
                {
                    // Free individual platos first
                    for (int i = 0; i < plato_result.count; i++)
                    {
                        free_plato(platos[i]);
                    }
                    free(platos);
                    sqlite3_finalize(stmt);
                    plato_result.platos = NULL;
                    plato_result.count = 0;
                    return plato_result;
                }
                platos = temp;
                plato_result.platos = platos;
            }
            int id = sqlite3_column_int(stmt, 0);
            const char* nombre = (const char*)sqlite3_column_text(stmt, 1);
            const char* descripcion = (const char*)sqlite3_column_text(stmt, 2);
            float precio = (float)sqlite3_column_double(stmt, 3);
            int disponible = sqlite3_column_int(stmt, 4);
            platos[plato_result.count] = crear_plato(id, nombre, descripcion, precio, disponible);
            plato_result.count++;
        }
    }
    while (result == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return plato_result;
}

Plato* get_plato_by_id(int id)
{
    sqlite3_stmt* stmt;
    char* sql = "SELECT Nombre, Descripcion, Precio, Disponible FROM Plato WHERE ID=?";
    int result = execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error preparando la consulta: %s", sqlite3_errmsg(get_db()));
        return NULL;
    }

    result = sqlite3_bind_int(stmt, 1, id);
    if (result != SQLITE_OK)
    {
        printf("Error parametrizando la consulta: %s", sqlite3_errmsg(get_db()));
        return NULL;
    }

    result = sqlite3_step(stmt);

    if (result != SQLITE_ROW)
    {
        return NULL;
    }
    const char* nombre = (char*)sqlite3_column_text(stmt, 0);
    const char* descripcion = (char*)sqlite3_column_text(stmt, 1);
    const float precio = (float)sqlite3_column_double(stmt, 2);
    const int disponible = sqlite3_column_int(stmt, 3);
    Plato* plato = crear_plato(id, nombre, descripcion, precio, disponible);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK)
    {
        printf("Error finalizando el statement: %s \n", sqlite3_errmsg(get_db()));
    }

    return plato;
}

int guardar_plato(Plato* plato)
{
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Plato(nombre, descripcion, precio, disponible) VALUES (?, ?, ?, ?);";
    int result = execute_query(sql, &stmt);

    if (result != SQLITE_OK)
    {
        printf("Error preparando la consulta: %s", sqlite3_errmsg(get_db()));
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, plato->nombre, -1, SQLITE_STATIC);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la BD: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    result = sqlite3_bind_text(stmt, 2, plato->descripcion, -1, SQLITE_STATIC);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la BD: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    result = sqlite3_bind_double(stmt, 3, plato->precio);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la BD: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    result = sqlite3_bind_int(stmt, 4, plato->disponible);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la BD: %s", sqlite3_errmsg(get_db()));
        return result;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error insertando en la BD: %s \n", sqlite3_errmsg(get_db()));
        return result;
    }

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK)
    {
        printf("Error finalizando el statement: %s \n", sqlite3_errmsg(get_db()));
        return result;
    }

    return SQLITE_OK;
}

int eliminar_plato(Plato* plato)
{
    sqlite3_stmt* stmt;
    char* sql = "DELETE FROM Plato WHERE ID=?";
    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        printf("Error al preparar el statement: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    result = sqlite3_bind_int(stmt, 1, plato->id);
    if (result != SQLITE_OK)
    {
        printf("Error al eliminar el plato: %s", sqlite3_errmsg(get_db()));
        return result;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error al eliminar el plato: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK)
    {
        printf("Error al finalizar el statement: %s", sqlite3_errmsg(get_db()));
        return result;
    }
    return SQLITE_OK;
}

void free_plato_result(PlatoResult* result)
{
    if (result->platos == NULL) return;

    for (int i = 0; i < result->count; i++)
    {
        free_plato(result->platos[i]);
    }
    free(result->platos);
    result->platos = NULL;
    result->count = 0;
}
