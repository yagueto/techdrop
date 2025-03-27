//
// Created by maddi.esparta on 27/03/2025.
//

#ifndef ROBOT_H
#define ROBOT_H
typedef struct {
    int id_robot;
    int estado; // 0->Ocupado, 1->Mantenimiento, 2->Disponible
    int pedido_actual;
} Robot;

void crearRobot(Robot *robot);
#endif //ROBOT_H
