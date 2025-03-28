#include <stdio.h>
#include <string.h>
#include "utils.h"

// Función de Asier Perallos ejercicio 15
void clearIfNeeded(char *str, int max_line)
{
    // Limpia los caracteres de m�s introducidos
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
        while (getchar() != '\n');
}

// Funcion para continuar(esperar a que el usuario pulse)
void waitForEnter() {
    printf("\nPresione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcion para obtener fecha de input
void getDate(char* buffer, int size) {
    printf("Introduce la fecha (YYYY-MM-DD): ");
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
