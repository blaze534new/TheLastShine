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
    string underline = "\033[4m";
    string reverse = "\033[7m";
    string black = "\033[30m";
    string red = "\033[31m";
    string green = "\033[32m";
    string giallo = "\033[33m";
    string blu = "\033[34m";
    string purple = "\033[35m";
    string cyan = "\033[36m";
    string gold = "\033[38;5;214m";
    string pink = "\033[38;5;198m";
    string rossoSangue = "\033[38;5;124m";
    string corallo = "\033[38;5;203m";
    string arancioScuro = "\033[38;5;166m";
    string pesca = "\033[38;5;216m";
    string mattone = "\033[38;5;130m";
    string smeraldo = "\033[38;5;47m";
    string oliva = "\033[38;5;100m";
    string lime = "\033[38;5;191m";
    string menta = "\033[38;5;121m";
    string verdeAcido = "\033[38;5;112m";
    string celeste = "\033[38;5;153m";
    string bluReale = "\033[38;5;27m";
    string turchese = "\033[38;5;45m";
    string indaco = "\033[38;5;54m";
    string bluAcciaio = "\033[38;5;67m";
    string lilla = "\033[38;5;183m";
    string prugna = "\033[38;5;96m";
    string fucsia = "\033[38;5;201m";
    string orchidea = "\033[38;5;170m";
    string violaNotte = "\033[38;5;17m";
    string cioccolato = "\033[38;5;52m";
    string bronzo = "\033[38;5;136m";
    string argento = "\033[38;5;249m";
    string platino = "\033[38;5;253m";
    string rame = "\033[38;5;167m";
    string fumo = "\033[38;5;240m";
    string grafite = "\033[38;5;236m";
    string nebbia = "\033[38;5;251m";
    string asfalto = "\033[38;5;234m";
    string osso = "\033[38;5;230m";
    string marrone = "\033[38;5;94m";
    string verdeBosco = "\033[38;5;22m";
    string grigioPietra = "\033[38;5;244m";
    string sabbia = "\033[38;5;222m";
    string fuoco = "\033[38;5;202m";
    string ghiaccio = "\033[38;5;123m";
    string fulmine = "\033[38;5;226m";
    string veleno = "\033[38;5;46m";
    string ombra = "\033[38;5;55m";
    string sacro = "\033[38;5;231m";
    string vitaBassa = "\033[38;5;196m";
    string monetaRara = "\033[38;5;220m";
    string leggendario = "\033[38;5;201m";
    string grigioScuro = "\033[38;5;236m";
    string bgRed = "\033[41m";
    string bgBlue = "\033[44m";
    string bgLava = "\033[48;5;160m";
    string bgForesta = "\033[48;5;22m";
    string bgAbisso = "\033[48;5;232m";
    string bgOro = "\033[48;5;214m";
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
inline Arma catalogo[3] = {
    {1, "Gladio", 6},
    {2, "Spatha", 8},
    {3, "Ascia", 8},
};
inline Spell spellBook[3] = {
    {"Palla di Fuoco", 1, 15, 0},
    {"Fulmine", 2, 12, 0},
    {"Cura Rapida", 21, 0, 20},
};

inline int getDadoArma(int id) {
    for (int i = 0; i < 3; i++)
        if (catalogo[i].ID == id) return catalogo[i].dado;
    return 4;
}

inline int tiraDado(int facce) {
    return (rand() % facce) + 1;
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
          player_loc_y(startY) {
        inv.monete = 0;
        inv.frammenti_ferro = 0;
        inv.acciaio = idArma;
    }

    int mod(int stat) { return (stat - 10) / 2; }
    int CA() { return 10 + mod(DES); }
    int bonusAtk() { return mod(FOR) + (liv / 4 + 2); }
    int dannoArma() { return tiraDado(getDadoArma(idArma)) + mod(FOR); }
    bool isVivo() { return hp > 0; }
    bool sottoTrentoPercento() { return hp < (hpMax * 30) / 100; }
};

Entity nemiciCatalogo[] = {
    Entity("Goblin", "Guerriero", 20, 10, 10, 1, 1, 0),
    Entity("Orc", "Barbaro", 30, 14, 8, 2, 3, 0),
    Entity("Stregone", "Mago", 25, 8, 12, 1, 2, 3),
};
int NUM_NEMICI_CATALOGO = 3;

void menuiniziale();
void gioca();
void crediti();
void storiainizio();
void negoziofabbro(Entity& giocatore);
void testo(const char* testo, int secondi);
void gameLoop(Entity& giocatore);
void stampaStato(const Entity& giocatore, const Entity& nemico);
int attaccaFisico(Entity& attaccante, Entity& bersaglio);
void usaIncantesimo(Entity& giocatore, Entity& nemico);
int difenditi(Entity& giocatore);
void turnoNemico(Entity& nemico, Entity& giocatore, int bonusCAGiocatore);
void combatManager(Entity& giocatore, Entity& nemico);
void combatManagerTutorial(Entity& giocatore, Entity& nemico);

