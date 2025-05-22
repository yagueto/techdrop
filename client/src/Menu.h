//
// Created by asier.amigorena on 22/05/2025.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>

using namespace std;

class Menu {
    string title;
    string* options;
    int numOptions;
    void (**handlers)();
public:
    Menu(const string &title, const int numOptions);
    void addOption(int index, const string &option, void (*handler)());
    void initializeMenus();
    void showMenu();
    virtual ~Menu();
};

#endif //MENU_H
