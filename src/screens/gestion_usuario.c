#include <db/bd_usuario.h>

#include <models/usuario.h>
#include <./utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearUsuario()
{
  Usuario *user = (Usuario *)malloc(sizeof(Usuario));
  char dni[10];
  char nombre[20];
  char contraseña[20];
  int ok = 0;

  do {
    printf("Introduce el DNI del usuario: ");
    fflush(stdout);
    fgets(dni, 10, stdin);
    clearIfNeeded(dni, 10);
    if (obtenerUsuario(dni, "dni") != NULL) {
      ok = 1;
      printf("El dni se encuentra en la base de datos\n");
    } else {
      ok = 0;
    }
  } while (ok != 0);

  do {
    printf("Introduce el nombre del usuario: ");
    fflush(stdout);
    fgets(nombre, 20, stdin);
    clearIfNeeded(nombre, 20);
    if (obtenerUsuario(nombre, "username") != NULL) {
      ok = 1;
      printf("El usuario está en uso\n");
    } else {
      ok = 0;
    }
  }while (ok != 0);


  printf("Contraseña: ");
  fflush(stdout);
  fgets(contraseña, 20, stdin);
  clearIfNeeded(contraseña, 20);

  user->dni = strdup(dni);
  user->nombre = strdup(nombre);
  user->contraseña = strdup(contraseña);

  insertarUsuario(user);
  freeUsuario(user);
}

void borrarUsuario() {
  int ok = 0;
  char dni[10];
  do {
    printf("Introduce el DNI del usuario a eliminar: ");
    fflush(stdout);
    fgets(dni, 10, stdin);
    clearIfNeeded(dni, 10);

    Usuario* usuario = obtenerUsuario(dni, "dni");
    if (usuario == NULL) {
      ok = 1;
      printf("No hay usuarios con ese DNI, introduce otro\n");
    } else {
      ok = 0;
      eliminarUsuario(usuario);
      printf("Usuario con dni %s, eliminado correctamente", dni);
    }
  } while (ok != 0);
}
