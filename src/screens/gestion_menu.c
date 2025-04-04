#include "gestion_menu.h"
#include <stdio.h>
#include <string.h>
#include "../utils.h"
#include "db/bd_plato.h"
#include "models/plato.h"

void handle_listarPlatos()
{
    clrscr();

    PlatoResult result = get_platos();
    Plato** platos = result.platos;
    int count = result.count;
    if (platos == NULL || count == 0)
    {
        printf("No hay platos disponibles.\n");
        waitForEnter();
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        printf("%d - %s (%s) -> %.2f\n", platos[i]->id, platos[i]->nombre, platos[i]->descripcion, platos[i]->precio);
    }

    int opcion;
    printf("Elige una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

    // Clean up properly
    free_plato_result(&result);

}

void handle_añadirPlato()
{
    clrscr();
    char nombre[100];
    char descripcion[200];
    char raw_precio[50];
    float precio;

    getchar();
    printf("Introduce nombre del plato: ");
    fgets(nombre, 1, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Quitar \n

    printf("\nIntroduce descripción: ");
    fgets(descripcion, 200, stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0'; // Quitar \n

    printf("\nIntroduce precio: ");
    fgets(raw_precio, 50, stdin);
    sscanf(raw_precio, "%f", &precio);

    puts("\n");
    printf("Nombre: %s, descripción: %s, precio: %.2f", nombre, descripcion, precio);
    waitForEnter();
}

void handle_eliminarPlato()
{
}
