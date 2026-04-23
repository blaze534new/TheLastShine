#pragma once
#include "palette.h"
#include <iostream>
#include <conio.h>
using namespace std;

// ─────────────────────────────────────────
//  COSTANTI
// ─────────────────────────────────────────

const int MAP_ROWS = 10;
const int MAP_COLS = 10;
const char TILE    = (char)219; // █

// ─────────────────────────────────────────
//  STRUCT PLAYER (posizione)
// ─────────────────────────────────────────

struct Player {
    int x, y; // riga, colonna
};

// ─────────────────────────────────────────
//  TILEMAP  — cosa disegnare su ogni cella
//  0 = pavimento  1 = muro
// ─────────────────────────────────────────

inline int tilemap[MAP_ROWS][MAP_COLS] = {
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
};

// ─────────────────────────────────────────
//  COLLISION MAP  — true = calpestabile
//  generata automaticamente dalla tilemap
//  (deve sempre essere in sync con tilemap)
// ─────────────────────────────────────────

inline bool collisionMap[MAP_ROWS][MAP_COLS];

// ─────────────────────────────────────────
//  DICHIARAZIONI
// ─────────────────────────────────────────

void inizializzaCollisionMap();
void stampaMappa(const Player& player);
void gameLoop();