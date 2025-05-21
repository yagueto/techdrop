
#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
using namespace std;

class Robot {
    int id;
    string nombre;
    int estado;
    int pedido_actual;
public:
    Robot();
    Robot(int id, string nombre, int estado, int pedido_actual);
    virtual ~Robot();
    int getId();
    string getNombre();
    int getEstado();
    int getPedidoActual();
};



#endif //ROBOT_H
