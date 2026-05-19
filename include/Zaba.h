#pragma once

#include "Pozycja.h"

// Klasa gracza: przechowuje pozycje zaby i logike ruchu po planszy.
class Zaba {
public:
    void ustawPozycjeStartowa(int xStart, int yStart);

    // Kazda z metod odpowiada jednej komendzie sterowania.
    void ruchWGore(int krok);
    void ruchWDol(int krok);
    void ruchWLewo(int krok);
    void ruchWPrawo(int krok);

    // Blokada wychodzenia poza plansze (sytuacja wyjatkowa z wymagan).
    void ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy);

    Pozycja pobierzPozycje() const;

private:
    Pozycja pozycja;
};