void testo(const char* t, int secondi) {
    cout << t << endl;
    this_thread::sleep_for(chrono::seconds(secondi));
    system("cls");
}

void storiainizio() {
    testo("THE LAST SHINE", 3);
    testo("Firenze, 1480.", 3);
    testo("Una citta costruita sopra la memoria.", 3);
    testo("E sotto... qualcosa che non e mai morto.", 3);
    testo("Sotto le strade vive una citta che nessuno deve vedere.", 4);
    testo("Un tempio romano sepolto, dimenticato dal tempo.", 3);
    testo("Una cerchia di nobili eruditi lo ha riportato alla luce.", 3);
    testo("I Neoplatonici.", 2);
    testo("Cercavano conoscenza.", 2);
    testo("Hanno trovato qualcosa di diverso.", 3);
    testo("Non era sapere.", 2);
    testo("Era fame.", 3);
    testo(" si risveglia.", 3);
    testo("Senza eta.", 2);
    testo("Senza pace.", 2);
    testo("Senza morte.", 3);
    testo("Ater Mortis un comandante romano sopravvissuto alle Idi di marzo.", 4);
    testo("Legato a un frammento divino.", 3);
    testo("La Scintilla di Quirino.", 3);
    testo("Un potere antico.", 2);
    testo("Una coscienza spezzata.", 2);
    testo("Un ciclo che non si e mai fermato.", 3);
    testo("Ora e prigioniero.", 2);
    testo("Nell'Arena delle Ombre.", 3);
    testo("E ogni combattimento...", 2);
    testo("lo sta riportando indietro.", 3);
}

void negoziofabbro(Entity& giocatore) {
    int scelta;

    cout << "==============================" << endl;
    cout << "        NEGOZIO ARMI          " << endl;
    cout << "==============================" << endl;
    cout << " 1) Gladio" << endl;
    cout << " 2) Spatha" << endl;
    cout << " 3) Pugio" << endl;
    cout << " 4) Lancia Frammentata" << endl;
    cout << " 5) Ascia Spacca Scudi" << endl;
    cout << " 6) Ascia Spacca Cranio" << endl;
    cout << " 7) Spada del Generale" << endl;
    cout << " 8) Spada dell'Imperatore" << endl;
    cout << "==============================" << endl;
    cout << "Scegli un'arma da comprare: ";
    cin >> scelta;
    cout << endl;

    switch (scelta) {
        case 1:
            if (armi.gladio) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 50) {
                giocatore.inv.monete -= 50;
                armi.gladio = true;
                cout << "Hai comprato: Gladio!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 2:
            if (armi.spatha) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 100) {
                giocatore.inv.monete -= 100;
                armi.spatha = true;
                cout << "Hai comprato: Spatha!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 3:
            if (armi.pugio) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 150) {
                giocatore.inv.monete -= 150;
                armi.pugio = true;
                cout << "Hai comprato: Pugio!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 4:
            if (armi.lancia) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 200) {
                giocatore.inv.monete -= 200;
                armi.lancia = true;
                cout << "Hai comprato: Lancia Frammentata!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 5:
            if (armi.asciascudi) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 250) {
                giocatore.inv.monete -= 250;
                armi.asciascudi = true;
                cout << "Hai comprato: Ascia Spacca Scudi!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 6:
            if (armi.asciacranio) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 300) {
                giocatore.inv.monete -= 300;
                armi.asciacranio = true;
                cout << "Hai comprato: Ascia Spacca Cranio!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 7:
            if (armi.spadagenerale) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 350) {
                giocatore.inv.monete -= 350;
                armi.spadagenerale = true;
                cout << "Hai comprato: Spada del Generale!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        case 8:
            if (armi.spadaimperatore) {
                cout << "Hai gia questo oggetto!" << endl;
            } else if (giocatore.inv.monete >= 400) {
                giocatore.inv.monete -= 400;
                armi.spadaimperatore = true;
                cout << "Hai comprato: Spada dell'Imperatore!" << endl;
            } else {
                cout << "Monete insufficienti!" << endl;
            }
            break;
        default:
            cout << "Scelta non valida!" << endl;
    }

    cout << "Monete rimaste: " << giocatore.inv.monete << endl;
}

