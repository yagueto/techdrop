//
// Created by asier.amigorena on 22/05/2025.
//

#include "Menu.h"
#include <iostream>

#include "domain/utils.h"


using namespace std;

Menu::Menu(const string &title, const int numOptions) {
    this->title = title;
    this->numOptions = numOptions;
    this->options = new string[numOptions];
    this->handlers = static_cast<void (**)()>(malloc(numOptions * sizeof(void(*)())));
}

void Menu::addOption(const int index, const string &option, void (*handler)()) {
    this->options[index] = option;
    this->handlers[index] = handler;
}

void Menu::showMenu() {
    do
    {
        system("clear"); // Limpiar pantalla antes de dibujar menú
        clrscr();
        // Cabecera del programa
        cout << " _            _         _                 \n"
             << "| |_ ___  ___| |__   __| |_ __ ___  _ __  \n"
             << "| __/ _ \\/ __| '_ \\ / _` | '__/ _ \\| '_ \\ \n"
             << "| ||  __/ (__| | | | (_| | | | (_) | |_) |\n"
             << " \\__\\___|\\___| |_|_|\\__,_|_|  \\___/| .__/ \n"
             << "                                   |_|    \n" << endl;
        cout << "-----" << this->title << "----\n" << endl;
        for (int i = 0; i < this->numOptions; ++i)
        {
            printf("%d: %s\n", i + 1, this->options[i]);
        }
        printf("0: Volver\n");
        int opcion;
        do
            {
            printf("Elige una opción: ");
            fflush(stdout);
            scanf("%d", &opcion);
            clearInputBuffer();

            if (opcion == 0) return;

            if (this->handlers[opcion - 1] == NULL) printf("Aún no implementado\n");
            }
        while (opcion < 0 || opcion > this->numOptions || this->handlers[opcion - 1] == NULL);
        this->handlers[opcion - 1]();
        }
    while (1);
}

Menu::~Menu() {

}

void Menu::initializeMenus() {
    Menu *menuPrincipal = new Menu("Menú principal", 4);
    /*
    addOption(menuPrincipal, 0, "Gestionar menú", handle_menuPlatos);
    addOption(menuPrincipal, 1, "Gestionar cuentas", handle_menuCuentas);
    addOption(menuPrincipal, 2, "Gestionar robots", handle_menuRobots);
    addOption(menuPrincipal, 3, "Estadísticas", handle_menuEstadisticas);
    */
}
