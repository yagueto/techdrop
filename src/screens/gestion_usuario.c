#include <bd.h>

#include "../estructuras/usuario.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearUsuario(Usuario *user)
{
  char dni[10];
  char nombre[20];
  char contraseña[20];
  int ok = 0;

  do {

    printf("Introduce el DNI del usuario: ");
    fflush(stdout);
    fgets(dni, 10, stdin);
    clearIfNeeded(dni, 10);

/*    if (obtenerUsuario() == NULL) {
*       ok = 1;
*    }
*/
  }while(ok == 0);


  printf("Introduce el nombre del usuario: ");
  fflush(stdout);
  fgets(nombre, 20, stdin);
  clearIfNeeded(nombre, 20);

  printf("Contraseña: ");
  fflush(stdout);
  fgets(contraseña, 20, stdin);
  clearIfNeeded(contraseña, 20);

  strcpy(user->dni, dni);
  strcpy(user->nombre, nombre);
  strcpy(user->contraseña, contraseña);
}