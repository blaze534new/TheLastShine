#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "palette.h"
#include "entity.h"
#include "menu.h"
using namespace std;

int main() {
    // Inizializza il generatore casuale per dadi, eventi e combattimento.
    srand(time(NULL));

    // Abilita i colori ANSI su Windows (necessari per la palette nel terminale).
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Crea il personaggio principale con statistiche iniziali.
    // Parametri: nome, classe, hp, FOR, DES, idArma, livello, numeroSpell.
    Entity giocatore("Eroe", "Guerriero", 40, 16, 12, 1, 4, 0);

    // Avvia il menu iniziale (porta d'ingresso di tutto il gioco).
    menuiniziale();

    return 0;
}
