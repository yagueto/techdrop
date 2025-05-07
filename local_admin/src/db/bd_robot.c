#include "bd_robot.h"
#include "db/bd_new.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "models/pedido.h"


int insertarRobot(Robot* robot)
{
    sqlite3_stmt* stmt;
    char sql[] = "INSERT INTO Robot (id, nombre, estado, pedido_actual) VALUES (NULL, ?, ?, ?)";


    int result = sqlite3_prepare_v2(get_db(), sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(get_db()));
        return result;
    }


    sqlite3_bind_text(stmt, 1, robot->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, robot->estado);
    sqlite3_bind_int(stmt, 3, robot->pedido_actual);


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(get_db()));
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

int eliminarRobot(int id)
{
    sqlite3_stmt* stmt;


    char sql[] = "DELETE FROM Robot WHERE id = ?";


    int result = sqlite3_prepare_v2(get_db(), sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        printf("Error preparing statement (DELETE): %s\n", sqlite3_errmsg(get_db()));
        return result;
    }


    sqlite3_bind_int(stmt, 1, id);


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error executing DELETE: %s\n", sqlite3_errmsg(get_db()));
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;
}


Robot* get_robot(int id)
{
    sqlite3_stmt* stmt;
    char* sql = "SELECT nombre, estado,pedido_actual FROM Robot WHERE id=?";
    int result = execute_query(sql, &stmt);


    if (result != SQLITE_OK)
    {
        printf("Error preparando la consulta: %s\n", sqlite3_errmsg(get_db()));
        return NULL;
    }


    result = sqlite3_bind_int(stmt, 1, id);
    if (result != SQLITE_OK)
    {
        printf("Error insertando en la bd: %s\n", sqlite3_errmsg(get_db()));
        sqlite3_finalize(stmt);
        return NULL;
    }


    result = sqlite3_step(stmt);
    if (result != SQLITE_ROW)
    {
        if (result == SQLITE_DONE)
        {
            printf("Robot  no encontrado\n");
        }
        else
        {
            printf("Error ejecutando consulta: %s\n", sqlite3_errmsg(get_db()));
        }
        sqlite3_finalize(stmt);
        return NULL;
    }
    Robot* robot = (Robot*)malloc(sizeof(Robot));
    const char* nombre = (char*)sqlite3_column_text(stmt, 0);
    const int estado = sqlite3_column_int(stmt, 1);
    const int pedido_actual = sqlite3_column_int(stmt, 2);


    robot->id = id;
    robot->nombre = strdup(nombre);
    robot->estado = estado;
    robot->pedido_actual = pedido_actual;


    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK)
    {
        printf("Error finalizando el statement: %s \n", sqlite3_errmsg(get_db()));
    }


    return robot;
}

int actualizarEstadoRobot(Robot* robot, int estado)
{
    if (estado < 0 || estado > 2)
    {
        printf("Estado invalido\n");
    }
    robot->estado = estado;
    sqlite3_stmt* stmt;
    char* sql = "UPDATE Robot SET estado = ? WHERE id = ?;";


    int result = execute_query(sql, &stmt);
    if (result != SQLITE_OK)
    {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(get_db()));
        return result;
    }


    sqlite3_bind_int(stmt, 1, estado);
    sqlite3_bind_int(stmt, 2, robot->id);


    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error actualizando estado del robot: %s\n", sqlite3_errmsg(get_db()));
        sqlite3_finalize(stmt);
        return result;
    }


    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

RobotLista* get_robotLista()
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, nombre, estado, pedido_actual FROM Robot;";
    int cantidad = 0;
    if (sqlite3_prepare_v2(get_db(), sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(get_db()));
        return NULL;
    }


    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        (cantidad)++;
    }


    if (cantidad == 0)
    {
        sqlite3_finalize(stmt);
        return NULL;
    }


    RobotLista* robotLista = (RobotLista*)malloc(sizeof(RobotLista));
    if (robotLista == NULL)
    {
        sqlite3_finalize(stmt);
        free_robotLista(robotLista);
        return NULL;
    }
    Robot** lista = malloc(cantidad * sizeof(Plato*));
    if (lista == NULL)
    {
        free_robotLista(robotLista);
        sqlite3_finalize(stmt);
        return NULL;
    }
    robotLista->cantidad = cantidad;


    sqlite3_reset(stmt);


    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && i < cantidad)
    {
        lista[i] = (Robot*)malloc(sizeof(Robot));
        if (lista[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(lista[j]);
            }
            free(lista);
            free_robotLista(robotLista);
            sqlite3_finalize(stmt);
            return NULL;
        }
        lista[i]->id = sqlite3_column_int(stmt, 0);
        const char* nombre = (const char*)sqlite3_column_text(stmt, 1);
        lista[i]->nombre = strdup(nombre);
        lista[i]->estado = sqlite3_column_int(stmt, 2);
        lista[i]->pedido_actual = sqlite3_column_int(stmt, 3);
        robotLista->lista = lista;
        i++;
    }


    sqlite3_finalize(stmt);

    return robotLista;
}

void free_robotLista(RobotLista* robotLista)
{
    if (robotLista->lista == NULL) return;


    for (int i = 0; i < robotLista->cantidad; i++)
    {
        freeRobot(robotLista->lista[i]);
    }
    free(robotLista->lista);
    robotLista->lista = NULL;
    robotLista->cantidad = 0;
}
