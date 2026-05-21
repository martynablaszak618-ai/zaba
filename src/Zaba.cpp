// Dolaczamy deklaracje klasy Zaba.
#include "Zaba.h"

// Dolaczamy std::clamp do pilnowania granic planszy.
#include <algorithm>

// Ustawia pozycje startowa zaby.
void Zaba::ustawPozycjeStartowa(int xStart, int yStart) {
    // Zapisujemy przekazane wspolrzedne.
    x = xStart;
    y = yStart;
}

// Przesuwa abe o podany krok w wybranym kierunku (dx, dy).
void Zaba::ruch(int dx, int dy, int krok) {
    // Zmieniamy X i Y zgodnie z kierunkiem i wielkoscia kroku.
    x += dx * krok;
    y += dy * krok;
}

// Pilnuje, aby zaba nie wyszla poza obszar planszy.
void Zaba::ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy) {
    // Ograniczamy X do przedzialu od 0 do ostatniej kolumny.
    x = std::clamp(x, 0, szerokoscPlanszy - 1);
    // Ograniczamy Y do przedzialu od 0 do ostatniego wiersza.
    y = std::clamp(y, 0, wysokoscPlanszy - 1);
}

// Zwraca aktualna wspolrzedna X zaby.
int Zaba::pobierzX() const { return x; }

// Zwraca aktualna wspolrzedna Y zaby.
int Zaba::pobierzY() const { return y; }
