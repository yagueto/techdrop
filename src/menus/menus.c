#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include "../estadisticas.h"
#include "../estructuras/estructuras.h"
#include "../bd.h"
#include "../estructuras/usuario.h"


void menuPrincipalAdmin(sqlite3 *db)
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
            menuUsuario();
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            menuEstadisticas(db);
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
    printf("3. Insertar Robot\n");
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
           // Robot *robot;
           // crearRobot(robot);
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


void menuEstadisticas(sqlite3 *db) {
    char opcion;

    // Estadisticas del negocio general
    printf("ESTADISTICAS DE NEGOCIO\n");
    printf("1. Pedidos por día/semana/mes\n");
    printf("2. Zonas mas popular\n");
    printf("3. Hora pico de pedidos\n");
    printf("4. Platos mas vendidos\n");
    printf("5. Clientes recurrentes\n");
    printf("6. Valor promedio de pedido\n");

    //Estadisticas de Robots
    printf("ESTADISTICAS DE ROBOTS\n");
    printf("7. Kilometros recorridos por robot\n");
    printf("8. Pedidos completados por robot\n");
    printf("9. Robots activos\n");

    printf("0. Volver al menu administrador\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("Pedidos por dia:");
            calcularPedidosPorDia(db);
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
        case 9:
            printf("9prueba");
            break;
        case 0:
            menuPrincipalAdmin(db);
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);

}

void menuUsuario()
{
    printf("Menu de usuarios:\n");
    printf("Pulsa 1 para crear un nuevo usuario\n");
    printf("Pulsa 2 para iniciar sesión con un usuario existente\n");
    printf("Pulsa 3 para eliminar un usuario\n");
    printf("Pulsa 0 para salir del menú\n");
    printf("Elección: ");
    fflush(stdout);

    char ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
            case 1:
                Usuario *user = (Usuario *)malloc(sizeof(Usuario));
            if (user == NULL) {
                printf("Error al asignar memoria para el usuario.\n");
                exit(1);
            }
            crearUsuario(user);
            //Futuro insert en la BBDD
            free(user);
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
