#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int gestionar_respuesta()
{
    int opcion;
    printf("Elige una opcion: ");
    scanf("%d", &opcion);
    while (getchar() != '\n');
    return opcion; // Return directly
}

// Función de Asier Perallos ejercicio 15
void clearIfNeeded(char *str, int max_line)
{
    // Limpia los caracteres de m�s introducidos
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
        while (getchar() != '\n');
}
