#include <stdio.h>
#include "menus.h"



int main()
{
    char opcion;

    do
    {
        opcion = menuPrincipal();

        switch (opcion)
        {
        case '1':
            printf("*Se registra\n");
            break;
        case '2':
            printf("*Inicia sesion\n");
            break;
        case '3':
            printf("nose menu 3 o algo\n");
            break;
        case '4':
            printf("*Ver número de pedidos diarios\n");
            break;
        case '0':
            printf("Volviendo al menú principal\n");
            break;
        default:
            printf("Error! La opción seleccionada no es correcta.\n");
        }
    }
    while (opcion != '0');
    return 0;
}
