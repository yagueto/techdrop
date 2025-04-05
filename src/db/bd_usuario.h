#ifndef BD_USUARIO_H
#define BD_USUARIO_H
#include <sqlite3.h>
#include <estructuras/usuario.h>

Usuario* obtenerUsuario(sqlite3 *db, char *dni);
int eliminarUsuario(sqlite3 *db, Usuario *usuario);

#endif //BD_USUARIO_H
