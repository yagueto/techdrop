#ifndef MENUINICIO_H
#define MENUINICIO_H
#include "Menu.h"


class MenuInicio : public Menu{
public:
    MenuInicio();
    void gestionarOpcion(int opcion) override;
};



#endif //MENUINICIO_H
