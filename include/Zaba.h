// Ta dyrektywa pilnuje, aby plik byl dolaczony tylko raz.
#pragma once

// Potrzebujemy klasy Pozycja do przechowywania miejsca zaby.
#include "Pozycja.h"

// Ta klasa reprezentuje gracza (czyli abe) i jej ruch.
class Zaba {
public:
    // Ustawia pozycje poczatkowa zaby na planszy.
    void ustawPozycjeStartowa(int xStart, int yStart);

    // Ruch o "krok" w gore (zwiekszenie wspolrzednej Y).
    void ruchWGore(int krok);
    // Ruch o "krok" w dol (zmniejszenie wspolrzednej Y).
    void ruchWDol(int krok);
    // Ruch o "krok" w lewo (zmniejszenie wspolrzednej X).
    void ruchWLewo(int krok);
    // Ruch o "krok" w prawo (zwiekszenie wspolrzednej X).
    void ruchWPrawo(int krok);

    // Koryguje pozycje, aby zaba nie wyszla poza plansze.
    void ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy);

    // Zwraca aktualna pozycje zaby.
    Pozycja pobierzPozycje() const;

private:
    // Pole przechowujace aktualna pozycje gracza.
    Pozycja pozycja;
};
