// Dolaczamy deklaracje klasy Samochod.
#include "Samochod.h"

// Konstruktor zapisuje wszystkie parametry startowe auta.
Samochod::Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
                   int wariantKoloruParam)
    : x(xStart),
      y(yStale),
      predkoscPikseleNaSek(predkosc),
      kierunekRuchu(kierunek),
      szerokoscPlanszyPiksele(szerokosc),
      wariantKoloru(wariantKoloruParam % 3) {}

// Aktualizuje pozycje auta o krok czasu.
void Samochod::aktualizuj(float deltaSekundy, float mnoznikTempa) {
    // Liczymy dystans: predkosc * tempo * czas.
    const float dystans = predkoscPikseleNaSek * mnoznikTempa * deltaSekundy;
    // Margines pozwala autu "wyjechac" troszke poza ekran przed zapetleniem.
    const float marginesPozaPlansza = 36.0f;

    // Jesli auto jedzie w prawo...
    if (kierunekRuchu == Kierunek::PRAWO) {
        // ...to zwiekszamy X.
        x += dystans;
        // Gdy auto zniknie calkiem za prawa krawedzia, przenosimy je na lewa strone.
        if (x > szerokoscPlanszyPiksele + marginesPozaPlansza) {
            x = -marginesPozaPlansza;
        }
    } else {
        // Jesli auto jedzie w lewo, zmniejszamy X.
        x -= dystans;
        // Gdy auto zniknie za lewa krawedzia, przenosimy je na prawa strone.
        if (x < -marginesPozaPlansza) {
            x = szerokoscPlanszyPiksele + marginesPozaPlansza;
        }
    }
}

// Zwraca biezaca pozycje pozioma auta.
float Samochod::pobierzX() const { return x; }

// Zwraca biezaca pozycje pionowa auta.
float Samochod::pobierzY() const { return y; }

// Zwraca wariant koloru auta.
int Samochod::pobierzWariantKoloru() const { return wariantKoloru; }

// Ustawia nowa pozycje X auta.
void Samochod::ustawX(float nowyX) { x = nowyX; }
