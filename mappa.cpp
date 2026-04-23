#include "mappa.h"
using namespace std;

// ─────────────────────────────────────────
//  INIZIALIZZA MAPPA
//  Carica tilemap e oggettiLayer della
//  mappa con l'indice dato
// ─────────────────────────────────────────

void inizializzaMappa(int indice) {
    mappaAttiva = indice;
    DatiMappa& dm = catalogo_mappe[indice];

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {

            // collision map
            collisionMap[i][j] = (dm.tilemap[i][j] == 0);

            // tile base
            mappa[i][j] = (dm.tilemap[i][j] == 1) ? MURO : PAVIMENTO;

            // oggetti
            if (dm.oggettiLayer[i][j] == 1) mappa[i][j] = OBJ_MONETA;
            if (dm.oggettiLayer[i][j] == 2) mappa[i][j] = OBJ_ARMA;
        }
    }

    // disegna le porte sul bordo (colore viola)
    for (int u = 0; u < dm.numUscite; u++) {
        Uscita& usc = dm.uscite[u];
        switch (usc.lato) {
            case 0: mappa[0]           [usc.pos] = PORTA; break; // su
            case 1: mappa[MAP_ROWS - 1][usc.pos] = PORTA; break; // giù
            case 2: mappa[usc.pos]     [0]        = PORTA; break; // sinistra
            case 3: mappa[usc.pos]     [MAP_COLS-1] = PORTA; break; // destra
        }
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
//  CONTROLLA USCITE
//  Se il giocatore è su una porta cambia
//  mappa e riposiziona il giocatore
//  sul lato opposto
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

            // entra dal lato opposto
            switch (usc.lato) {
                case 0: Player.player_loc_x = MAP_ROWS - 2; Player.player_loc_y = usc.pos; break; // veniva da su  → entra in basso
                case 1: Player.player_loc_x = 1;            Player.player_loc_y = usc.pos; break; // veniva da giù → entra in alto
                case 2: Player.player_loc_y = MAP_COLS - 2; Player.player_loc_x = usc.pos; break; // veniva da sx  → entra a destra
                case 3: Player.player_loc_y = 1;            Player.player_loc_x = usc.pos; break; // veniva da dx  → entra a sinistra
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

    // bordi: blocca solo se NON è una porta
    if (nx < 0 || nx >= MAP_ROWS || ny < 0 || ny >= MAP_COLS) return;

    // collisione muri
    if (!collisionMap[nx][ny]) {
        // controlla se è una porta prima di bloccare
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
        if (!ePorta) return; // muro normale: blocca
    }

    Player.player_loc_x = nx;
    Player.player_loc_y = ny;

    // controlla se il giocatore è entrato in una porta
    controllaUscite(Player);
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

        cout << "\n[W/A/S/D] Muoviti   [E] Raccogli   [Q] Esci\n";
        cout << "Mappa: " << mappaAttiva << "\n";
        if (!messaggio.empty()) { cout << messaggio << "\n"; messaggio = ""; }

        char input = _getch();
        if (input == 'q' || input == 'Q') break;

        if (input == 'e' || input == 'E') {
            int x = Player.player_loc_x;
            int y = Player.player_loc_y;
            DatiMappa& dm = catalogo_mappe[mappaAttiva];
            switch (dm.oggettiLayer[x][y]) {
                case 1:
                    messaggio = "\u2609 Hai raccolto una Moneta!";
                    dm.oggettiLayer[x][y] = 0;
                    mappa[x][y] = PAVIMENTO;
                    break;
                case 2:
                    messaggio = "\u2694 Hai raccolto un'Arma!";
                    dm.oggettiLayer[x][y] = 0;
                    mappa[x][y] = PAVIMENTO;
                    break;
                default:
                    messaggio = "Nessun oggetto qui.";
                    break;
            }
        } else {
            muoviPlayer(Player, input);
        }
    }
}