#include "combat.h"
#include <iostream>
#include "menu.h"
using namespace std;

// ─────────────────────────────────────────
//  STAMPA STATO
// ─────────────────────────────────────────

void stampaStato(const Entity& g, const Entity& n) {
    cout << "\n========================================\n";
    cout << "[" << g.name << "]  HP: " << g.hp << "/" << g.hpMax
         << "   CA: " << (10 + (g.DES - 10) / 2) << "\n";
    cout << "[" << n.name << "]  HP: " << n.hp << "/" << n.hpMax
         << "   CA: " << (10 + (n.DES - 10) / 2) << "\n";
    cout << "========================================\n";
}

// ─────────────────────────────────────────
//  ATTACCO FISICO
// ─────────────────────────────────────────

int attaccaFisico(Entity& attaccante, Entity& bersaglio) {
    int  tiro    = tiraDado(20);
    bool critico = (tiro == 20);
    int  totale  = tiro + attaccante.bonusAtk();

    cout << "\n" << attaccante.name << " attacca! [d20=" << tiro;
    if (critico) cout << " CRITICO!";
    cout << " | totale=" << totale << " vs CA=" << bersaglio.CA() << "]\n";

    if (critico || totale >= bersaglio.CA()) {
        int dado  = getDadoArma(attaccante.idArma);
        int danno = tiraDado(dado) + attaccante.mod(attaccante.FOR);
        if (critico) danno += tiraDado(dado);
        if (danno < 1) danno = 1;
        bersaglio.hp -= danno;
        cout << "Colpito! Danno: " << danno << "\n";
        return danno;
    }

    cout << "Mancato!\n";
    return 0;
}

// ─────────────────────────────────────────
//  USA INCANTESIMO (giocatore)
// ─────────────────────────────────────────

void usaIncantesimo(Entity& giocatore, Entity& nemico) {
    if (giocatore.numSpell <= 0) {
        cout << "Nessun incantesimo disponibile!\n";
        return;
    }

    cout << "\nScegli incantesimo:\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << spellBook[i].name;
        if (spellBook[i].ID <= 20) cout << " (Danno: " << spellBook[i].danno << ")";
        else                       cout << " (Cura: "  << spellBook[i].cura  << ")";
        cout << "\n";
    }

    int scelta;
    cin >> scelta;
    if (scelta < 1 || scelta > 3) { cout << "Scelta non valida.\n"; return; }

    Spell& s = spellBook[scelta - 1];
    giocatore.numSpell--;

    if (s.ID <= 20) {
        nemico.hp -= s.danno;
        cout << giocatore.name << " lancia " << s.name << "! Danno: " << s.danno << "\n";
    } else {
        giocatore.hp += s.cura;
        if (giocatore.hp > giocatore.hpMax) giocatore.hp = giocatore.hpMax;
        cout << giocatore.name << " lancia " << s.name << "! Curati: " << s.cura << "\n";
    }
}

// ─────────────────────────────────────────
//  DIFESA
// ─────────────────────────────────────────

int difenditi(Entity& giocatore) {
    cout << "\n" << giocatore.name << " si mette in guardia! (+3 CA questo turno)\n";
    return 3;
}

// ─────────────────────────────────────────
//  TURNO NEMICO (IA)
// ─────────────────────────────────────────

void turnoNemico(Entity& nemico, Entity& giocatore, int bonusCAGiocatore) {
    cout << "\n--- Turno di " << nemico.name << " ---\n";

    // Priorità 1: cura una volta sola sotto 30% HP
    if (nemico.sottoTrentoPercento() && !nemico.haUsatoCura) {
        for (int i = 0; i < 3; i++) {
            if (spellBook[i].ID >= 21 && nemico.numSpell > 0) {
                nemico.hp += spellBook[i].cura;
                if (nemico.hp > nemico.hpMax) nemico.hp = nemico.hpMax;
                nemico.numSpell--;
                nemico.haUsatoCura = true;
                cout << nemico.name << " lancia " << spellBook[i].name
                     << "! Si cura di " << spellBook[i].cura << " HP.\n";
                return;
            }
        }
    }

    // Priorità 2: Mago usa spell di danno
    if (nemico.classe == "Mago" && nemico.numSpell > 0) {
        for (int i = 0; i < 3; i++) {
            if (spellBook[i].ID <= 20) {
                giocatore.hp -= spellBook[i].danno;
                nemico.numSpell--;
                cout << nemico.name << " lancia " << spellBook[i].name
                     << "! Danno: " << spellBook[i].danno << "\n";
                return;
            }
        }
    }

    // Priorità 3: attacco fisico
    int tiro   = tiraDado(20);
    int totale = tiro + nemico.bonusAtk();
    int caEff  = giocatore.CA() + bonusCAGiocatore;

    cout << nemico.name << " attacca! [d20=" << tiro
         << " | totale=" << totale << " vs CA=" << caEff << "]\n";

    if (tiro == 20 || totale >= caEff) {
        int dado  = getDadoArma(nemico.idArma);
        int danno = tiraDado(dado) + nemico.mod(nemico.FOR);
        if (tiro == 20) danno += tiraDado(dado);
        if (danno < 1) danno = 1;
        giocatore.hp -= danno;
        cout << "Colpito! Danno: " << danno << "\n";
    } else {
        cout << "Mancato!\n";
    }
}

