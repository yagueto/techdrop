#ifndef ROBOT_H
#define ROBOT_H
typedef struct {
    int id;
    char* nombre;
    int estado; // 0->Ocupado, 1->Mantenimiento, 2->Disponible
    int pedido_actual;
} Robot;

Robot* crearRobot(char* nombre, int estado);
void freeRobot(Robot* r);
char* estado_a_texto(int estado);
#endif //ROBOT_H
