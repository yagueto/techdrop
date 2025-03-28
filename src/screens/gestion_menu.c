#include "gestion_menu.h"

#include <string.h>

#include "../utils.h"

void handle_listarPlatos()
{
    clrscr();
    printf("piribi");

    int opcion;
    printf("Elige una opción: ");
    fflush(stdout);
    scanf("%d", &opcion);

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
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Quitar \n

    printf("\nIntroduce descripción: ");
    fgets(descripcion, 200, stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0'; // Quitar \n

    printf("\nIntroduce precio: ");
    fgets(raw_precio, 50, stdin);
    sscanf(raw_precio, "%f", &precio);

    puts("\n");
    printf("Nombre: %s, descripción: %s, precio: %f", nombre, descripcion, precio);
    waitForEnter();

}

void handle_eliminarPlato()
{

}