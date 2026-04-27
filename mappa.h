#pragma once
#include "palette.h"
#include "entity.h"
#include <iostream>
#include <conio.h>
using namespace std;

// ─────────────────────────────────────────
//  COSTANTI
// ─────────────────────────────────────────

const int MAP_ROWS  = 10;
const int MAP_COLS  = 10;
const int NUM_MAPPE = 4;
const int MAX_NPC   = 10;
const int MAX_NEMICI_MAPPA = 10;

// ── sprite grafici ────────────────────────
const string MURO      = "\033[37m\u2588\u2588\033[0m"; // █ grigio
const string PORTA     = "\033[35m\u2588\u2588\033[0m"; // █ viola
const string PAVIMENTO = "\033[33m\u2588\u2588\033[0m"; // █ giallo
const string SPRITE_PL = "\033[32m\u2588\u2588\033[0m"; // █ verde
const string NEMICO    = "\033[31m\u2588\u2588\033[0m"; // █ rosso

// ── oggetti ───────────────────────────────
const string OBJ_MONETA = "\033[33m\u2609\u2609\033[0m"; // ☉ giallo
const string OBJ_ARMA   = "\033[36m\u2694\u2694\033[0m"; // ⚔ ciano
const string OBJ_NPC    = "\033[36m\u263C\u263C\033[0m"; // ☼ ciano (NPC)

// ─────────────────────────────────────────
//  STRUCT NPC
// ─────────────────────────────────────────

struct NPC {
    int    id;
    string nome;
    int    x, y;
    int    tipo;    // 1 = fabbro
};

// ─────────────────────────────────────────
//  STRUCT USCITA
// ─────────────────────────────────────────

struct Uscita {
    int lato;
    int pos;
    int mappaDestinazione;
};

// ─────────────────────────────────────────
//  STRUCT NEMICO MAPPA
//  Rappresenta un nemico specifico
//  posizionato sulla mappa
// ─────────────────────────────────────────

struct NemicoMappa {
    int     idCatalogo;    // indice in nemiciCatalogo[]
    int     x, y;          // posizione
    bool    vivo = true;   // è ancora vivo?
};

// ─────────────────────────────────────────
//  STRUCT DATI MAPPA
// ─────────────────────────────────────────

struct DatiMappa {
    int         tilemap     [MAP_ROWS][MAP_COLS];
    int         oggettiLayer[MAP_ROWS][MAP_COLS];
    Uscita      uscite[4];
    int         numUscite;
    NPC         npcs[MAX_NPC];
    int         numNpc;
    NemicoMappa nemici[MAX_NEMICI_MAPPA];
    int         numNemici;
};

// ─────────────────────────────────────────
//  CATALOGO NEMICI
// ─────────────────────────────────────────

// Dichiarazione esterna (implementata in mappa.cpp)
extern Entity nemiciCatalogo[];
extern int NUM_NEMICI_CATALOGO;

// ─────────────────────────────────────────
//  CATALOGO MAPPE
// ─────────────────────────────────────────

inline DatiMappa catalogo_mappe[NUM_MAPPE] = {

    // ── MAPPA 0 ──────────────────────────
    {
        {   // tilemap
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        },
        {   // oggettiLayer
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        {{3, 5, 1}},
        1,
        {},
        0,
        {   // nemiciMappa: {idCatalogo, x, y, vivo}
            {0, 3, 3},  // Goblin in (3,3)
            {1, 7, 6},  // Orc in (7,6)
        },
        2   // numNemici
    },

    // ── MAPPA 1 ──────────────────────────
    {
        {   // tilemap
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        },
        {   // oggettiLayer
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
        {{2, 5, 0}, {1, 2, 2}},
        2,
        {   // NPC
            {1, "Fabbro", 5, 5, 1}
        },
        1,
        {   // nemiciMappa
            {2, 2, 3},  // Stregone in (2,3)
            {1, 8, 2},  // Orc in (8,2)
        },
        2
    },

    // ── MAPPA 2 ──────────────────────────
    {
        {   // tilemap
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        },
        {   // oggettiLayer
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {{0, 2, 1}},
        1,
        {},
        0,
        {},
        0   // nessun nemico
    },

    // ── MAPPA 3 ──────────────────────────
    {
        {   // tilemap
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        },
        {   // oggettiLayer
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {},
        0,
        {},
        0,
        {},
        0
    },
};

// ─────────────────────────────────────────
//  STATO MAPPA ATTIVA (runtime)
// ─────────────────────────────────────────

inline int     mappaAttiva = 0;
inline bool    collisionMap[MAP_ROWS][MAP_COLS];
inline string  mappa[MAP_ROWS][MAP_COLS];

// ─────────────────────────────────────────
//  DICHIARAZIONI
// ─────────────────────────────────────────

void inizializzaMappa(int indice);
void stampaMappa(const Entity& Player);
void muoviPlayer(Entity& Player, char input);
void interagisciNPC(Entity& Player);
void gameLoop(Entity& Player);