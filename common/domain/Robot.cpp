//
// Created by naia.martin on 15/05/2025.
//

#include "Robot.h"

Robot::Robot() {
  this->id = 0;
  this->nombre = "";
  this->estado = 0;
  this->pedido_actual = 0;
}

Robot::Robot(int id, string nombre, int estado, int pedido_actual) {
  this->id = id;
  this->nombre = nombre;
  this->estado = estado;
  this->pedido_actual = pedido_actual;
}
Robot::~Robot() {
  // delete [] nombre;
}
int Robot::getId() { return this->id; }
string Robot::getNombre() { return this->nombre; }
int Robot::getEstado() { return this->estado; }
int Robot::getPedidoActual() { return this->pedido_actual; }