#include "menus.h"
#include <stdio.h>
#include <stdlib.h>

void menuPrincipalAdmin()
{
    printf("1. Gestionar menú\n");
    printf("2. Gestionar cuentas\n");
    printf("3. Gestionar robots\n");
    printf("4. Estadísticas\n");
    printf("0. Salir\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("prueba");
            break;
        case 2:
            printf("prueba");
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            menuEstadisticas();
            break;
        case 0:
            printf("prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}

void menuCliente()
{
    printf("1. Hacer pedido\n");
    printf("2. Ver mi pedido\n");
    printf("3. Cancelar pedido\n");
    printf("4. Ver tiempo restante para la entrega\n");
    printf("0. Volver al menu principal\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("prueba");
            break;
        case 2:
            printf("prueba");
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            printf("prueba");
            break;
        case 0:
            printf("prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}

void menuGestionCuentas()
{
    printf("1. Eliminar usuario\n");
    printf("2. Ver usuario\n");
    printf("3. Gestionar permisos\n");
    printf("0. Volver al menu administrador\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("prueba");
            break;
        case 2:
            printf("prueba");
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            printf("prueba");
            break;
        case 0:
            printf("prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}


void menuGestionMenu()
{
    printf("1. Añadir plato\n");
    printf("2. Eliminar plato\n");
    printf("0. Volver al menu administrador\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("prueba");
            break;
        case 2:
            printf("prueba");
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            printf("prueba");
            break;
        case 0:
            printf("prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}

void menuEstadoRobots()
{
    char opcion;

    printf("1. Ver robots disponibles\n");
    printf("2. Ver cola de pedidos pendientes\n");
    printf("0. Volver al menu administrador\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("1prueba");
            break;
        case 2:
            printf("2prueba");
            break;
        case 3:
            printf("3prueba");
            break;
        case 4:
            printf("4prueba");
            break;
        case 0:
            printf("0prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}

int gestionar_respuesta()
{
    printf("Elige una opcion: ");

    char opcion;
    scanf(" %c", &opcion); // Espacio antes de %c para evitar problemas con el buffer

    char* endptr;
    const int out = strtol(&opcion, &endptr, 10);

    return out;
}

void menuEstadisticas() {
    char opcion;

    // Estadisticas del negocio general
    printf("ESTADISTICAS DE NEGOCIO\n");
    printf("1. Pedidos por dia/semana/mes\n");
    printf("2. Hora pico de pedidos\n");
    printf("3. Platos mas vendidos\n");
    printf("4. Clientes recurrentes\n");
    printf("5. Valor promedio de pedido\n");

    //Estadisticas de Robots
    printf("ESTADISTICAS DE ROBOTS\n");
    printf("6. Kilometros recorridos por robot\n");
    printf("7. Pedidos completados por robot\n");
    printf("8. Robots activos\n");

    printf("0. Volver al menu principal\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("1prueba");
            break;
        case 2:
            printf("2prueba");
            break;
        case 3:
            printf("3prueba");
            break;
        case 4:
            printf("4prueba");
            break;
        case 5:
            printf("5prueba");
            break;
        case 6:
            printf("6prueba");
            break;
        case 7:
            printf("7prueba");
            break;
        case 8:
            printf("8prueba");
            break;

        case 0:
            menuPrincipalAdmin();
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);

}
