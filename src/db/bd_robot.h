//
// Created by maddi.esparta on 05/04/2025.
//

#ifndef BD_ROBOT_H
#define BD_ROBOT_H
#include <models/robot.h>
typedef  struct {
    Robot** lista;
    int cantidad;
}RobotLista;
int insertarRobot(Robot* robot);
int eliminarRobot(int id);
Robot* get_robot(int id);
int actualizarEstadoRobot(Robot* robot, int estado);
void free_robotLista(RobotLista* robotLista);
RobotLista* get_robotLista();

#endif //BD_ROBOT_H
