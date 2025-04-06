#ifndef BD_USUARIO_H
#define BD_USUARIO_H
#include <sqlite3.h>
#include <models/usuario.h>

Usuario* obtenerUsuario(char *param, char* type);
int eliminarUsuario(Usuario *usuario);
int insertarUsuario(Usuario *usuario);

#endif //BD_USUARIO_H
