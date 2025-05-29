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

Robot::Robot(const int id, const string &nombre, const int estado,
             const int pedido_actual) {
  this->id = id;
  this->nombre = nombre;
  this->estado = estado;
  this->pedido_actual = pedido_actual;
}
Robot::~Robot() = default;
int Robot::getId() const { return this->id; }
string Robot::getNombre() const { return this->nombre; }
int Robot::getEstado() const { return this->estado; }
int Robot::getPedidoActual() const { return this->pedido_actual; }