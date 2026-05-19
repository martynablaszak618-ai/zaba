#pragma once

#include "Typy.h"

// Pojedynczy samochod poruszajacy sie po poziomym pasie.
class Samochod {
public:
    Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
             int wariantKoloru);

    // Ruch auta w czasie; po wyjechaniu poza ekran wraca z drugiej strony.
    void aktualizuj(float deltaSekundy, float mnoznikTempa);

    float pobierzX() const;
    float pobierzY() const;
    int pobierzWariantKoloru() const;
    void ustawX(float nowyX);

private:
    float x = 0.0f;
    float y = 0.0f;
    float predkoscPikseleNaSek = 100.0f;
    Kierunek kierunekRuchu = Kierunek::PRAWO;
    float szerokoscPlanszyPiksele = 800.0f;
    int wariantKoloru = 0;
};
