#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <windows.h>
using namespace std;

struct Palette {
    string reset = "\033[0m";
    string bold = "\033[1m";
    string red = "\033[31m";
    string green = "\033[32m";
    string giallo = "\033[33m";
    string blu = "\033[34m";
    string cyan = "\033[36m";
    string gold = "\033[38;5;214m";
    string pink = "\033[38;5;198m";
    string bgRed = "\033[41m";
};
inline Palette p;

struct Arma {
    int ID;
    string nome;
    int dado;
};

struct Spell {
    string name;
    int ID;
    int danno;
    int cura;
};

struct armamentario {
    bool gladio = false;
    bool spatha = false;
    bool pugio = false;
    bool lancia = false;
    bool spadagenerale = false;
    bool asciascudi = false;
    bool asciacranio = false;
    bool spadaimperatore = false;
};

inline armamentario armi;
inline Arma catalogo[3] = {{1, "Gladio", 6}, {2, "Spatha", 8}, {3, "Ascia", 8}};
inline Spell spellBook[3] = {
    {"Palla di Fuoco", 1, 15, 0},
    {"Fulmine", 2, 12, 0},
    {"Cura Rapida", 21, 0, 20},
};

inline int tiraDado(int facce) {
    return (rand() % facce) + 1;
}

inline int getDadoArma(int id) {
    for (int i = 0; i < 3; i++) {
        if (catalogo[i].ID == id) return catalogo[i].dado;
    }
    return 4;
}

struct inventario {
    int monete = 0;
    int frammenti_ferro = 0;
    int lingotto_ferro = 0;
    int acciaio = 0;
    int rutilo = 0;
    int ilmenite = 0;
    int titanio = 0;
    int legno = 0;
};

class Entity {
public:
    string name;
    string classe;
    int hp, hpMax;
    int FOR, DES;
    int idArma;
    int liv;
    int numSpell;
    bool haUsatoCura;
    int player_loc_x;
    int player_loc_y;
    inventario inv;

    Entity(string n, string cl, int h, int f, int d, int arma, int l, int sp, int startX = 1, int startY = 1)
        : name(n),
          classe(cl),
          hp(h),
          hpMax(h),
          FOR(f),
          DES(d),
          idArma(arma),
          liv(l),
          numSpell(sp),
          haUsatoCura(false),
          player_loc_x(startX),
          player_loc_y(startY) {}

    int mod(int stat) { return (stat - 10) / 2; }
    int CA() { return 10 + mod(DES); }
    int bonusAtk() { return mod(FOR) + (liv / 4 + 2); }
    bool isVivo() { return hp > 0; }
    bool sottoTrentoPercento() { return hp < (hpMax * 30) / 100; }
};

Entity nemiciCatalogo[] = {
    Entity("Goblin", "Guerriero", 20, 10, 10, 1, 1, 0),
    Entity("Orc", "Barbaro", 30, 14, 8, 2, 3, 0),
    Entity("Stregone", "Mago", 25, 8, 12, 1, 2, 3),
};
int NUM_NEMICI_CATALOGO = 3;

void testo(const char* t, int secondi) {
    cout << t << endl;
    this_thread::sleep_for(chrono::seconds(secondi));
    system("cls");
}

void stampaStato(const Entity& g, const Entity& n) {
    cout << "\n========================================\n";
    cout << "[" << g.name << "]  HP: " << g.hp << "/" << g.hpMax << "   CA: " << (10 + (g.DES - 10) / 2) << "\n";
    cout << "[" << n.name << "]  HP: " << n.hp << "/" << n.hpMax << "   CA: " << (10 + (n.DES - 10) / 2) << "\n";
    cout << "========================================\n";
}

int attaccaFisico(Entity& attaccante, Entity& bersaglio) {
    int tiro = tiraDado(20);
    bool critico = (tiro == 20);
    int totale = tiro + attaccante.bonusAtk();

    cout << "\n" << attaccante.name << " attacca! [d20=" << tiro;
    if (critico) cout << " CRITICO!";
    cout << " | totale=" << totale << " vs CA=" << bersaglio.CA() << "]\n";

    if (critico || totale >= bersaglio.CA()) {
        int dado = getDadoArma(attaccante.idArma);
        int danno = tiraDado(dado) + attaccante.mod(attaccante.FOR);
        if (critico) danno += tiraDado(dado);
        if (danno < 1) danno = 1;
        bersaglio.hp -= danno;
        cout << "Colpito! Danno: " << danno << "\n";
        return danno;
    }

    cout << "Mancato!\n";
    return 0;
}

