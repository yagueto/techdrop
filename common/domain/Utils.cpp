#include "Utils.h"
#include <iostream>
#include <limits>
using namespace std;

void waitForEnter()
{
    cout << "Presiona ENTER para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia el buffer
}