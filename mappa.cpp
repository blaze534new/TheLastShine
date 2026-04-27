#include "mappa.h"
#include "catalogo.h"
#include "combat.h"
using namespace std;

// ─────────────────────────────────────────
//  CATALOGO NEMICI
// ─────────────────────────────────────────

Entity nemiciCatalogo[] = {
    Entity("Goblin",    "Guerriero", 20, 10, 10, 1, 1, 0),
    Entity("Orc",       "Barbaro",   30, 14, 8,  2, 3, 0),
    Entity("Stregone",  "Mago",      25, 8,  12, 1, 2, 3),
};

int NUM_NEMICI_CATALOGO = 3;

// ─────────────────────────────────────────
//  INIZIALIZZA MAPPA
// ─────────────────────────────────────────

void inizializzaMappa(int indice) {
    mappaAttiva = indice;
    DatiMappa& dm = catalogo_mappe[indice];

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {

            collisionMap[i][j] = (dm.tilemap[i][j] == 0);
            mappa[i][j] = (dm.tilemap[i][j] == 1) ? MURO : PAVIMENTO;

            // oggetti
            if (dm.oggettiLayer[i][j] == 1) mappa[i][j] = OBJ_MONETA;
            if (dm.oggettiLayer[i][j] == 2) mappa[i][j] = OBJ_ARMA;
        }
    }

    // porte
    for (int u = 0; u < dm.numUscite; u++) {
        Uscita& usc = dm.uscite[u];
        switch (usc.lato) {
            case 0: mappa[0]           [usc.pos] = PORTA; break;
            case 1: mappa[MAP_ROWS - 1][usc.pos] = PORTA; break;
            case 2: mappa[usc.pos]     [0]        = PORTA; break;
            case 3: mappa[usc.pos]     [MAP_COLS-1] = PORTA; break;
        }
    }

    // NPC
    for (int n = 0; n < dm.numNpc; n++) {
        NPC& npc = dm.npcs[n];
        mappa[npc.x][npc.y] = OBJ_NPC;
    }

    // Nemici
    for (int ne = 0; ne < dm.numNemici; ne++) {
        NemicoMappa& nemico = dm.nemici[ne];
        if (nemico.vivo)
            mappa[nemico.x][nemico.y] = NEMICO;
    }
}

// ─────────────────────────────────────────
//  STAMPA MAPPA
// ─────────────────────────────────────────

void stampaMappa(const Entity& Player) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (i == Player.player_loc_x && j == Player.player_loc_y)
                cout << SPRITE_PL;
            else
                cout << mappa[i][j];
        }
        cout << "\n";
    }
}

// ─────────────────────────────────────────
//  INTERAGISCI CON NPC
// ─────────────────────────────────────────

void interagisciNPC(Entity& Player) {
    DatiMappa& dm = catalogo_mappe[mappaAttiva];
    int x = Player.player_loc_x;
    int y = Player.player_loc_y;

    for (int n = 0; n < dm.numNpc; n++) {
        NPC& npc = dm.npcs[n];
        if (npc.x == x && npc.y == y) {
            if (npc.tipo == 1) {
                // MENÙ FABBRO
                bool inMenu = true;
                while (inMenu) {
                    system("CLS");
                    cout << p.bold << p.gold << "=== NEGOZIO DEL " << npc.nome << " ===" << p.reset << "\n\n";

                    cout << "Scegli un'arma da acquistare:\n\n";
                    for (int a = 0; a < 3; a++) {
                        cout << (a + 1) << ". " << catalogo[a].nome
                             << " (d" << catalogo[a].dado << ") - 50 Monete\n";
                    }
                    cout << "4. Esci dal negozio\n\n";
                    cout << "Scelta: ";

                    char scelta = _getch();
                    system("CLS");

                    switch (scelta) {
                        case '1':
                        case '2':
                        case '3': {
                            int idx = scelta - '1';
                            cout << "\n" << p.green << "✓ Hai acquistato: "
                                 << catalogo[idx].nome << "!" << p.reset << "\n";
                            cout << "Premi un tasto per tornare...\n";
                            _getch();
                            break;
                        }
                        case '4':
                            inMenu = false;
                            cout << "\n" << p.cyan << "Arrivederci, avventuriero!" << p.reset << "\n";
                            cout << "Premi un tasto...\n";
                            _getch();
                            break;
                        default:
                            cout << "\n" << p.red << "Scelta non valida!" << p.reset << "\n";
                            cout << "Premi un tasto...\n";
                            _getch();
                            break;
                    }
                }
            }
            return;
        }
    }
}

// ─────────────────────────────────────────
//  CONTROLLA USCITE
// ─────────────────────────────────────────

