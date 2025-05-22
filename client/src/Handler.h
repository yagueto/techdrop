//
// Created by naia.martin on 21/05/2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "Menu.h"


class Handler {
protected:
    Menu* menu;
public:
    Handler();
    virtual ~Handler();
    void setMenu(Menu* menu);

    virtual void gestionarOpcion(int opcion) = 0;
};



#endif //HANDLER_H
