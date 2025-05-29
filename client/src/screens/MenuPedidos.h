#ifndef MENUPEDIDOS_H
#define MENUPEDIDOS_H
#include "Menu.h"


class MenuPedidos : public Menu{
public:
    MenuPedidos();
    void gestionarOpcion(int opcion) override;
};



#endif //MENUPEDIDOS_H
