#pragma once
#include <string>
using namespace std;

// ─────────────────────────────────────────
//  STRUTTURE DATI
// ─────────────────────────────────────────

struct Arma {
    int    ID;
    string nome;
    int    dado;
};

struct Spell {
    string name;
    int    ID;     // 1-20 danno | 21-31 cura | 32+ buff
    int    danno;
    int    cura;
};

struct Inventario {
    int monete;
    int Frammenti_Ferro;
};

// ─────────────────────────────────────────
//  CATALOGHI
//  inline: evita definizione multipla
// ─────────────────────────────────────────

inline char cube = 219;

inline Arma catalogo[3] = {
    {1, "Gladio", 6},
    {2, "Spatha", 8},
    {3, "Ascia",  8},
};

inline Spell spellBook[3] = {
    {"Palla di Fuoco", 1,  15, 0},
    {"Fulmine",        2,  12, 0},
    {"Cura Rapida",   21,   0, 20},
};

inline int getDadoArma(int id) {
    for (int i = 0; i < 3; i++)
        if (catalogo[i].ID == id)
            return catalogo[i].dado;
    return 4;
}
