//
// Created by naia.martin on 26/03/2025.
//

#include "estadisticas.h"
#include "estructuras.h"
#include "bd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funciones para las estadisticas de negocio
void calcularPedidosPorDia(sqlite3 *db){
    //Cargar datos de la bd
    int total_pedidos;
    Pedido *pedidos = cargarPedidos(db, &total_pedidos);

    if (!pedidos || total_pedidos == 0) {
        printf("No hay pedidos registrados.\n");
        return;
    }
    printf("\nPedidos por día:\n");
    char fechaActual[11] = ""; //Agrupar por fecha
    int contador = 0;

    for (int i = 0; i < total_pedidos; i++) {
        char fechaPedido[11];
        strncpy(fechaPedido, pedidos[i].fecha, 10);
        fechaPedido[10] = '\0';

        if (strcmp(fechaPedido, fechaActual) == 0) {
            contador++;
        } else {
            if (contador > 0) {
                printf("%s: %d pedidos\n", fechaActual, contador);
            }
            strcpy(fechaActual, fechaPedido);
            contador = 1;
        }
    }
    printf("%s: %d pedidos\n", fechaActual, contador);//ultimo grupo
    free(pedidos);
}

void calcularZonasPopulares(sqlite3 *db)
{

}
void calcularHoraPico(sqlite3 *db)
{

}
void calcularPlatosMasVendidos(sqlite3 *db)
{

}
void calcularClientesRecurrentes(sqlite3 *db)
{

}
void calcularValorMedioPedido(sqlite3 *db)
{

}

//Funciones para las estadisticas de robots
void calcularKmPorRobot(sqlite3 *db)
{

}
void calcularPedidosPorRobot(sqlite3 *db)
{

}
void calcularRobotsActivos(sqlite3 *db)
{

}