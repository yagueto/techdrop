#include "menus.h"
#include <stdio.h>

char menuPrincipal() {
    char opcion;

    printf("1. Registrarse\n");
    printf("2. Iniciar sesion\n");
    //printf("3. Acceder como administrador\n");
    printf("0. Salir\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);  // Espacio antes de %c para evitar problemas con el buffer

    return opcion;
}

char menuCliente() {
    char opcion;

    printf("1. Hacer pedido\n");
    printf("2. Ver mi pedido\n");
    printf("3. Cancelar pedido\n");
    printf("4. Ver tiempo restante para la entrega\n");
    printf("0. Volver al menu principal\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);

    return opcion;
}

char menuAdministrador() {
    char opcion;

    printf("1. Gestionar cuentas\n");
    printf("2. Gestionar menu\n");
    printf("3. Ver estado de los robots\n");
    printf("4. Ver numero de pedidos diarios\n");
    printf("0. Volver al menu principal\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);

    return opcion;
}

char menuGestionCuentas() {
    char opcion;

    printf("1. Eliminar usuario\n");
    printf("2. Ver usuario\n");
    printf("3. Gestionar permisos\n");
    printf("0. Volver al menu administrador\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);

    return opcion;
}


char menuGestionMenu() {
    char opcion;

    printf("1. Añadir plato\n");
    printf("2. Eliminar plato\n");
    printf("0. Volver al menu administrador\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);

    return opcion;
}

char menuEstadoRobots() {
    char opcion;

    printf("1. Ver robots disponibles\n");
    printf("2. Ver cola de pedidos pendientes\n");
    printf("0. Volver al menu administrador\n");
    printf("Elige una opcion: ");
    fflush(stdout);
    scanf(" %c", &opcion);

    return opcion;
}
