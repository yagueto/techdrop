#ifndef USUARIO_H
#define USUARIO_H

typedef struct
{
  char dni[10];
  char nombre[20];
  char contraseña[20];
} Usuario;

void usuarioDB(Usuario *user);
#endif //USUARIO_H