#ifndef BD_PLATO_H
#define BD_PLATO_H
#include "models/plato.h"

typedef struct
{
    Plato** platos;
    int count;
} PlatoResult;

PlatoResult get_platos();
void free_plato_result(PlatoResult* result);
#endif //BD_PLATO_H
