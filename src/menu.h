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

#endif //MENU_H
