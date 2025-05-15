#ifndef USUARIO_H
#define USUARIO_H

typedef struct
{
  char *dni;
  char *nombre;
  char *contraseña;
} Usuario;

void freeUsuario(Usuario *user);
#endif //USUARIO_H