void usaIncantesimo(Entity& giocatore, Entity& nemico) {
    if (giocatore.numSpell <= 0) {
        cout << "Nessun incantesimo disponibile!\n";
        return;
    }

    cout << "\nScegli incantesimo:\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << spellBook[i].name;
        if (spellBook[i].ID <= 20)
            cout << " (Danno: " << spellBook[i].danno << ")";
        else
            cout << " (Cura: " << spellBook[i].cura << ")";
        cout << "\n";
    }

    int scelta;
    cin >> scelta;
    if (scelta < 1 || scelta > 3) {
        cout << "Scelta non valida.\n";
        return;
    }

    Spell& s = spellBook[scelta - 1];
    giocatore.numSpell--;

    if (s.ID <= 20) {
        nemico.hp -= s.danno;
        cout << giocatore.name << " lancia " << s.name << "! Danno: " << s.danno << "\n";
    } else {
        giocatore.hp += s.cura;
        if (giocatore.hp > giocatore.hpMax) giocatore.hp = giocatore.hpMax;
        cout << giocatore.name << " lancia " << s.name << "! Curati: " << s.cura << "\n";
    }
}

int difenditi(Entity& giocatore) {
    cout << "\n" << giocatore.name << " si mette in guardia! (+3 CA questo turno)\n";
    return 3;
}

void turnoNemico(Entity& nemico, Entity& giocatore, int bonusCAGiocatore) {
    cout << "\n--- Turno di " << nemico.name << " ---\n";

    if (nemico.sottoTrentoPercento() && !nemico.haUsatoCura) {
        for (int i = 0; i < 3; i++) {
            if (spellBook[i].ID >= 21 && nemico.numSpell > 0) {
                nemico.hp += spellBook[i].cura;
                if (nemico.hp > nemico.hpMax) nemico.hp = nemico.hpMax;
                nemico.numSpell--;
                nemico.haUsatoCura = true;
                cout << nemico.name << " lancia " << spellBook[i].name << "! Si cura di " << spellBook[i].cura << " HP.\n";
                return;
            }
        }
    }

    if (nemico.classe == "Mago" && nemico.numSpell > 0) {
        for (int i = 0; i < 3; i++) {
            if (spellBook[i].ID <= 20) {
                giocatore.hp -= spellBook[i].danno;
                nemico.numSpell--;
                cout << nemico.name << " lancia " << spellBook[i].name << "! Danno: " << spellBook[i].danno << "\n";
                return;
            }
        }
    }

    int tiro = tiraDado(20);
    int totale = tiro + nemico.bonusAtk();
    int caEff = giocatore.CA() + bonusCAGiocatore;

    cout << nemico.name << " attacca! [d20=" << tiro << " | totale=" << totale << " vs CA=" << caEff << "]\n";

    if (tiro == 20 || totale >= caEff) {
        int dado = getDadoArma(nemico.idArma);
        int danno = tiraDado(dado) + nemico.mod(nemico.FOR);
        if (tiro == 20) danno += tiraDado(dado);
        if (danno < 1) danno = 1;
        giocatore.hp -= danno;
        cout << "Colpito! Danno: " << danno << "\n";
    } else {
        cout << "Mancato!\n";
    }
}

void combatManager(Entity& giocatore, Entity& nemico) {
    cout << "\n*** INIZIA IL COMBATTIMENTO ***\n";
    cout << giocatore.name << " (" << giocatore.classe << ") VS " << nemico.name << " (" << nemico.classe << ")\n";

    while (giocatore.isVivo() && nemico.isVivo()) {
        stampaStato(giocatore, nemico);
        cout << "\nAzione:\n1. Attacca\n";
        if (giocatore.classe == "Mago")
            cout << "2. Usa Incantesimo (" << giocatore.numSpell << " rimasti)\n";
        else
            cout << "2. Usa Incantesimo [non disponibile per " << giocatore.classe << "]\n";
        cout << "3. Difenditi\n> ";

        int scelta;
        cin >> scelta;
        int bonusCA = 0;

        switch (scelta) {
            case 1:
                attaccaFisico(giocatore, nemico);
                break;
            case 2:
                if (giocatore.classe == "Mago")
                    usaIncantesimo(giocatore, nemico);
                else
                    cout << "I " << giocatore.classe << " non usano magie!\n";
                break;
            case 3:
                bonusCA = difenditi(giocatore);
                break;
            default:
                cout << "Scelta non valida!\n";
                break;
        }

        if (!nemico.isVivo()) break;
        turnoNemico(nemico, giocatore, bonusCA);
    }

    cout << "\n========================================\n";
    if (giocatore.isVivo())
        cout << "*** " << giocatore.name << " ha vinto! ***\n";
    else
        cout << "*** " << nemico.name << " ha vinto. Hai perso! ***\n";
    cout << "========================================\n";
}

