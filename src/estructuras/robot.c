//
// Created by maddi.esparta on 27/03/2025.
//

#include "robot.h"
#include <stdio.h>

#include <string.h>
void crearRobot(Robot *robot) {
    int estado;
    int pedido;
    char nombre[20];
    robot->id_robot = NULL;
    printf("Introduce el nombre del robot: ");
    fflush(stdout);
    fgets(nombre, 20, stdin);
    strcpy(robot->nombre, nombre);

    printf("Introduce el estado del robot(0->Ocupado, 1->Mantenimiento, 2->Libre): ");
    fflush(stdout);
    scanf("%d", &estado);
    robot->estado = estado;
    printf("Introduce el pedido actual(-1 si no tiene): ");
    fflush(stdout);
    scanf("%d", &pedido);
    robot->pedido_actual = pedido;
}

