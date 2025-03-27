#include <stdio.h>
#include "../utils.h"
void menu_gestion_menus()
{
    printf("1. Hacer pedido\n");
    printf("2. Ver mi pedido\n");
    printf("3. Cancelar pedido\n");
    printf("4. Ver tiempo restante para la entrega\n");
    printf("0. Volver al menu principal\n");
    fflush(stdout);

    int ans;
    do
    {
        ans = gestionar_respuesta();

        switch (ans)
        {
        case 1:
            printf("prueba");
            break;
        case 2:
            printf("prueba");
            break;
        case 3:
            printf("prueba");
            break;
        case 4:
            printf("prueba");
            break;
        case 0:
            printf("prueba");
            break;
        default:
            ans = -1;
        }
    }
    while (ans == -1);
}
