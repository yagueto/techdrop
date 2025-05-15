#include "pedido.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
time_t string_a_time(char* s) {
    struct tm tm = {0};
    int año, mes, dia;
    if (s == NULL || strlen(s) == 0) {
        return (time_t)-1;
    }

    if (sscanf(s, "%d-%d-%d", &año, &mes, &dia) != 3) {
        return (time_t)-1;  // Fecha inválida
    }
    tm.tm_year = año - 1900;
    tm.tm_mon = mes - 1;
    tm.tm_mday = dia;
    return mktime(&tm);
}
Pedido* crearPedido(int id,int id_usuario,char* direccion,time_t fecha, int estado) {
    Pedido* p = malloc(sizeof(Pedido));
    p->id = id;
    p->id_usuario = id_usuario;
    p->direccion = direccion;
    p->fecha = fecha;
    p->estado = estado;
    return p;
}
