#ifndef UTILS_H
#define UTILS_H
void clearIfNeeded(char *str, int max_line);
void waitForEnter();
void getDate(char* buffer, int size);

#ifdef _WIN32
#define clrscr() system("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#endif //UTILS_H
