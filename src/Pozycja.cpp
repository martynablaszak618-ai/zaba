// Dolaczamy deklaracje klasy Pozycja.
#include "Pozycja.h"

// Konstruktor zapisuje przekazane wspolrzedne jako aktualna pozycje.
Pozycja::Pozycja(int nowyX, int nowyY) : x(nowyX), y(nowyY) {}

// Getter zwraca biezaca wartosc osi X.
int Pozycja::pobierzX() const { return x; }

// Getter zwraca biezaca wartosc osi Y.
int Pozycja::pobierzY() const { return y; }

// Setter nadpisuje jednoczesnie wspolrzedna X i Y.
void Pozycja::ustaw(int nowyX, int nowyY) {
    // Ustawiamy nowy X.
    x = nowyX;
    // Ustawiamy nowy Y.
    y = nowyY;
}
