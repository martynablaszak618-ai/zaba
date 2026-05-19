#include "Zaba.h"

#include <algorithm>

void Zaba::ustawPozycjeStartowa(int xStart, int yStart) {
    pozycja.ustaw(xStart, yStart);
}

void Zaba::ruchWGore(int krok) {
    pozycja.ustaw(pozycja.pobierzX(), pozycja.pobierzY() + krok);
}

void Zaba::ruchWDol(int krok) {
    pozycja.ustaw(pozycja.pobierzX(), pozycja.pobierzY() - krok);
}

void Zaba::ruchWLewo(int krok) {
    pozycja.ustaw(pozycja.pobierzX() - krok, pozycja.pobierzY());
}

void Zaba::ruchWPrawo(int krok) {
    pozycja.ustaw(pozycja.pobierzX() + krok, pozycja.pobierzY());
}

void Zaba::ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy) {
    const int x = std::clamp(pozycja.pobierzX(), 0, szerokoscPlanszy - 1);
    const int y = std::clamp(pozycja.pobierzY(), 0, wysokoscPlanszy - 1);
    pozycja.ustaw(x, y);
}

Pozycja Zaba::pobierzPozycje() const {
    return pozycja;
}
