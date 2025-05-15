#include "usuario.h"

#include <stdlib.h>

void freeUsuario(Usuario *user){
    free(user->dni);
    free(user->nombre);
    free(user->contraseña);
    free(user);
}
