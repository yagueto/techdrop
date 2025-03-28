#include <stdio.h>
#include "menu.h"
#include "estadisticas.h"
#include <stdlib.h>
#include <string.h>

static sqlite3* dbCon = NULL;

Menu* menuPrincipal;
Menu* menuGestionPlatos;
Menu* menuGestionCuentas;
Menu* menuEstadisticas;


Menu* createMenu(const char* title, const int numOptions)
{
    Menu* menu = malloc(sizeof(Menu));
    if (!menu) return NULL;

    menu->title = strdup(title);
    menu->numOptions = numOptions;
    menu->options = (char**)malloc(numOptions * sizeof(char*));
    menu->handlers = (void (**)())malloc(numOptions * sizeof(void(*)()));

    return menu;
}

void addOption(Menu* menu, const int index, const char* option, void (*handler)())
{
    if (!menu || index < 0 || index >= menu->numOptions) return;
    menu->options[index] = strdup(option);
    menu->handlers[index] = handler;
}

void showMenu(Menu* menu)
{
    if (!menu) return;
    do
    {
        clrscr(); // Limpiar pantalla antes de dibujar menú
        printf(
            " _            _         _                 \n| |_ ___  ___| |__   __| |_ __ ___  _ __  \n| __/ _ \\/ __| '_ \\ / _` | '__/ _ \\| '_ \\ \n| ||  __/ (__| | | | (_| | | | (_) | |_) |\n \\__\\___|\\___| |_|_|\\__,_|_|  \\___/| .__/ \n                                   |_|    \n");

        printf("-----%s----\n", menu->title);
        for (int i = 0; i < menu->numOptions; ++i)
        {
            printf("%d: %s\n", i + 1, menu->options[i]);
        }
        printf("0: Volver\n");
        int opcion;
        do
        {
            printf("Elige una opción: ");
            fflush(stdout);
            scanf("%d", &opcion);
            if (menu->handlers[opcion - 1] == NULL) printf("Aún no implementado\n");
        }
        while (opcion < 0 || opcion > menu->numOptions || menu->handlers[opcion - 1] == NULL);
        if (opcion == 0) return;
        menu->handlers[opcion - 1]();
    }
    while (1);
}

void destroyMenu(Menu* menu)
{
    if (!menu) return;

    free(menu->title);

    for (int i = 0; i < menu->numOptions; i++)
    {
        free(menu->options[i]);
    }
    free(menu->options);

    free(menu->handlers);
    free(menu);
}

void handle_menuPlatos()
{
    showMenu(menuGestionPlatos);
}

void handle_menuCuentas()
{
    showMenu(menuGestionCuentas);
}

void handle_menuEstadisticas()
{
    showMenu(menuEstadisticas);
}

void initializeMenus(sqlite3* db)
{
    dbCon = db;
    // Crear menús
    menuPrincipal = createMenu("Menú principal", 3);
    addOption(menuPrincipal, 0, "Gestionar menú", handle_menuPlatos);
    addOption(menuPrincipal, 1, "Gestionar cuentas", handle_menuCuentas);
    addOption(menuPrincipal, 2, "Estadísticas", handle_menuEstadisticas);

    menuGestionPlatos = createMenu("Gestión menú", 3);
    addOption(menuGestionPlatos, 0, "Listar platos", NULL);
    addOption(menuGestionPlatos, 1, "Añadir platos", NULL);
    addOption(menuGestionPlatos, 2, "Eliminar plato(s)", NULL);

    menuGestionCuentas = createMenu("Gestión cuentas", 3);
    addOption(menuGestionCuentas, 0, "Listar cuentas", NULL);
    addOption(menuGestionCuentas, 1, "Añadir cuenta", NULL);
    addOption(menuGestionCuentas, 2, "Eliminar cuenta(s)", NULL);

    menuEstadisticas = createMenu("Estadísticas del sistema", 9);
    addOption(menuEstadisticas, 0, "Pedidos por día", NULL);
    addOption(menuEstadisticas, 1, "Zonas mas popular", NULL);
    addOption(menuEstadisticas, 2, "Hora pico de pedidos", NULL);
    addOption(menuEstadisticas, 3, "Platos más vendidos", NULL);
    addOption(menuEstadisticas, 4, "Clientes recurrentes", NULL);
    addOption(menuEstadisticas, 5, "Valor promedio de pedido", NULL);
    addOption(menuEstadisticas, 6, "Kilómetros recorridos por robot", NULL);
    addOption(menuEstadisticas, 7, "Pedidos completados por robot", NULL);
    addOption(menuEstadisticas, 8, "Robots activos", NULL);


    showMenu(menuPrincipal);

    // Liberar la memoria
    destroyMenu(menuPrincipal);
    destroyMenu(menuGestionPlatos);
    destroyMenu(menuGestionCuentas);
    destroyMenu(menuEstadisticas);
}
