#pragma once
#include "palette.h"
#include "entity.h"
#include <iostream>
#include <conio.h>
using namespace std;

// ─────────────────────────────────────────

// ─────────────────────────────────────────

const int MAP_ROWS  = 10;
const int MAP_COLS  = 10;
const int NUM_MAPPE = 4;   // numero di mappe totali

// ── sprite grafici ────────────────────────
const string MURO      = "\033[37m\u2588\u2588\033[0m"; // █ grigio
const string PORTA     = "\033[35m\u2588\u2588\033[0m"; // █ viola  (uscita)
const string PAVIMENTO = "\033[33m\u2588\u2588\033[0m"; // █ giallo
const string SPRITE_PL = "\033[32m\u2588\u2588\033[0m"; // █ verde

// ── oggetti ───────────────────────────────
const string OBJ_MONETA = "\033[33m\u2609\u2609\033[0m"; // ☉ giallo
const string OBJ_ARMA   = "\033[36m\u2694\u2694\033[0m"; // ⚔ ciano

// ─────────────────────────────────────────
//  STRUCT USCITA
//  Descrive un'uscita su un bordo della mappa
//  lato: 0=su 1=giù 2=sinistra 3=destra
//  pos:  riga o colonna del blocco porta
//  mappaDestinazione: indice mappa collegata
// ─────────────────────────────────────────

struct Uscita {
    int lato;
    int pos;
    int mappaDestinazione;
};

// ─────────────────────────────────────────
//  DATI MAPPE
//  Ogni mappa ha: tilemap, oggettiLayer,
//  lista uscite
// ─────────────────────────────────────────

struct DatiMappa {
    int     tilemap     [MAP_ROWS][MAP_COLS];
    int     oggettiLayer[MAP_ROWS][MAP_COLS];
    Uscita  uscite[4];   // max 4 uscite (una per lato)
    int     numUscite;
};

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
        // uscite: lato=3 (destra), pos=5 (riga 5), destinazione=mappa 1
        {{3, 5, 1}},
        1  // numUscite
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
        // uscite: lato=2 (sinistra), pos=5 (riga 5), destinazione=mappa 0
        {{2, 5, 0},{1,2,2}},
        2  // numUscite
    },

    // ── MAPPA 2 ──────────────────────────

    { // MAPPA 2: Stanza del Tesoro (Indice 2)
        { // tilemap (disegno dei muri)
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // Il centro ha un muro a forma di U
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        },
        { // oggettiLayer (1 = moneta, 2 = arma)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0, 0, 0, 0}, // Un'arma speciale al centro
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        {{0, 2, 1}}, // uscita: lato=1 (giù), pos=2 (colonna 2), destinazione=mappa 0
        1
    },
    // <--- NON DIMENTICARE QUESTA VIRGOLA SE C'E' UN'ALTRA MAPPA DOPO!
};

// ─────────────────────────────────────────
//  STATO MAPPA ATTIVA  (runtime)
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
void gameLoop(Entity& Player);