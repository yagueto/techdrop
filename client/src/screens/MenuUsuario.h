#ifndef MENUUSUARIO_H
#define MENUUSUARIO_H
#include <domain/Usuario.h>

#include "Globals.h"
#include "Menu.h"


class MenuUsuario : public Menu{
  Usuario usuario = Globals::usuario_actual;
public:
  MenuUsuario(const Socket &socket);
  void gestionarOpcion(int opcion) override;
};



#endif //MENUUSUARIO_H
