// Ta dyrektywa zapobiega podwojnemu dolaczeniu tego samego pliku.
#pragma once

// Klasa przechowuje jedna pozycje na planszy: wspolrzedna X i Y.
class Pozycja {
public:
    // Konstruktor domyslny: tworzy pozycje (0, 0).
    Pozycja() = default;
    // Konstruktor z parametrami: tworzy pozycje z konkretnym X i Y.
    Pozycja(int nowyX, int nowyY);

    // Metoda zwraca aktualna wartosc wspolrzednej X.
    int pobierzX() const;
    // Metoda zwraca aktualna wartosc wspolrzednej Y.
    int pobierzY() const;
    // Metoda ustawia nowa wartosc X i nowa wartosc Y.
    void ustaw(int nowyX, int nowyY);

private:
    // Pole przechowuje wspolrzedna pozioma.
    int x = 0;
    // Pole przechowuje wspolrzedna pionowa.
    int y = 0;
};
