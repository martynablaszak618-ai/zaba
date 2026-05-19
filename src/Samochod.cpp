#include "Samochod.h"

Samochod::Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
                   int wariantKoloruParam)
    : x(xStart),
      y(yStale),
      predkoscPikseleNaSek(predkosc),
      kierunekRuchu(kierunek),
      szerokoscPlanszyPiksele(szerokosc),
      wariantKoloru(wariantKoloruParam % 3) {}

void Samochod::aktualizuj(float deltaSekundy, float mnoznikTempa) {
    const float dystans = predkoscPikseleNaSek * mnoznikTempa * deltaSekundy;
    const float marginesPozaPlansza = 36.0f;

    if (kierunekRuchu == Kierunek::PRAWO) {
        x += dystans;
        if (x > szerokoscPlanszyPiksele + marginesPozaPlansza) {
            x = -marginesPozaPlansza;
        }
    } else {
        x -= dystans;
        if (x < -marginesPozaPlansza) {
            x = szerokoscPlanszyPiksele + marginesPozaPlansza;
        }
    }
}

float Samochod::pobierzX() const { return x; }

float Samochod::pobierzY() const { return y; }

int Samochod::pobierzWariantKoloru() const { return wariantKoloru; }

void Samochod::ustawX(float nowyX) { x = nowyX; }
