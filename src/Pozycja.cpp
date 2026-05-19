#include "Pozycja.h"

Pozycja::Pozycja(int nowyX, int nowyY) : x(nowyX), y(nowyY) {}

int Pozycja::pobierzX() const { return x; }

int Pozycja::pobierzY() const { return y; }

void Pozycja::ustaw(int nowyX, int nowyY) {
    x = nowyX;
    y = nowyY;
}
