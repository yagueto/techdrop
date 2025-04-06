#include "estadisticas.h"
#include "db/bd_estadisticas.h"
#include <stdio.h>
#include <string.h>

//funciones para las estadisticas de negocio
void calcularPedidosPorDia(sqlite3 *db, const char *fecha){
    if (!fecha || strlen(fecha) != 10) {
        printf("\nformato de fecha inválido. usar yyyy-mm-dd\n");
        return;
    }
    int total = obtenerTotalPedidosPorDia(db, fecha);
    if (total >= 0) {
        printf("\npedidos del dia %s: %d\n", fecha, total);
    } else {
        printf("\nerror al obtener datos\n");
    }
}

void calcularZonasPopulares(sqlite3 *db)
{
    char zonas[5][100]; //maximo 5 zonas para mostrar por pantalla
    int contadores[5] = {0};
    int total = obtenerZonasPopulares(db, zonas, contadores, 5);
    printf("\n");
    if (total>0)
    {
        printf("zonas mas populares:\n\n");
        for (int i = 0; i < total; i++)
        {
            printf("%d. %s: %d pedidos\n", i + 1, zonas[i], contadores[i]);
        }
    }else
    {
        printf("no hay datos de zonas\n");
    }
}

void calcularHoraPico(sqlite3 *db)
{
   int hora = obtenerHoraPico(db);
    if (hora >= 0)
    {
        printf("\nhora pico: %d:00\n", hora);
    }else
    {
        printf("no hay datos de horas");
    }
}
void calcularPlatosMasVendidos(sqlite3 *db)
{
    int ids[5];
    int cantidades[5];
    int total = obtenerPlatosMasVendidos(db,ids,cantidades,5);

    if (total> 0)
    {
        printf("\nplatos mas vendidos:\n");
        for (int i = 0; i < total; i++)
        {
            printf("%d. plato id %d: %d unidades\n", i + 1, ids[i], cantidades[i]);
        }
    }else
    {
        printf("no hay datos de platos\n");
    }
}
void calcularClientesRecurrentes(sqlite3 *db)
{
    int ids_usuarios[5];
    int total_pedidos[5];
    int total = obtenerClientesRecurrentes(db, ids_usuarios, total_pedidos, 5);

    if (total > 0)
    {
        printf("\nclientes recurrentes:\n");
        for (int i = 0; i < total; i++)
        {
            printf("%d. usuario %d: %d pedidos\n", i+1, ids_usuarios[i], total_pedidos[i]);
        }
    }else
    {
        printf("no hay datos de clientes recurrentes.");
    }
}
void calcularValorMedioPedido(sqlite3 *db)
{
    double valor_medio = obtenerValorMedioPedido(db);
    if (valor_medio >= 0) {
        printf("\nvalor medio de pedido: %.2f€\n", valor_medio);
    } else {
        printf("no hay datos para calcular el valor medio\n");
    }
}

void calcularRobotsActivos(sqlite3 *db)
{
    int disponibles = obtenerRobotsActivos(db);
    if (disponibles >= 0) {
        printf("\nRobots activos: %d\n", disponibles);
    } else {
        printf("Error al obtener robots activos\n");
    }
}