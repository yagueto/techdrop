

#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include "Menu.h"

class MenuPrincipal : public Menu {
public:
  explicit MenuPrincipal(const Socket &socket);
  void gestionarOpcion(int opcion) override;
};

#endif // MENUPRINCIPAL_H
