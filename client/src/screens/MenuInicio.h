#ifndef MENUINICIO_H
#define MENUINICIO_H
#include "Menu.h"

class MenuInicio : public Menu {
public:
  MenuInicio(const Socket &socket);
  void gestionarOpcion(int opcion) override;
};

#endif // MENUINICIO_H
