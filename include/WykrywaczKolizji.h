/**
 * @file WykrywaczKolizji.h
 * @brief Detekcja kolizji zaby z samochodami.
 */

#pragma once

// Potrzebujemy informacji o drodze i pasach.
#include "Droga.h"
// Potrzebujemy danych o tym, ktore wiersze sa pasami.
#include "UstawieniaTrudnosci.h"
// Potrzebujemy aktualnej pozycji zaby.
#include "Zaba.h"

/** @brief Sprawdza kolizje zaby z samochodami na pasie drogi. */
class WykrywaczKolizji {
public:
    /**
     * @brief Sprawdza, czy zaba zderzyla sie z autem.
     * @param zaba Obiekt gracza.
     * @param droga Droga z pasami i autami.
     * @param rozmiarPola Rozmiar pola siatki [px].
     * @param szerokoscSiatki Liczba kolumn (zarezerwowane).
     * @param wysokoscSiatki Liczba wierszy (zarezerwowane).
     * @param ustawienia Konfiguracja poziomu (lista pasow).
     * @return true gdy wykryto kolizje.
     */
    bool czyJestKolizja(const Zaba& zaba,
                        const Droga& droga,
                        float rozmiarPola,
                        int szerokoscSiatki,
                        int wysokoscSiatki,
                        const UstawieniaTrudnosci& ustawienia) const;
};
