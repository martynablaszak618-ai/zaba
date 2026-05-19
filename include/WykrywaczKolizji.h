#pragma once

#include "Droga.h"
#include "UstawieniaTrudnosci.h"
#include "Zaba.h"

// Klasa odpowiedzialna tylko za sprawdzanie przecięcia zaby i samochodu.
class WykrywaczKolizji {
public:
    bool czyJestKolizja(const Zaba& zaba,
                        const Droga& droga,
                        float rozmiarPola,
                        int szerokoscSiatki,
                        int wysokoscSiatki,
                        const UstawieniaTrudnosci& ustawienia) const;
};
