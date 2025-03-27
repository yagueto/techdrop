#include "usuario.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuUsuario()
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
        usuario *user = (usuario *)malloc(sizeof(usuario));
      if (user == NULL) {
        printf("Error al asignar memoria para el usuario.\n");
        exit(1);
      }
      crearUsuario(user);
      //Futuro insert en la BBDD
      free(user);
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
  clearIfNeeded(name, 20);

  printf("Contraseña: ");
  fflush(stdout);
  fgets(pass, 20, stdin);
  clearIfNeeded(pass, 20);

  strcpy(user->nombre, name);
  strcpy(user->contraseña, pass);
}
