#include "gestion_menu.h"
#include <sqlite3.h>
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
    printf("Elige un ítem para ver más información: ");
    fflush(stdout);
    scanf("%d", &opcion);
    clearInputBuffer();

    if (opcion > 0 && opcion <= count)
    {
        clrscr();
        Plato* plato = platos[opcion-1];
        char* disponible;
        if (plato->disponible == PLATO_DISPONIBLE)
        {
            disponible = "Sí";
        }
        else
        {
            disponible = "No";
        }
        printf("%d : %s\nDescripción: %s\nPrecio: %.2f\nDisponible: %s\n\n", plato->id, plato->nombre, plato->descripcion,
               plato->precio, disponible);

        waitForEnter();
    }

    // Clean up properly
    free_plato_result(&result);
}

void handle_añadirPlato()
{
    clrscr();
    char nombre[100];
    char descripcion[200];
    char raw_preciso[50];
    float precio;

    printf("Introduce nombre del plato (máx 100 caracteres): ");
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Quitar \n

    printf("Introduce descripción (máx 200 caracteres): ");
    fgets(descripcion, 200, stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0'; // Quitar \n

    printf("Introduce precio: ");
    fgets(raw_precio, 50, stdin);
    sscanf(raw_precio, "%f", &precio);

    printf("\nNombre: %s, descripción: %s, precio: %.2f\n", nombre, descripcion, precio);
    Plato* plato = crear_plato(0, nombre, descripcion, precio, PLATO_DISPONIBLE);
    guardar_plato(plato);
    free_plato(plato);

    waitForEnter();
}

void handle_eliminarPlato()
{
    clrscr();
    int id;

    printf("Introduce el ID del elemento a borrar: ");
    fflush(stdout);
    scanf("%d", &id);
    clearInputBuffer();

    Plato* plato = get_plato_by_id(id);

    if (plato == NULL)
    {
        printf("El plato no existe");
        waitForEnter();
        return;
    }

    int result = -1;
    do
    {
        printf("\nNombre: %s, descripción: %s, precio: %.2f\n", plato->nombre, plato->descripcion, plato->precio);
        printf("¿Desea eliminar el plato? \n0 -> No \n1 -> Si:\n");
        fflush(stdout);
        scanf("%d", &result);
        clearInputBuffer();

    } while (result != 0 && result != 1);
    puts("\n");
    if (result == 1)
    {
        eliminar_plato(plato);
        printf("Eliminado correctamente\n");
    } else
    {
        printf("Cancelado\n");
    }
    waitForEnter();
    free_plato(plato);

}