void combatManagerTutorial(Entity& giocatore, Entity& nemico) {
    cout << "\n*** INIZIA IL TUO PRIMO COMBATTIMENTO ***\n";
    cout << giocatore.name << " (" << giocatore.classe << ") VS " << nemico.name << " (" << nemico.classe << ")\n";
    testo("Benvenuto nell'arena e nel tuo primo combattimento", 1);
    testo("Il combattimento e' a turni: giochi tu, poi il nemico.", 2);
    testo("Alterna attacco e difesa per vincere gli scontri.", 2);
    testo("Azioni disponibili: 1) Attacca 2) Incantesimo (solo mago) 3) Difenditi", 2);

    while (giocatore.isVivo() && nemico.isVivo()) {
        stampaStato(giocatore, nemico);
        cout << "\nAzione:\n1. Attacca\n";
        if (giocatore.classe == "Mago")
            cout << "2. Usa Incantesimo (" << giocatore.numSpell << " rimasti)\n";
        else
            cout << "2. Usa Incantesimo [non disponibile per " << giocatore.classe << "]\n";
        cout << "3. Difenditi\n> ";

        int scelta;
        cin >> scelta;
        int bonusCA = 0;

        switch (scelta) {
            case 1:
                attaccaFisico(giocatore, nemico);
                break;
            case 2:
                if (giocatore.classe == "Mago")
                    usaIncantesimo(giocatore, nemico);
                else
                    cout << "I " << giocatore.classe << " non usano magie!\n";
                break;
            case 3:
                bonusCA = difenditi(giocatore);
                break;
            default:
                cout << "Scelta non valida!\n";
                break;
        }

        if (!nemico.isVivo()) break;
        turnoNemico(nemico, giocatore, bonusCA);
    }

    cout << "\n========================================\n";
    if (giocatore.isVivo())
        cout << "*** " << giocatore.name << " ha completato il tutorial! ***\n";
    else
        cout << "*** Sei stato sconfitto nel tutorial. ***\n";
    cout << "========================================\n";
}

void storiainizio() {
    testo("THE LAST SHINE", 2);
    testo("Firenze, 1480.", 2);
    testo("Una citta' costruita sopra la memoria.", 2);
    testo("E sotto... qualcosa che non e' mai morto.", 2);
}

void negoziofabbro(Entity& giocatore) {
    int scelta;
    cout << "==============================\n";
    cout << "        NEGOZIO ARMI          \n";
    cout << "==============================\n";
    cout << " 1) Gladio (50)\n 2) Spatha (100)\n 3) Pugio (150)\n";
    cout << " 4) Lancia Frammentata (200)\n 5) Ascia Spacca Scudi (250)\n";
    cout << " 6) Ascia Spacca Cranio (300)\n 7) Spada del Generale (350)\n";
    cout << " 8) Spada dell'Imperatore (400)\n";
    cout << "==============================\n";
    cout << "Scegli un'arma da comprare: ";
    cin >> scelta;

    switch (scelta) {
        case 1:
            if (!armi.gladio && giocatore.inv.monete >= 50) {
                armi.gladio = true;
                giocatore.inv.monete -= 50;
                cout << "Hai comprato: Gladio!\n";
            } else
                cout << "Acquisto non possibile.\n";
            break;
        case 2:
            if (!armi.spatha && giocatore.inv.monete >= 100) {
                armi.spatha = true;
                giocatore.inv.monete -= 100;
                cout << "Hai comprato: Spatha!\n";
            } else
                cout << "Acquisto non possibile.\n";
            break;
        default:
            cout << "Scelta non valida o non ancora disponibile.\n";
            break;
    }
    cout << "Monete rimaste: " << giocatore.inv.monete << "\n";
}

void crediti() {
    cout << "\033[2J\033[H";
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;
    cout << p.red << p.bold << "        CREDITI THE LAST SHINE        " << p.reset << endl;
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;
    cout << p.blu << "Titolo del gioco:" << p.green << " THE LAST SHINE" << p.reset << endl;
    cout << p.blu << "Sviluppatori:" << p.giallo
         << " Lernetti Biagio, D'Agnese Alessandro, Malizzi Marco, Volpi Emanuele, Favilli Dieoudonne'"
         << p.reset << endl;
    cout << p.blu << "Testing: " << p.pink << " Malizzi Marco, Favilli Dieoudonne'" << p.reset << endl;
    cout << "=================================\n";
    cout << "   Grazie per aver giocato <3!   \n";
    cout << "=================================\n";
}

