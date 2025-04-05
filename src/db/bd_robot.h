//
// Created by maddi.esparta on 05/04/2025.
//

#ifndef BD_ROBOT_H
#define BD_ROBOT_H
#include <models/robot.h>

int insertarRobot(Robot* robot);
int eliminarRobot(int id);
Robot* get_robot(int id);
int actualizarEstadoRobot(Robot* robot, int estado);

#endif //BD_ROBOT_H
