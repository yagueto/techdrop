//
// Created by maddi.esparta on 27/03/2025.
//

#include "robot.h"
#include <stdio.h>
void crearRobot(Robot *robot) {
    int estado;
    int pedido;
    robot->id_robot = 0;
    printf("Introduce el estado del robot(0->Ocupado, 1->Mantenimiento, 2->Libre): ");
    fflush(stdout);
    scanf("%d", &estado);
    robot->estado = estado;
    printf("Introduce el pedido actual(-1 si no tiene): ");
    fflush(stdout);
    scanf("%d", &pedido);
    robot->pedido_actual = pedido;
}