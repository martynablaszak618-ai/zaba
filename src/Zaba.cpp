// Dolaczamy deklaracje klasy Zaba.
#include "Zaba.h"

// Dolaczamy std::clamp do pilnowania granic planszy.
#include <algorithm>

// Ustawia pozycje startowa zaby.
void Zaba::ustawPozycjeStartowa(int xStart, int yStart) {
    // Zapisujemy przekazane wspolrzedne do obiektu pozycji.
    pozycja.ustaw(xStart, yStart);
}

// Przesuwa abe o podany krok w gore.
void Zaba::ruchWGore(int krok) {
    // X zostaje ten sam, Y zwiekszamy o krok.
    pozycja.ustaw(pozycja.pobierzX(), pozycja.pobierzY() + krok);
}

// Przesuwa abe o podany krok w dol.
void Zaba::ruchWDol(int krok) {
    // X zostaje ten sam, Y zmniejszamy o krok.
    pozycja.ustaw(pozycja.pobierzX(), pozycja.pobierzY() - krok);
}

// Przesuwa abe o podany krok w lewo.
void Zaba::ruchWLewo(int krok) {
    // X zmniejszamy o krok, Y zostaje bez zmian.
    pozycja.ustaw(pozycja.pobierzX() - krok, pozycja.pobierzY());
}

// Przesuwa abe o podany krok w prawo.
void Zaba::ruchWPrawo(int krok) {
    // X zwiekszamy o krok, Y zostaje bez zmian.
    pozycja.ustaw(pozycja.pobierzX() + krok, pozycja.pobierzY());
}

// Pilnuje, aby zaba nie wyszla poza obszar planszy.
void Zaba::ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy) {
    // Ograniczamy X do przedzialu od 0 do ostatniej kolumny.
    const int x = std::clamp(pozycja.pobierzX(), 0, szerokoscPlanszy - 1);
    // Ograniczamy Y do przedzialu od 0 do ostatniego wiersza.
    const int y = std::clamp(pozycja.pobierzY(), 0, wysokoscPlanszy - 1);
    // Zapisujemy skorygowane wspolrzedne.
    pozycja.ustaw(x, y);
}

// Zwraca aktualna pozycje zaby.
Pozycja Zaba::pobierzPozycje() const {
    // Zwracamy kopie obiektu pozycji.
    return pozycja;
}
