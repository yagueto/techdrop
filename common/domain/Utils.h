#ifndef UTILS_H
#define UTILS_H

void clearIfNeeded(char *str, int max_line);
void waitForEnter();
void getDate(char* buffer, int size);
void clearInputBuffer();

#ifdef _WIN32
#define clrscr() system("cls")
#else
#include <iostream>
#define clrscr() std::cout << "\e[1;1H\e[2J";
#endif

#endif //UTILS_H
