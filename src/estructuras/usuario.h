#ifndef USUARIO_H
#define USUARIO_H

typedef struct
{
  char nombre[20];
  char contraseña[20];
} Usuario;

void crearUsuario(Usuario *user);

#endif //USUARIO_H