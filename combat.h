#pragma once
#include "entity.h"

// ─────────────────────────────────────────
//  DICHIARAZIONI  FUNZIONI DI COMBATTIMENTO
// ─────────────────────────────────────────

void stampaStato    (const Entity& giocatore, const Entity& nemico);
int  attaccaFisico  (Entity& attaccante, Entity& bersaglio);
void usaIncantesimo (Entity& giocatore,  Entity& nemico);
int  difenditi      (Entity& giocatore);
void turnoNemico    (Entity& nemico, Entity& giocatore, int bonusCAGiocatore);
void combatManager  (Entity& giocatore, Entity& nemico);