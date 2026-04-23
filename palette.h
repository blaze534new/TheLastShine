#pragma once
#include <string>
using namespace std;

// ─────────────────────────────────────────
//  PALETTE  — colori e stili ANSI
// ─────────────────────────────────────────

struct Palette {
    string reset     = "\033[0m";

    // Stili
    string bold      = "\033[1m";
    string underline = "\033[4m";
    string reverse   = "\033[7m";

    // Colori testo
    string black  = "\033[30m";
    string red    = "\033[31m";
    string green  = "\033[32m";
    string giallo = "\033[33m";
    string blu    = "\033[34m";
    string purple = "\033[35m";
    string cyan   = "\033[36m";
    string gold   = "\033[38;5;214m";
    string pink   = "\033[38;5;198m";

    // Sfondi
    string bgRed  = "\033[41m";
    string bgBlue = "\033[44m";
};

inline Palette p; // inline: unica definizione anche se incluso da più file
