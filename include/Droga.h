/**
 * @file Droga.h
 * @brief Cala droga — zbior pasow ruchu na planszy.
 */

#pragma once

// Potrzebujemy klasy pojedynczego pasa.
#include "PasRuchu.h"
// Potrzebujemy ustawien poziomu trudnosci.
#include "UstawieniaTrudnosci.h"

// Biblioteka losowania (przekazywane do pasow przy aktualizacji).
#include <random>
// Biblioteka list dynamicznych.
#include <vector>

/** @brief Reprezentuje cala droge jako zbior pasow ruchu. */
class Droga {
public:
    /**
     * @brief Buduje pasy drogi na podstawie ustawien poziomu.
     * @param ustawienia Parametry trudnosci (wiersze pasow, predkosci).
     * @param szerokoscPlanszy Szerokosc planszy w pikselach.
     * @param wysokoscPlanszy Wysokosc planszy w pikselach.
     * @param wysokoscPola Rozmiar jednego pola siatki [px].
     */
    void skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                     float szerokoscPlanszy,
                     float wysokoscPlanszy,
                     float wysokoscPola);

    /** @brief Aktualizuje wszystkie pasy o jedna klatke symulacji. */
    void aktualizuj(float deltaSekundy, std::mt19937& generator);
    /** @return Lista pasow drogi. */
    const std::vector<PasRuchu>& pobierzPasy() const;
    /** @return Numery wierszy logicznych bedacych pasami. */
    const std::vector<int>& pobierzWierszePasow() const;

private:
    // Wszystkie pasy nalezace do tej drogi.
    std::vector<PasRuchu> pasy;
    // Numery wierszy logicznych odpowiadajace pasom.
    std::vector<int> wierszePasow;
};
