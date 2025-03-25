#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char menuUsuario()
{
  printf("Menu de usuarios:\n");
  printf("Pulsa 1 para crear un nuevo usuario\n");
  printf("Pulsa 2 para iniciar sesión con un usuario existente\n");
  printf("Pulsa 3 para eliminar un usuario\n");
  printf("Pulsa 0 para salir del menú\n");
  printf("Elección: ");
  fflush(stdout);

  char ans;
  do
  {
    ans = gestionar_respuesta();

    switch (ans)
    {
      case 1:
        usuario *user;
        crearUsuario(user);
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

void crearUsuario(usuario *user)
{
  char name[20];
  char pass[20];
  printf("Introduce el nombre del usuario: ");
  fflush(stdout);
  fgets(name, 20, stdin);
  printf("Contraseña: ");
  fflush(stdout);
  fgets(pass, 20, stdin);
  user->nombre = name;
  user->contraseña = pass;
}

int gestionar_respuesta()
{
  printf("Elige una opcion: ");

  char opcion;
  scanf(" %c", &opcion); // Espacio antes de %c para evitar problemas con el buffer

  char* endptr;
  const int out = strtol(&opcion, &endptr, 10);

  return out;
}
