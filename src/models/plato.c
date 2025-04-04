#include "plato.h"

#include <stdlib.h>
#include <string.h>

Plato* crear_plato(
    const int id,
    const char* nombre,
    const char* descripcion,
    const float precio,
    const int disponible
)
{
    Plato* plato = malloc(sizeof(Plato));
    if (plato == NULL) return NULL;

    plato->id = id;
    plato->nombre = strdup(nombre);
    plato->descripcion = strdup(descripcion);
    plato->precio = precio;
    plato->disponible = disponible;

    return plato;
}

void free_plato(Plato* plato)
{
    free(plato->nombre);
    free(plato->descripcion);
    free(plato);
}
