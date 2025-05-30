#ifndef MENUUSUARIO_H
#define MENUUSUARIO_H
#include "Menu.h"


class MenuUsuario : public Menu{
public:
  MenuUsuario(const Socket &socket);
  void gestionarOpcion(int opcion) override;
};



#endif //MENUUSUARIO_H
