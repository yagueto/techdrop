#include <stdio.h>
#include "utils.h"

void menuPrincipal()
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


void menuAdministrador()
{
    printf("1. Gestionar cuentas\n");
    printf("2. Gestionar menu\n");
    printf("3. Ver estado de los robots\n");
    printf("4. Ver numero de pedidos diarios\n");
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
