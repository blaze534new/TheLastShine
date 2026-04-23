#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "palette.h"
#include "entity.h"
#include "menu.h"
using namespace std;

int main() {
    srand(time(NULL));

    // Abilita colori ANSI su Windows
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Dichiarazione entità giocatore
    Entity giocatore("Eroe", "Guerriero", 40, 16, 12, 1, 4, 0);

    menuiniziale();

    return 0;
}
