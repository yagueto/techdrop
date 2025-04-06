#include "models/robot.h"
#include "gestion_robot.h"
#include <stdio.h>
#include "utils.h"
#include <string.h>


#include "db/bd_pedido.h"
#include "db/bd_robot.h"


#define MAX_LINE 100


void handle_añadirRobot() {
   char str[MAX_LINE];
   char nombre[MAX_LINE];
   int estado;


   printf("Introduce el nombre: ");
   fflush(stdout);
   if (fgets(nombre, MAX_LINE, stdin) == NULL) {
       printf("Error al leer la entrada\n");
       return;
   }
   nombre[strcspn(nombre, "\n")] = '\0';
   if (strlen(nombre) == 0) {
       printf("Error: El nombre no puede estar vacío\n");
       waitForEnter();
       return;
   }


   printf("Introduce el estado(0->Ocupado, 1->Mantenimiento, 2->Disponible): ");
   fflush(stdout);
   fgets(str, MAX_LINE, stdin) ;
   sscanf(str, "%i", &estado);
   if (estado < 0 || estado > 2) {
       printf("Error: Estado %d fuera de rango (0-2)\n", estado);
       waitForEnter();
       return;
   }
    Robot* robot = crearRobot(nombre, estado);
    int respuesta=-1;
    if (estado == 2) {
        printf("¿Quieres asignar un pedido automaticamente?\n0 -> No \n1 -> Si:\n");
        fflush(stdout);
        scanf("%d", &respuesta);
        clearInputBuffer();

        if (respuesta == 0) {
            printf("\nNuevo robot: %s, nuevo estado: %i", nombre, estado);
        }else if (respuesta == 1) {
            int id = pedidoCola();
            if (id == -1) {
                printf("En estos momentos no hay pedidos en cola");
                printf("\nNuevo robot: %s, nuevo estado: %i", nombre, estado);
            }else {
                robot->pedido_actual = id;
                robot->estado = 0;
                printf("Se le ha asignado el pedido: %d", id);
                printf("\nNuevo robot: %s, nuevo estado: %i", nombre, estado);
            }
        }else {
            printf("Valor invalido");
            waitForEnter();
            return;
        }

    }else {
        printf("\nNuevo robot: %s, nuevo estado: %i", nombre, estado);
    }

   insertarRobot(robot);
   freeRobot(robot);
   waitForEnter();


}
void handle_eliminarRobot() {
   char str[MAX_LINE];
   int id;
   printf("Introduce el id del robot: ");
   fflush(stdout);
   fgets(str, MAX_LINE, stdin);
   sscanf(str, "%i", &id);




   Robot* robot = get_robot(id);


   if (robot == NULL) {
       printf("No existe un robot con este id");
       waitForEnter();
       return;
   }
   int result = -1;
   do
   {
       printf("\nNombre: %s, estado: %i, pedido_actual: %i\n", robot->nombre, robot->estado, robot->pedido_actual);
       printf("¿Desea eliminar el robot? \n0 -> No \n1 -> Si:\n");
       fflush(stdout);
       scanf("%d", &result);
       clearInputBuffer();


   } while (result != 0 && result != 1);
   puts("\n");
   if (result == 1)
   {
       eliminarRobot(robot->id);
       printf("Robot %i Eliminado correctamente\n", robot->id);
   } else
   {
       printf("Cancelado\n");
   }
   freeRobot(robot);
   waitForEnter();
}
void handle_listaRobots() {


   RobotLista* robotLista = get_robotLista();


   const char* estados[] = {"Ocupado", "Mantenimiento", "Disponible"};
   if (robotLista == NULL || robotLista->lista == NULL) {
       printf("No hay robots disponibles o ocurrió un error.\n");
       waitForEnter();
       return;
   }


   int cantidad = robotLista->cantidad;


   for (int i = 0; i < cantidad; ++i)
   {
       printf("Robot ID: %d\n", robotLista->lista[i]->id);
       printf("Nombre: %s\n", robotLista->lista[i]->nombre );
       printf("Estado: %s\n", estados[robotLista->lista[i]->estado]);
       printf("Pedido actual: %d\n\n", robotLista->lista[i]->pedido_actual);
   }


   free_robotLista(robotLista);
   waitForEnter();
}
void handle_modificar_estadoRobot() {
   char str[MAX_LINE];
   int id;
   int estado;
   printf("Introduce el id del robot: ");
   fflush(stdout);
   fgets(str, MAX_LINE, stdin) ;
   sscanf(str, "%i", &id);
   Robot* r = get_robot(id);
   if (r == NULL) {
       printf("No existe un robot con id %i\n", id);
       waitForEnter();
       return;
   }
   printf("\nRobot: %i\n", id);
   printf("Estado actual: %s\n",estado_a_texto(r->estado));
   printf("Nuevo estado:\n");
   printf("0 -> Ocupado\n");
   printf("1 -> Mantenimiento\n");
   printf("2 -> Disponible\n");
   printf("Selecciona estado: ");
   fflush(stdout);
   if (fgets(str, MAX_LINE, stdin) == NULL) {
       fprintf(stderr, "Entrada inválida\n");


       waitForEnter();
       return;
   }
   sscanf(str, "%i", &estado);
   if (estado == r->estado) {
       printf("Debes seleccionar otro estado\n");
       waitForEnter();
       return;
   }
   if (actualizarEstadoRobot(r, estado) !=0) {
       printf("Error al actualizar estado\n");




   }else {
       printf("Estado actualizado correctamente\n");
       printf("Nuevo estado: %s\n", estado_a_texto(estado));


   }


}
