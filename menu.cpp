#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "menu.h"
#include "palette.h"
#include "mappa.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <windows.h>
using namespace std;

// ─────────────────────────────────────────
//  UTILITY
// ─────────────────────────────────────────

void testo(const char* t, int secondi) {

    cout << t << endl;

    // Aspetta solo 10 millisecondi prima del prossimo controllo
    this_thread::sleep_for(chrono::seconds(secondi));


    system("cls");
}

// ─────────────────────────────────────────
//  STORIA INIZIALE
// ─────────────────────────────────────────

void storiainizio() {
    testo("THE LAST SHINE", 1);
    testo("Firenze, 1480.", 1);
    testo("Una città costruita sopra la memoria.", 1);
    testo("E sotto… qualcosa che non è mai morto.", 1);
    testo("Sotto le strade vive una città che nessuno deve vedere.", 2);
    testo("Un tempio romano sepolto, dimenticato dal tempo.", 2);
    testo("Una cerchia di nobili eruditi lo ha riportato alla luce.", 2);
    testo("I Neoplatonici.", 1);
    testo("Cercavano conoscenza.", 1);
    testo("Hanno trovato qualcosa di diverso.", 2);
    testo("Non era sapere.", 1);
    testo("Era fame.", 1);
    testo(" si risveglia.", 2);
    testo("Senza età.", 1);
    testo("Senza pace.", 1);
    testo("Senza morte.", 1);
    testo("Ater Mortis un comandante romano sopravvissuto alle Idi di marzo.", 2);
    testo("Legato a un frammento divino.", 1);
    testo("La Scintilla di Quirino.", 1);
    testo("Un potere antico.", 1);
    testo("Una coscienza spezzata.", 1);
    testo("Un ciclo che non si è mai fermato.", 2);
    testo("Ora è prigioniero.", 1);
    testo("Nell'Arena delle Ombre.", 1);
    testo("E ogni combattimento…", 1);
    testo("lo sta riportando indietro.", 1);
}

// ─────────────────────────────────────────
//  NEGOZIO FABBRO
// ─────────────────────────────────────────

void negoziofabbro() {
    int scelta;

    cout << "==============================" << endl;
    cout << "        NEGOZIO ARMI          " << endl;
    cout << "==============================" << endl;
    cout << " 1) Gladio - 50"                     << endl;
    cout << " 2) Spatha - 100"                     << endl;
    cout << " 3) Pugio"                      << endl;
    cout << " 4) Lancia Frammentata"         << endl;
    cout << " 5) Ascia Spacca Scudi"         << endl;
    cout << " 6) Ascia Spacca Cranio"        << endl;
    cout << " 7) Spada del Generale"         << endl;
    cout << " 8) Spada dell'Imperatore"      << endl;
    cout << "==============================" << endl;
    cout << "Scegli un'arma da comprare: ";
    cin >> scelta;
    cout << endl;

    switch (scelta) {
        case 1: if (Inventario.monete >= 50) {
            cout << "Hai comprato: Gladio!" << endl;
        } break;

        case 2: cout << "Hai comprato: Spatha!"              << endl; break;
        case 3: cout << "Hai comprato: Pugio!"               << endl; break;
        case 4: cout << "Hai comprato: Lancia Frammentata!"  << endl; break;
        case 5: cout << "Hai comprato: Ascia Spacca Scudi!"  << endl; break;
        case 6: cout << "Hai comprato: Ascia Spacca Cranio!" << endl; break;
        case 7: cout << "Hai comprato: Spada del Generale!"  << endl; break;
        case 8: cout << "Hai comprato: Spada dell'Imperatore!" << endl; break;
        default: cout << "Scelta non valida!" << endl;
    }
}

// ─────────────────────────────────────────
//  CREDITI
// ─────────────────────────────────────────

