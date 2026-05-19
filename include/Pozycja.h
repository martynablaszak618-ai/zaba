#pragma once

// Prosta klasa wspolrzednych planszy.
class Pozycja {
public:
    Pozycja() = default;
    Pozycja(int nowyX, int nowyY);

    int pobierzX() const;
    int pobierzY() const;
    void ustaw(int nowyX, int nowyY);

private:
    int x = 0;
    int y = 0;
};
