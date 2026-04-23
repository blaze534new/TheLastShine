#pragma once
#include <string>
#include <cstdlib>
#include "catalogo.h"
using namespace std;

// ─────────────────────────────────────────
//  HELPER: dado
// ─────────────────────────────────────────

inline int tiraDado(int facce) {
    return (rand() % facce) + 1;
}

// ─────────────────────────────────────────
//  CLASSE ENTITY
// ─────────────────────────────────────────

class Entity {
public:
    string name;
    string classe;       // "Guerriero", "Barbaro", "Mago"
    int    hp, hpMax;
    int    FOR, DES;
    int    idArma;
    int    liv;
    int    numSpell;
    bool   haUsatoCura;

    // ── posizione sulla mappa ─────────────
    int    player_loc_x;
    int    player_loc_y;

    Entity(string n, string cl, int h, int f, int d, int arma, int l, int sp,
           int startX = 1, int startY = 1)
        : name(n), classe(cl), hp(h), hpMax(h),
          FOR(f), DES(d), idArma(arma), liv(l),
          numSpell(sp), haUsatoCura(false),
          player_loc_x(startX), player_loc_y(startY) {}

    int  mod(int stat)         { return (stat - 10) / 2; }
    int  CA()                  { return 10 + mod(DES); }
    int  bonusAtk()            { return mod(FOR) + (liv / 4 + 2); }
    int  dannoArma()           { return tiraDado(getDadoArma(idArma)) + mod(FOR); }
    bool isVivo()              { return hp > 0; }
    bool sottoTrentoPercento() { return hp < (hpMax * 30) / 100; }
};