void crediti() {
    cout << "\033[2J\033[H";
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;
    cout << p.red << p.bold  << "        CREDITI THE LAST SHINE        " << p.reset << endl;
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;

    cout << p.blu   << "Titolo del gioco:"       << p.green  << " THE LAST SHINE"                                                              << p.reset << endl;
    cout << p.blu   << "Sviluppatori:"           << p.giallo << " Lernetti Biagio, D'Agnese Alessandro, Malizzi Marco, Volpi Emanuele, Favilli Dieudonnè" << p.reset << endl;
    cout << p.blu   << "Programmazione: "        << p.gold   << "Lernetti Biagio, Malizzi Marco, D'Agnese Alessandro, Volpi Emanuele, Favilli Dieudonnè"                                                             << p.reset << endl;
    cout << p.blu   << "Grafica: "               << p.red    << "Lernetti Biagio, Volpi Emanuele"                                              << p.reset << endl;
    cout << p.blu   << "Programmazzione HTML:"   << p.cyan   << " Malizzi Marco"                                                               << p.reset << endl;
    cout << p.blu   << "Testing: "               << p.pink   << " Malizzi Marco, Favilli Dieudonnè"                                           << p.reset << endl;
    cout << "ALTRE COSE SE CI VENGONO IN MENTE: [INSERISCI_TESTO]" << endl;

    cout << "=================================" << endl;
    cout << "   Grazie per aver giocato <3!   " << endl;
    cout << "=================================" << endl;
    system("pause");
}

// ─────────────────────────────────────────
//  GIOCA
// ─────────────────────────────────────────

void gioca() {
    // Per ora il flusso di gioco parte dalla storia introduttiva.
    storiainizio();
    gameLoop();
    //g++ main.cpp combat.cpp menu.cpp mappa.cpp -o TheLastShine
    cout <<"FINE GIOCO";
}

// ─────────────────────────────────────────
//  MENU INIZIALE
// ─────────────────────────────────────────

void manuale() {
    cout << "Questo è il MANUALE del gioco, questi sono tutti i comandi che ti seviranno per giocare!" << endl;
    cout << "========================================================================================" << endl;
    cout << "Comando 1" << endl;
    cout << "comando 2" << endl;
    cout << "comando 3" << endl;
    cout << "comando 4" << endl;
    cout << "========================================================================================" << endl;
    system("pause");
}

void menuiniziale() {
    int scelta;

    cout << p.blu   << "_________          _______  " << p.red   << "  _        _______  _______ _________ " << p.green << "  _______          _________ _        _______ "          << endl;
    cout << p.blu   << "\\__   __/|\\     /|(  ____ \\ " << p.red   << " ( \\      (  ___  )(  ____ \\\\__   __/" << p.green << "  (  ____ \\|\\     /|\\__   __/( (    /|(  ____ \\" << endl;
    cout << p.blu   << "   ) (   | )   ( || (    \\/ " << p.red   << " | (      | (   ) || (    \\/   ) (   " << p.green << "  | (    \\/| )   ( |   ) (   |  \\  ( || (    \\/"          << endl;
    cout << p.blu   << "   | |   | (___) || (__     " << p.red   << " | |      | (___) || (_____    | |   " << p.green << "  | (_____ | (___) |   | |   |   \\ | || (__    "            << endl;
    cout << p.blu   << "   | |   |  ___  ||  __)    " << p.red   << " | |      |  ___  |(_____  )   | |   " << p.green << "  (_____  )|  ___  |   | |   | (\\ \\) ||  __)   "          << endl;
    cout << p.blu   << "   | |   | (   ) || (       " << p.red   << " | |      | (   ) |      ) |   | |   " << p.green << "        ) || (   ) |   | |   | | \\   || (      "            << endl;
    cout << p.blu   << "   | |   | )   ( || (____/\\" << p.red   << "  | (____/\\| )   ( |/\\____) |   | |   " << p.green << "  /\\____) || )   ( |___) (___| )  \\  || (____/\\"        << endl;
    cout << p.blu   << "   )_(   |/     \\|(_______/ " << p.red   << " (_______/|/     \\|\\_______)   )_(   " << p.green << "  \\_______)|/     \\|\\_______/|/    )_)(_______/" << p.reset << endl;

    while (true) {
        cout << endl << endl;
        cout << setw(10) << "" << "1. " << p.giallo << "GIOCA"   << p.reset << endl;
        cout << setw(10) << "" << "2. " << p.giallo << "MANUALE" << p.reset << endl;
        cout << setw(10) << "" << "3. " << p.giallo << "CREDITI" << p.reset << endl;
        cout << setw(10) << "" << "4. " << p.giallo << "ESCI"    << p.reset << endl;

        cout << "\n   =====================" << endl;
        cout << "   Scelta: ";
        cin >> scelta;

        switch (scelta) {
            case 1: gioca();    break;
            case 2: manuale();  break; // manuale da implementare
            case 3: crediti();  break;
            case 4: exit(0);
        }
    }
}