void crediti() {
    cout << "\033[2J\033[H";
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;
    cout << p.red << p.bold << "        CREDITI THE LAST SHINE        " << p.reset << endl;
    cout << p.bgRed << p.red << "======================================" << p.reset << endl;

    cout << p.blu << "Titolo del gioco:" << p.green << " THE LAST SHINE" << p.reset << endl;
    cout << p.blu << "Sviluppatori:" << p.giallo
         << " Lernetti Biagio, D'Agnese Alessandro, Malizzi Marco, Volpi Emanuele, Favilli Dieoudonne"
         << p.reset << endl;
    cout << p.blu << "Programmazione: " << p.gold << "[INSERISCI_NOMI]" << p.reset << endl;
    cout << p.blu << "Grafica: " << p.red << "Lernetti Biagio, Volpi Emanuele" << p.reset << endl;
    cout << p.blu << "Programmazzione HTML:" << p.cyan << " Malizzi Marco" << p.reset << endl;
    cout << p.blu << "Testing: " << p.pink << " Malizzi Marco, Favilli Dieoudonne" << p.reset << endl;
    cout << "ALTRE COSE SE CI VENGONO IN MENTE: [INSERISCI_TESTO]" << endl;
    cout << "=================================" << endl;
    cout << "   Grazie per aver giocato <3!   " << endl;
    cout << "=================================" << endl;
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
    cout << giocatore.name << " (" << giocatore.classe << ")" << " VS " << nemico.name << " (" << nemico.classe << ")\n";

    while (giocatore.isVivo() && nemico.isVivo()) {
        stampaStato(giocatore, nemico);
        cout << "\nAzione:\n";
        cout << "1. Attacca\n";
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
    cout << giocatore.name << " (" << giocatore.classe << ")" << " VS " << nemico.name << " (" << nemico.classe << ")\n";
    testo("Benvenuto nell'arena e nel tuo primo combattimento", 1);
    testo("Il combattimento e a turno avrai un turno per attaccare ma anche il nemico avra un turno per attaccarti", 2);
    testo("Sfrutta una tua strategia per battere i nemici alternando difesa e attacco", 2);
    testo("Le azioni principali che puoi fare sono:", 1);
    testo("1) Attacco lancerai un D20(Dado a 20 facce) e il risultato del dado determinera quanti danni farai", 1);
    testo("oltre ai danni dati dal risultato del dado puoi avere dei bonus attacco in base alla classe e/o ai bonus che sbloccherai nel gioco", 1);
    testo("2) Usa incantesimo", 1);

    while (giocatore.isVivo() && nemico.isVivo()) {
        stampaStato(giocatore, nemico);
        cout << "\nAzione:\n";
        cout << "1. Attacca\n";
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

void gameLoop(Entity& giocatore) {
    bool tutorialFatto = false;

    while (giocatore.isVivo()) {
        system("CLS");
        cout << "=== ARENA ===\n";
        cout << "HP: " << giocatore.hp << "/" << giocatore.hpMax << " | Monete: " << giocatore.inv.monete << "\n";
        cout << "1. Tutorial combattimento\n";
        cout << "2. Combattimento normale\n";
        cout << "3. Negozio fabbro\n";
        cout << "4. Esci\n> ";

        int scelta;
        cin >> scelta;

        if (scelta == 1) {
            Entity nemicoTutorial("Nemico", "Barbaro", 30, 14, 10, 2, 1, 0);
            combatManagerTutorial(giocatore, nemicoTutorial);
            tutorialFatto = true;
            if (giocatore.isVivo()) giocatore.inv.monete += 25;
        } else if (scelta == 2) {
            if (!tutorialFatto) {
                cout << "Prima completa il tutorial.\n";
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }
            Entity nemico = nemiciCatalogo[rand() % NUM_NEMICI_CATALOGO];
            combatManager(giocatore, nemico);
            if (giocatore.isVivo()) giocatore.inv.monete += 25;
        } else if (scelta == 3) {
            negoziofabbro(giocatore);
            this_thread::sleep_for(chrono::seconds(1));
        } else if (scelta == 4) {
            break;
        } else {
            cout << "Scelta non valida.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void gioca() {
    Entity giocatore("Eroe", "Guerriero", 40, 16, 12, 1, 4, 0);
    gameLoop(giocatore);
}

void menuiniziale() {
    int scelta;

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
    cout << "   =====================" << endl << endl;

    cout << left;
    cout << setw(10) << "" << "1. " << p.giallo << "GIOCA" << p.reset << endl;
    cout << setw(10) << "" << "2. " << p.giallo << "MANUALE" << p.reset << endl;
    cout << setw(10) << "" << "3. " << p.giallo << "CREDITI" << p.reset << endl;
    cout << setw(10) << "" << "4. " << p.giallo << "ESCI" << p.reset << endl;

    cout << "\n   =====================" << endl;
    cout << "   Scelta: ";
    cin >> scelta;

    switch (scelta) {
        case 1:
            gioca();
            break;
        case 2:
            break;
        case 3:
            crediti();
            break;
        case 4:
            exit(0);
        default:
            break;
    }
}

int main() {
    srand(time(NULL));

    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    menuiniziale();
    return 0;
}
