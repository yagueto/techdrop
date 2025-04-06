#ifndef BD_USUARIO_H
#define BD_USUARIO_H
#include <models/usuario.h>

Usuario* obtenerUsuario(char *param, char* type);
int eliminarUsuario(Usuario *usuario);
int insertarUsuario(Usuario *usuario);
void listarUsuarios();

#endif //BD_USUARIO_H
