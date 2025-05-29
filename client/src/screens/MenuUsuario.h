#ifndef MENUUSUARIO_H
#define MENUUSUARIO_H
#include "Menu.h"


class MenuUsuario : public Menu{
public:
    MenuUsuario();
    void gestionarOpcion(int opcion) override;
};



#endif //MENUUSUARIO_H
