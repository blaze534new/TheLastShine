#include "mappa.h"
using namespace std;

// ─────────────────────────────────────────
//  GENERA COLLISION MAP DALLA TILEMAP
//  true  = pavimento (calpestabile)
//  false = muro      (bloccato)
// ─────────────────────────────────────────

void inizializzaCollisionMap() {
    for (int i = 0; i < MAP_ROWS; i++)
        for (int j = 0; j < MAP_COLS; j++)
            collisionMap[i][j] = (tilemap[i][j] == 0);
}

// ─────────────────────────────────────────
//  STAMPA MAPPA
// ─────────────────────────────────────────

void stampaMappa(const Player& player) {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {

            // Giocatore
            if (i == player.x && j == player.y) {
                cout << p.green << TILE << p.reset;
                continue;
            }

            // Tile in base alla tilemap
            if (tilemap[i][j] == 1)
                cout << p.purple << TILE << p.reset; // muro → grigio (purple = viola, usiamo bold white)
            else
                cout << p.giallo << TILE << p.reset; // pavimento → giallo
        }
        cout << "\n";
    }
}

// ─────────────────────────────────────────
//  MOVIMENTO CON CONTROLLO COLLISIONI
// ─────────────────────────────────────────

void muoviPlayer(Player& player, char input) {
    int nx = player.x;
    int ny = player.y;

    if      (input == 'w') nx--;
    else if (input == 's') nx++;
    else if (input == 'a') ny--;
    else if (input == 'd') ny++;
    else return; // tasto non gestito, esci subito

    // Controllo bordi
    if (nx < 0 || nx >= MAP_ROWS || ny < 0 || ny >= MAP_COLS) return;

    // Controllo collisione: si muove solo se la cella è calpestabile
    if (collisionMap[nx][ny])  {
        player.x = nx;
        player.y = ny;
    }
}

// ─────────────────────────────────────────
//  GAME LOOP MAPPA
// ─────────────────────────────────────────

void gameLoop() {
    inizializzaCollisionMap();

    // Posizione iniziale giocatore (prima cella libera)
    Player player = {1, 1};

    while (true) {
        system("CLS");
        stampaMappa(player);

        cout << "\n[W/A/S/D] Muoviti   [Q] Esci\n";

        char input = _getch();
        if (input == 'q' || input == 'Q') break;

        muoviPlayer(player, input);
    }
}