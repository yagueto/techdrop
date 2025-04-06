#include <bd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.h"

Robot* crearRobot(char* nombre, int estado) {


    if (nombre == NULL || strlen(nombre) == 0) {
        fprintf(stderr, "Error: Nombre inválido\n");
        return NULL;
    }


    if (estado < 0 || estado > 2) {
        printf("Error: Estado %d fuera de rango (0-2)\n", estado);
        return NULL;
    }


    Robot* robot = (Robot*)malloc(sizeof(Robot));
    robot->id = 0;
    robot->nombre = strdup(nombre);
    robot->estado = estado;
    robot->pedido_actual = -1;


    return robot;


}
void freeRobot(Robot* r)
{
    if (r == NULL) return;
    if (r->nombre != NULL) {
        free(r->nombre);
        r->nombre = NULL;
    }
    free(r);
}
char* estado_a_texto(int estado) {
    if (estado < 0 || estado > 2) {
        printf("Estado invalido\n");
        return NULL;
    }


    switch (estado) {
        case 0:  return "Ocupado";
        case 1: return "Mantenimiento";
        case 2: return "Disponible";
        default: return "Desconocido";
    }
}


