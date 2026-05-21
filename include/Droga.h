// Ta dyrektywa zapobiega wielokrotnemu dolaczaniu pliku.
#pragma once

// Potrzebujemy klasy pojedynczego pasa.
#include "PasRuchu.h"
// Potrzebujemy ustawien poziomu trudnosci.
#include "UstawieniaTrudnosci.h"

// Biblioteka losowania (przekazywane do pasow przy aktualizacji).
#include <random>
// Biblioteka list dynamicznych.
#include <vector>

// Klasa reprezentuje cala droge (czyli zbior wielu pasow ruchu).
class Droga {
public:
    // Buduje droge na podstawie ustawien i rozmiarow planszy.
    void skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                     float szerokoscPlanszy,
                     float wysokoscPlanszy,
                     float wysokoscPola);

    // Aktualizuje wszystkie pasy drogi.
    void aktualizuj(float deltaSekundy, std::mt19937& generator);
    // Zwraca liste pasow drogi.
    const std::vector<PasRuchu>& pobierzPasy() const;
    // Zwraca liste numerow wierszy, ktore sa pasami drogi.
    const std::vector<int>& pobierzWierszePasow() const;

private:
    // Wszystkie pasy nalezace do tej drogi.
    std::vector<PasRuchu> pasy;
    // Numery wierszy logicznych odpowiadajace pasom.
    std::vector<int> wierszePasow;
};
