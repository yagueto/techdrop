//
// Created by naia.martin on 26/03/2025.
//

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/*typedef struct {
    int id_pedido;
    int id_usuario;
    char direccion[100];
    char fecha[20];
    int estado;
} Pedido;

typedef struct {
    int id_plato;
    char nombre[50];
    char descripcion[50];
    float precio;
    int disponible;
} Plato;

typedef struct {
    int id_detalle;
    int id_pedido;
    int id_plato;
    int cantidad;
    float precio_unitario;
} PedidoDetalle;*/
typedef struct {
    int id_robot;
    char nombre[20];
    int estado; // 0->Ocupado, 1->Mantenimiento, 2->Disponible
    int pedido_actual;
} Robot;


// Funciones para arrays
// Pedido* crearArrayPedidos(int capacidad);
// Plato* crearArrayPlatos(int capacidad);
// PedidoDetalle* crearArrayPedidoDetalle(int capacidad);
Robot* crearArrayRobots(int capacidad);

//Liberar arrays
// void liberarArrayPedidos(Pedido *arrayPedidos);
// void liberarArrayPlatos(Plato *arrayPlatos);
// void liberarArrayPedidoDetalle(PedidoDetalle *arrayPedidoDetalle);
void liberarArrayRobots(Robot *arrayRobots);

#endif //ESTRUCTURAS_H
