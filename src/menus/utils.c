#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int gestionar_respuesta()
{
    int opcion;
    printf("Elige una opcion: ");
    scanf("%d", &opcion);
    return opcion; // Return directly
}
