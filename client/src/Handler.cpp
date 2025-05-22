#include "Handler.h"

#include <cstddef>

#include "Menu.h"

Handler::Handler()
{
    this->menu = NULL;
}
Handler::~Handler()
{
    delete [] this->menu;
}
void Handler::setMenu(Menu* menu)
{
    this->menu = menu;
}