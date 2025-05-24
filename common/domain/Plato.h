
#ifndef PLATO_H
#define PLATO_H

#include "Message.h"
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

    void serializar(Message &m);
    static Plato Deserializar(const Message &m);
};



#endif //PLATO_H
