
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
  Robot(int id, const string &nombre, int estado, int pedido_actual);
  virtual ~Robot();
  int getId() const;
  string getNombre() const;
  int getEstado() const;
  int getPedidoActual() const;
};

#endif //ROBOT_H
