// Dyrektywa pilnuje pojedynczego dolaczenia pliku w kompilacji.
#pragma once

// Potrzebujemy informacji o drodze i pasach.
#include "Droga.h"
// Potrzebujemy danych o tym, ktore wiersze sa pasami.
#include "UstawieniaTrudnosci.h"
// Potrzebujemy aktualnej pozycji zaby.
#include "Zaba.h"

// Ta klasa odpowiada tylko za wykrywanie kolizji zaby z autem.
class WykrywaczKolizji {
public:
    // Sprawdza, czy w biezacej klatce doszlo do zderzenia.
    bool czyJestKolizja(const Zaba& zaba,
                        const Droga& droga,
                        float rozmiarPola,
                        int szerokoscSiatki,
                        int wysokoscSiatki,
                        const UstawieniaTrudnosci& ustawienia) const;
};
