// Ta dyrektywa pilnuje, aby plik byl dolaczony tylko raz.
#pragma once

// Ta klasa reprezentuje gracza (czyli abe) i jej ruch.
class Zaba {
public:
    // Ustawia pozycje poczatkowa zaby na planszy.
    void ustawPozycjeStartowa(int xStart, int yStart);

    // Przesuwa abe o podany krok: dx w lewo/prawo, dy w gore/dol (np. dy=1 to gora).
    void ruch(int dx, int dy, int krok = 1);

    // Koryguje pozycje, aby zaba nie wyszla poza plansze.
    void ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy);

    // Zwraca aktualna wspolrzedna X zaby.
    int pobierzX() const;
    // Zwraca aktualna wspolrzedna Y zaby.
    int pobierzY() const;

private:
    // Pole przechowuje wspolrzedna pozioma.
    int x = 0;
    // Pole przechowuje wspolrzedna pionowa.
    int y = 0;
};
