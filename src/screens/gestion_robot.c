//
// Created by maddi.esparta on 05/04/2025.
//
#include "models/robot.h"
#include "gestion_robot.h"
#include <stdio.h>
#include "utils.h"
#include <string.h>

#include "db/bd_robot.h"

#define MAX_LINE 100

void handle_añadirRobot() {
    char str[MAX_LINE];
    char nombre[MAX_LINE];
    int estado;

    printf("Introduce el nombre: ");
    fflush(stdout);
    if (fgets(nombre, MAX_LINE, stdin) == NULL) {
        printf("Error al leer la entrada\n");
        return;
    }
    nombre[strcspn(nombre, "\n")] = '\0';
    if (strlen(nombre) == 0) {
        printf("Error: El nombre no puede estar vacío\n");
        waitForEnter();
        return;
    }

    printf("Introduce el estado(0->Ocupado, 1->Mantenimiento, 2->Disponible): ");
    fflush(stdout);
    fgets(str, MAX_LINE, stdin) ;
    sscanf(str, "%i", &estado);
    if (estado < 0 || estado > 2) {
        printf("Error: Estado %d fuera de rango (0-2)\n", estado);
        waitForEnter();
        return;
    }

    printf("\nNombre: %s, estado: %i", nombre, estado);
    Robot* robot = crearRobot(nombre, estado);
    insertarRobot(robot);
    freeRobot(robot);
    waitForEnter();

}
void handle_eliminarRobot() {
    char str[MAX_LINE];
    int id;
    printf("Introduce el id del robot: ");
    fflush(stdout);
    fgets(str, MAX_LINE, stdin);
    sscanf(str, "%i", &id);


    Robot* robot = get_robot(id);

    if (robot == NULL) {
        printf("No existe un robot con este id");
        waitForEnter();
        return;
    }
    int result = -1;
    do
    {
        printf("\nNombre: %s, estado: %i, pedido_actual: %i\n", robot->nombre, robot->estado, robot->pedido_actual);
        printf("¿Desea eliminar el robot? \n0 -> No \n1 -> Si:\n");
        fflush(stdout);
        scanf("%d", &result);
        clearInputBuffer();

    } while (result != 0 && result != 1);
    puts("\n");
    if (result == 1)
    {
        eliminarRobot(robot);
        printf("Robot %s Eliminado correctamente\n", robot->nombre);
        waitForEnter()
    } else
    {
        printf("Cancelado\n");
    }
    freeRobot(robot);
    waitForEnter();
}
void handle_listaRobots() {

}
void handle_modificar_estadoRobot() {
    char str[MAX_LINE];
    int id;
    int estado;
    printf("Introduce el id del robot: ");
    fflush(stdout);
    fgets(str, MAX_LINE, stdin) ;
    sscanf(str, "%i", &id);
    Robot* r = get_robot(id);
    if (r == NULL) {
        printf("No existe un robot con id %i\n", id);
        waitForEnter();
        return;
    }
    printf("\nRobot: %i\n", id);
    printf("Estado actual: %s\n",estado_a_texto(r->estado));
    printf("Nuevo estado:\n");
    printf("0 -> Ocupado\n");
    printf("1 -> Mantenimiento\n");
    printf("2 -> Disponible\n");
    printf("Selecciona estado: ");
    fflush(stdout);
    if (fgets(str, MAX_LINE, stdin) == NULL) {
        fprintf(stderr, "Entrada inválida\n");

        waitForEnter();
        return;
    }
    sscanf(str, "%i", &estado);
    if (estado == r->estado) {
        printf("Debes seleccionar otro estado\n");
        waitForEnter();
        return;
    }
    if (actualizarEstadoRobot(r, estado) !=0) {
        printf("Error al actualizar estado\n");


    }else {
        printf("Estado actualizado correctamente\n");
        printf("Nuevo estado: %s\n", estado_a_texto(estado));

    }

}