#ifndef BD_PLATO_H
#define BD_PLATO_H
#include "models/plato.h"

typedef struct
{
    Plato** platos;
    int count;
} PlatoResult;

PlatoResult get_platos();
Plato* get_plato_by_id(int id);
int guardar_plato(Plato* plato);
int eliminar_plato(Plato* plato);
void free_plato_result(PlatoResult* result);
#endif //BD_PLATO_H
