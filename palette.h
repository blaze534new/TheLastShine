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

    // --- TONI DEL ROSSO E ARANCIO ---
    string rossoSangue  = "\033[38;5;124m";
    string corallo      = "\033[38;5;203m";
    string arancioScuro = "\033[38;5;166m";
    string pesca        = "\033[38;5;216m";
    string mattone      = "\033[38;5;130m";

    // --- TONI DEL VERDE ---
    string smeraldo     = "\033[38;5;47m";
    string oliva        = "\033[38;5;100m";
    string lime         = "\033[38;5;191m";
    string menta        = "\033[38;5;121m";
    string verdeAcido   = "\033[38;5;112m";

    // --- TONI DEL BLU E AZZURRO ---
    string celeste      = "\033[38;5;153m";
    string bluReale     = "\033[38;5;27m";
    string turchese     = "\033[38;5;45m";
    string indaco       = "\033[38;5;54m";
    string bluAcciaio   = "\033[38;5;67m";

    // --- TONI DEL VIOLA E ROSA ---
    string lilla        = "\033[38;5;183m";
    string prugna       = "\033[38;5;96m";
    string fucsia       = "\033[38;5;201m";
    string orchidea     = "\033[38;5;170m";
    string violaNotte   = "\033[38;5;17m";

    // --- TONI TERRA E METALLO ---
    string cioccolato   = "\033[38;5;52m";
    string bronzo       = "\033[38;5;136m";
    string argento      = "\033[38;5;249m";
    string platino      = "\033[38;5;253m";
    string rame         = "\033[38;5;167m";

    // --- GRIGI E SFUMATURE OSCURE ---
    string fumo         = "\033[38;5;240m";
    string grafite      = "\033[38;5;236m";
    string nebbia       = "\033[38;5;251m";
    string asfalto      = "\033[38;5;234m";
    string osso         = "\033[38;5;230m";

    // ─────────────────────────────────────────
    //  NUOVI COLORI ESTESI (GDR Style)
    // ─────────────────────────────────────────
    // Ambientali
    string marrone      = "\033[38;5;94m";  // Legno / Terra
    string verdeBosco   = "\033[38;5;22m";  // Erba / Foreste
    string grigioPietra = "\033[38;5;244m"; // Muri antichi
    string sabbia       = "\033[38;5;222m"; // Deserto

    // Magia e Effetti
    string fuoco        = "\033[38;5;202m"; // Arancione vivo
    string ghiaccio     = "\033[38;5;123m"; // Celeste magico
    string fulmine      = "\033[38;5;226m"; // Giallo brillante
    string veleno       = "\033[38;5;46m";  // Verde acido
    string ombra        = "\033[38;5;55m";  // Viola oscuro
    string sacro        = "\033[38;5;231m"; // Bianco luce

    // Interfaccia e Loot
    string vitaBassa    = "\033[38;5;196m"; // Rosso intenso
    string monetaRara   = "\033[38;5;220m"; // Oro brillante
    string leggendario  = "\033[38;5;201m"; // Magenta/Viola acceso
    string grigioScuro  = "\033[38;5;236m"; // Testo meno importante

    // ─────────────────────────────────────────
    //  SFONDI (Background)
    // ─────────────────────────────────────────
    string bgRed    = "\033[41m";       // Il tuo bgRed attuale
    string bgBlue   = "\033[44m";       // Il tuo bgBlue attuale
    string bgLava   = "\033[48;5;160m"; // Sfondo rosso fuoco
    string bgForesta = "\033[48;5;22m";  // Sfondo verde scuro
    string bgAbisso = "\033[48;5;232m"; // Sfondo nero totale
    string bgOro    = "\033[48;5;214m"; // Sfondo color oro

};

inline Palette p; // inline: unica definizione anche se incluso da più file
