
#ifndef PLATO_H
#define PLATO_H
#include "string.h"
#include <iostream>
using namespace std;


class Plato {
    int id;
    string nombre;
    string descripcion;
    float precio;
    int disponible;
public:
    Plato();
    Plato(int id, string nombre,string descripcion,float precio, int disponible);
    int getId();
    string getNombre();
    string getDescp();
    float getPrecio();
    int getDisponibilidad();
};



#endif //PLATO_H
