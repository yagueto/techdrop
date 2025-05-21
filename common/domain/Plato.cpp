//
// Created by naia.martin on 15/05/2025.
//

#include "Plato.h"
Plato::Plato() {
  this->descripcion = " ";
  this->disponible = 0;
  this->id = NULL;
  this->nombre = " ";
  this->precio = 0;
}
Plato::Plato(int id, string nombre, string descripcion, float precio,
             int disponible) {
  this->id = id;
  this->nombre = nombre;
  this->descripcion = descripcion;
  this->precio = precio;
  this->disponible = disponible;
}
int Plato::getId() { return this->id; }
string Plato::getNombre() { return this->nombre; }
string Plato::getDescp() { return this->descripcion; }
float Plato::getPrecio() { return this->precio; }
int Plato::getDisponibilidad() { return this->disponible; }