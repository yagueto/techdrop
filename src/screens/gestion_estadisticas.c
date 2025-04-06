#include <estadisticas.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <estadisticas.h>

#include "db/bd_new.h"

//Implementacion de handlers de estadisticas
void handle_pedidosPorDia() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== PEDIDOS POR DÍA ===\n");
    char fecha[11];
    printf("Introduce la fecha (YYYY-MM-DD): ");
    if (fgets(fecha, sizeof(fecha), stdin))
    {
        clearInputBuffer();
        //Quitar el salto de linea
        fecha[strcspn(fecha, "\n")] = '\0';

        if (strlen(fecha) == 10) {
            calcularPedidosPorDia(dbCon, fecha);
        } else {
            printf("\nUsa formato: YYYY-MM-DD\n");
        }
    }
    waitForEnter();
}
void handle_zonasPopulares(){
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== ZONAS POPULARES ===\n");

    calcularZonasPopulares(dbCon);
    waitForEnter();
}

void handle_horaPico() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== HORA PICO ===\n");

    calcularHoraPico(dbCon);
    waitForEnter();
}

void handle_platosMasVendidos() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== PLATOS MAS VENDIDOS ===\n");
    calcularPlatosMasVendidos(dbCon);
    waitForEnter();
}

void handle_clientesRecurrentes() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== CLIENTES RECURRENTES ===\n");
    calcularClientesRecurrentes(dbCon);
    waitForEnter();
}

void handle_valorMedioPedido() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== VALOR MEDIO DE PEDIDOS ===\n");
    calcularValorMedioPedido(dbCon);
    waitForEnter();
}

void handle_robotsActivos() {
    sqlite3 *dbCon = get_db();
    clrscr();
    printf("\n=== ROBOTS ACTIVOS ===\n");
    calcularRobotsActivos(dbCon);
    waitForEnter();
}
