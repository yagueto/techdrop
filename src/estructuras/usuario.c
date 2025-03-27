#include "usuario.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearUsuario(Usuario *user)
{
  char name[20];
  char pass[20];
  printf("Introduce el nombre del usuario: ");
  fflush(stdout);
  fgets(name, 20, stdin);
  clearIfNeeded(name, 20);

  printf("Contraseña: ");
  fflush(stdout);
  fgets(pass, 20, stdin);
  clearIfNeeded(pass, 20);

  strcpy(user->nombre, name);
  strcpy(user->contraseña, pass);
}
