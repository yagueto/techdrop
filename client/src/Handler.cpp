//
// Created by naia.martin on 21/05/2025.
//

#include "Handler.h"
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