void gameLoop(Entity& giocatore) {
    system("cls");
    storiainizio();

    Entity nemicoTutorial("Allievo dell'Arena", "Guerriero", 18, 10, 10, 1, 1, 0);
    combatManagerTutorial(giocatore, nemicoTutorial);
    if (!giocatore.isVivo()) return;

    while (giocatore.isVivo()) {
        cout << "\n===== GAME LOOP =====\n";
        cout << "HP: " << giocatore.hp << "/" << giocatore.hpMax << " | Monete: " << giocatore.inv.monete << "\n";
        cout << "1. Nuovo combattimento\n2. Negozio fabbro\n3. Esci alla schermata principale\n> ";

        int scelta;
        cin >> scelta;
        if (scelta == 1) {
            Entity nemico = nemiciCatalogo[rand() % NUM_NEMICI_CATALOGO];
            combatManager(giocatore, nemico);
            if (giocatore.isVivo()) {
                giocatore.inv.monete += 25;
                cout << "Ricompensa: +25 monete\n";
            }
        } else if (scelta == 2) {
            negoziofabbro(giocatore);
        } else if (scelta == 3) {
            break;
        } else {
            cout << "Scelta non valida.\n";
        }
    }
}

void gioca() {
    Entity giocatore("Eroe", "Guerriero", 40, 16, 12, 1, 4, 0);
    gameLoop(giocatore);
}

void menuiniziale() {
    while (true) {
        cout << p.blu << "_________          _______  " << p.red << "  _        _______  _______ _________ " << p.green
             << "  _______          _________ _        _______ " << endl;
        cout << p.blu << "\\__   __/|\\     /|(  ____ \\ " << p.red << " ( \\      (  ___  )(  ____ \\\\__   __/" << p.green
             << "  (  ____ \\|\\     /|\\__   __/( (    /|(  ____ \\" << endl;
        cout << p.blu << "   ) (   | )   ( || (    \\/ " << p.red << " | (      | (   ) || (    \\/   ) (   " << p.green
             << "  | (    \\/| )   ( |   ) (   |  \\  ( || (    \\/" << endl;
        cout << p.blu << "   | |   | (___) || (__     " << p.red << " | |      | (___) || (_____    | |   " << p.green
             << "  | (_____ | (___) |   | |   |   \\ | || (__    " << endl;
        cout << p.blu << "   | |   |  ___  ||  __)    " << p.red << " | |      |  ___  |(_____  )   | |   " << p.green
             << "  (_____  )|  ___  |   | |   | (\\ \\) ||  __)   " << endl;
        cout << p.blu << "   | |   | (   ) || (       " << p.red << " | |      | (   ) |      ) |   | |   " << p.green
             << "        ) || (   ) |   | |   | | \\   || (      " << endl;
        cout << p.blu << "   | |   | )   ( || (____/\\" << p.red << "  | (____/\\| )   ( |/\\____) |   | |   " << p.green
             << "  /\\____) || )   ( |___) (___| )  \\  || (____/\\" << endl;
        cout << p.blu << "   )_(   |/     \\|(_______/ " << p.red << " (_______/|/     \\|\\_______)   )_(   " << p.green
             << "  \\_______)|/     \\|\\_______/|/    )_)(_______/" << p.reset << endl;

        cout << "\n      " << p.red << p.bold << "THE LAST SHINE" << p.reset << endl;
        cout << "   =====================\n\n";
        cout << left;
        cout << setw(10) << "" << "1. " << p.giallo << "GIOCA" << p.reset << endl;
        cout << setw(10) << "" << "2. " << p.giallo << "MANUALE" << p.reset << endl;
        cout << setw(10) << "" << "3. " << p.giallo << "CREDITI" << p.reset << endl;
        cout << setw(10) << "" << "4. " << p.giallo << "ESCI" << p.reset << endl;
        cout << "\n   =====================\n";
        cout << "   Scelta: ";

        int scelta;
        cin >> scelta;
        system("cls");

        switch (scelta) {
            case 1:
                gioca();
                break;
            case 2:
                cout << "Manuale in lavorazione.\n";
                break;
            case 3:
                crediti();
                break;
            case 4:
                return;
            default:
                cout << "Scelta non valida.\n";
                break;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    menuiniziale();
    return 0;
}