// ─────────────────────────────────────────
//  COMBAT MANAGER
// ─────────────────────────────────────────

void combatManager(Entity& giocatore, Entity& nemico) {
    cout << "\n*** INIZIA IL COMBATTIMENTO ***\n";
    cout << giocatore.name << " (" << giocatore.classe << ")"
         << " VS " << nemico.name << " (" << nemico.classe << ")\n";

    while (giocatore.isVivo() && nemico.isVivo()) {

        stampaStato(giocatore, nemico);

        cout << "\nAzione:\n";
        cout << "1. Attacca\n";
        if (giocatore.classe == "Mago")
            cout << "2. Usa Incantesimo (" << giocatore.numSpell << " rimasti)\n";
        else
            cout << "2. Usa Incantesimo [non disponibile per " << giocatore.classe << "]\n";
        cout << "3. Difenditi\n> ";

        int scelta;
        cin >> scelta;
        int bonusCA = 0;

        switch (scelta) {
            case 1: attaccaFisico(giocatore, nemico); break;
            case 2:
                if (giocatore.classe == "Mago") usaIncantesimo(giocatore, nemico);
                else cout << "I " << giocatore.classe << " non usano magie!\n";
                break;
            case 3: bonusCA = difenditi(giocatore); break;
            default: cout << "Scelta non valida!\n"; break;
        }

        if (!nemico.isVivo()) break;
        turnoNemico(nemico, giocatore, bonusCA);
    }

    cout << "\n========================================\n";
    if (giocatore.isVivo())
        cout << "*** " << giocatore.name << " ha vinto! ***\n";
    else
        cout << "*** " << nemico.name << " ha vinto. Hai perso! ***\n";
    cout << "========================================\n";
}

void combatManagerTutorial(Entity& giocatore, Entity& nemico) {
    cout << "\n*** INIZIA IL TUO PRIMO COMBATTIMENTO ***\n";
    cout << giocatore.name << " (" << giocatore.classe << ")"
         << " VS " << nemico.name << " (" << nemico.classe << ")\n";
    testo("Benvenuto nell'arena e nel tuo primo combattimento", 1);
    testo("Il combattimento è a turno avrai un turno per attaccare ma anche il nemico avrà un turno per attaccarti", 2);
    testo("Sfrutta una tua strategia per battere i nemici alternando difesa e attacco", 2);
    testo("Le azioni principali che puoi fare sono:", 1);
    testo("1) Attacco lancerai un D20(Dado a 20 facce) e il risultato del dado determinerà quanti danni farai  ", 1);
    testo("oltre ai danni dati dal risultato del dado puoi avere dei bonus attacco in base alla classe e/o ai bonus che sbloccherai nel gioco ", 1);
    testo("2) Usa incantesimo  ", 1);  // TODO: FINIRE IL TUTORIAL
    while (giocatore.isVivo() && nemico.isVivo()) {
        // Ciclo principale: stato -> turno giocatore -> turno nemico.
        stampaStato(giocatore, nemico);

        cout << "\nAzione:\n";
        cout << "1. Attacca\n";
        if (giocatore.classe == "Mago")
            cout << "2. Usa Incantesimo (" << giocatore.numSpell << " rimasti)\n";
        else
            cout << "2. Usa Incantesimo [non disponibile per " << giocatore.classe << "]\n";
        cout << "3. Difenditi\n> ";

        int scelta;
        cin >> scelta;
        int bonusCA = 0;

        switch (scelta) {
            case 1: attaccaFisico(giocatore, nemico); break;
            case 2:
                if (giocatore.classe == "Mago") usaIncantesimo(giocatore, nemico);
                else cout << "I " << giocatore.classe << " non usano magie!\n";
                break;
            case 3: bonusCA = difenditi(giocatore); break;
            default: cout << "Scelta non valida!\n"; break;
        }

        if (!nemico.isVivo()) break;
        turnoNemico(nemico, giocatore, bonusCA);
    }

    cout << "\n========================================\n";
    if (giocatore.isVivo())
        cout << "*** " << giocatore.name << " ha vinto! ***\n";
    else
        cout << "*** " << nemico.name << " ha vinto. Hai perso! ***\n";
    cout << "========================================\n";
}