#ifndef USUARIO_H
#define USUARIO_H

typedef struct
{
  char nombre[20];
  char contraseña[20];
}usuario;

char menuUsuario();
void crearUsuario(usuario *user);
int gestionar_respuesta();

#endif //USUARIO_H