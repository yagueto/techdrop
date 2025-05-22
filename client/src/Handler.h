#ifndef HANDLER_H
#define HANDLER_H

class Menu;//declaracion adelantada

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
