

#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H
#include "Menu.h"


class MenuPrincipal : public Menu{
public:
    MenuPrincipal();
    void gestionarOpcion(int opcion) override;
};

#endif //MENUPRINCIPAL_H