bool controllaUscite(Entity& Player) {
    DatiMappa& dm = catalogo_mappe[mappaAttiva];

    for (int u = 0; u < dm.numUscite; u++) {
        Uscita& usc = dm.uscite[u];
        bool suPorta = false;

        switch (usc.lato) {
            case 0: suPorta = (Player.player_loc_x == 0            && Player.player_loc_y == usc.pos); break;
            case 1: suPorta = (Player.player_loc_x == MAP_ROWS - 1 && Player.player_loc_y == usc.pos); break;
            case 2: suPorta = (Player.player_loc_y == 0            && Player.player_loc_x == usc.pos); break;
            case 3: suPorta = (Player.player_loc_y == MAP_COLS - 1 && Player.player_loc_x == usc.pos); break;
        }

        if (suPorta) {
            inizializzaMappa(usc.mappaDestinazione);

            switch (usc.lato) {
                case 0: Player.player_loc_x = MAP_ROWS - 2; Player.player_loc_y = usc.pos; break;
                case 1: Player.player_loc_x = 1;            Player.player_loc_y = usc.pos; break;
                case 2: Player.player_loc_y = MAP_COLS - 2; Player.player_loc_x = usc.pos; break;
                case 3: Player.player_loc_y = 1;            Player.player_loc_x = usc.pos; break;
            }
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────
//  CONTROLLA NEMICI
//  Se il giocatore tocca un nemico,
//  avvia il combattimento e rimuove il nemico
// ─────────────────────────────────────────

bool controllaNemici(Entity& Player) {
    DatiMappa& dm = catalogo_mappe[mappaAttiva];
    int x = Player.player_loc_x;
    int y = Player.player_loc_y;

    for (int ne = 0; ne < dm.numNemici; ne++) {
        NemicoMappa& nemicoMappa = dm.nemici[ne];

        if (nemicoMappa.vivo && nemicoMappa.x == x && nemicoMappa.y == y) {
            // Trovato un nemico!
            Entity nemico = nemiciCatalogo[nemicoMappa.idCatalogo];

            system("CLS");
            cout << "\n" << p.red << p.bold << "⚔ TI ATTACCA UN " << nemico.name << "! ⚔" << p.reset << "\n\n";
            cout << "Premi un tasto per iniziare il combattimento...\n";
            _getch();

            // Avvia combattimento
            combatManager(Player, nemico);

            // Dopo il combattimento, rimuovi il nemico
            if (!nemico.isVivo()) {
                nemicoMappa.vivo = false;
                mappa[x][y] = PAVIMENTO;
                cout << "\n" << p.green << "Il nemico è stato sconfitto!" << p.reset << "\n";
                cout << "Premi un tasto per continuare...\n";
                _getch();
            } else {
                // Giocatore ha perso
                cout << "\n" << p.red << "Sei stato sconfitto..." << p.reset << "\n";
                cout << "GAME OVER\n";
                _getch();
                exit(0);
            }
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────
//  MOVIMENTO
// ─────────────────────────────────────────

void muoviPlayer(Entity& Player, char input) {
    int nx = Player.player_loc_x;
    int ny = Player.player_loc_y;

    if      (input == 'w') nx--;
    else if (input == 's') nx++;
    else if (input == 'a') ny--;
    else if (input == 'd') ny++;
    else return;

    if (nx < 0 || nx >= MAP_ROWS || ny < 0 || ny >= MAP_COLS) return;

    if (!collisionMap[nx][ny]) {
        DatiMappa& dm = catalogo_mappe[mappaAttiva];
        bool ePorta = false;
        for (int u = 0; u < dm.numUscite; u++) {
            Uscita& usc = dm.uscite[u];
            if ((usc.lato == 0 && nx == 0            && ny == usc.pos) ||
                (usc.lato == 1 && nx == MAP_ROWS - 1 && ny == usc.pos) ||
                (usc.lato == 2 && ny == 0            && nx == usc.pos) ||
                (usc.lato == 3 && ny == MAP_COLS - 1 && nx == usc.pos))
                ePorta = true;
        }
        if (!ePorta) return;
    }

    Player.player_loc_x = nx;
    Player.player_loc_y = ny;

    controllaUscite(Player);
    // Controlla nemici DOPO aver mosso il giocatore
    controllaNemici(Player);
}

// ─────────────────────────────────────────
//  GAME LOOP MAPPA
// ─────────────────────────────────────────

void gameLoop(Entity& Player) {
    inizializzaMappa(0);
    string messaggio = "";

    while (true) {
        system("CLS");
        stampaMappa(Player);

        cout << "\n[W/A/S/D] Muoviti   [E] Raccogli/Interagisci   [Q] Esci\n";
        cout << "Mappa: " << mappaAttiva << "  Pos: (" << Player.player_loc_x << ", " << Player.player_loc_y << ")\n";
        if (!messaggio.empty()) { cout << messaggio << "\n"; messaggio = ""; }

        char input = _getch();
        if (input == 'q' || input == 'Q') break;

        if (input == 'e' || input == 'E') {
            int x = Player.player_loc_x;
            int y = Player.player_loc_y;
            DatiMappa& dm = catalogo_mappe[mappaAttiva];

            // Controlla se c'è un NPC
            bool trovatoNpc = false;
            for (int n = 0; n < dm.numNpc; n++) {
                if (dm.npcs[n].x == x && dm.npcs[n].y == y) {
                    trovatoNpc = true;
                    interagisciNPC(Player);
                    break;
                }
            }

            // Se non c'è NPC, controlla oggetti
            if (!trovatoNpc) {
                switch (dm.oggettiLayer[x][y]) {
                    case 1:
                        messaggio = "\u2609 Hai raccolto una Moneta!";
                        Player.inv.monete += 10;
                        dm.oggettiLayer[x][y] = 0;
                        mappa[x][y] = PAVIMENTO;
                        break;
                    case 2:
                        messaggio = "\u2694 Hai raccolto un'Arma!";
                        dm.oggettiLayer[x][y] = 0;
                        mappa[x][y] = PAVIMENTO;
                        break;
                    default:
                        messaggio = "Nessun oggetto o NPC qui.";
                        break;
                }
            }
        } else {
            muoviPlayer(Player, input);
        }
    }
}