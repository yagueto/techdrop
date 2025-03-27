//
// Created by yaguete on 27/03/25.
//

#ifndef MENU_H
#define MENU_H
typedef struct
{
    char* title;
    char** options;
    int numOptions;
    void (**handlers)();
} Menu;


void initializeMenus();

#ifdef _WIN32
#define clrscr() system("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#endif //MENU_H
