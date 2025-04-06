#include <db/bd_usuario.h>

#include <models/usuario.h>
#include <./utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearUsuario()
{
  clrscr();
  Usuario *user = (Usuario *)malloc(sizeof(Usuario));
  char dni[10];
  char nombre[20];
  char contraseña[20];
  int ok = 0;

  do {
    printf("Introduce el DNI del usuario: ");
    fflush(stdout);
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = '\0';
    clearIfNeeded(dni, 10);
    Usuario *usuario = obtenerUsuario(dni, "dni");
    if (usuario != NULL) {
      ok = 1;
      printf("El dni se encuentra en la base de datos\n");
      freeUsuario(usuario);
    } else {
      ok = 0;
    }
  } while (ok != 0);

  do {
    printf("Introduce el nombre del usuario: ");
    fflush(stdout);
    fgets(nombre, 20, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';
    clearIfNeeded(nombre, 20);
    Usuario* usuario = obtenerUsuario(nombre, "username");
    if (usuario != NULL) {
      ok = 1;
      printf("El usuario está en uso\n");
      freeUsuario(usuario);
    } else {
      ok = 0;
    }
  }while (ok != 0);


  printf("Contraseña: ");
  fflush(stdout);
  fgets(contraseña, 20, stdin);
  contraseña[strcspn(nombre, "\n")] = '\0';
  clearIfNeeded(contraseña, 20);

  user->dni = strdup(dni);
  user->nombre = strdup(nombre);
  user->contraseña = strdup(contraseña);

  insertarUsuario(user);

  freeUsuario(user);
}

void borrarUsuario() {
  clrscr();
  int ok = 0;
  do {
    char dni[10];
    printf("Introduce el DNI del usuario a eliminar: ");
    fflush(stdout);
    fgets(dni, 10, stdin);
    dni[strcspn(dni, "\n")] = '\0';
    clearIfNeeded(dni, 10);

    Usuario* usuario = obtenerUsuario(dni, "dni");
    if (usuario == NULL) {
      ok = 1;
      printf("No hay usuarios con ese DNI, introduce otro\n");
    } else {
      ok = 0;
      eliminarUsuario(usuario);
      printf("Usuario con dni %s, eliminado correctamente", dni);
      waitForEnter();
    }
  } while (ok != 0);
}

void listarUsuarios() {
  clrscr();
  Usuario* usuarios = listaUsuarios();

  if (usuarios == NULL) {
    printf("Error obteniendo la lista de usuarios\n");
    return;
  }

  printf("DNI\t\tUsername\n");
  printf("-------------------------\n");

  int i = 0;
  while (usuarios[i].dni != NULL) {
    printf("%s\t%s\n", usuarios[i].dni, usuarios[i].nombre);
    i++;
  }

  i = 0;
  while (usuarios[i].dni != NULL) {
    free(usuarios[i].dni);
    free(usuarios[i].nombre);
    free(usuarios[i].contraseña);
    i++;
  }
  free(usuarios);
  waitForEnter();
}