/**
 * @file UstawieniaTrudnosci.h
 * @brief Parametry liczbowe poziomow trudnosci i funkcje pomocnicze planszy.
 */

#pragma once

// Potrzebujemy enumu PoziomTrudnosci z typow wspolnych.
#include "Typy.h"

// Potrzebujemy wektora do listy numerow wierszy drogowych.
#include <vector>

/** @brief Zestaw parametrow opisujacych jeden poziom trudnosci. */
struct UstawieniaTrudnosci {
    // Ile wierszy ma cala plansza gry.
    int wysokoscSiatki = 5;
    // Numery wierszy, ktore sa pasami ruchu (asfaltem).
    std::vector<int> wierszePasow;
    // Bazowa predkosc samochodow (piksele na sekunde).
    float predkoscSamochodow = 100.0f;
    // Co ile sekund tworzy sie nowe auto.
    float interwalTworzeniaAuta = 1.2f;
    // Minimalny wymagany odstep miedzy autami.
    float minimalnyOdstepAut = 150.0f;
    // Minimalna liczba aut na pasie na starcie.
    int autaNaStarcieMin = 1;
    // Maksymalna liczba aut na pasie na starcie.
    int autaNaStarcieMax = 2;
    // Gorna granica aut, jakie moga jednoczesnie byc na pasie.
    int maksAutNaPasie = 3;
};

/**
 * @brief Zwraca komplet ustawien dla wybranego poziomu trudnosci.
 * @param poziom Poziom LATWY, SREDNI lub TRUDNY.
 * @return Struktura UstawieniaTrudnosci z parametrami planszy i ruchu aut.
 */
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom);

/**
 * @brief Zwraca numer ostatniego wiersza bedacego pasem drogi.
 * @param ustawienia Biezaca konfiguracja poziomu.
 * @return Indeks wiersza (logika gry, Y=0 na dole).
 */
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia);

/**
 * @brief Zwraca numer wiersza mety (pierwszy zielony za droga).
 * @param ustawienia Biezaca konfiguracja poziomu.
 * @return Indeks wiersza mety.
 */
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia);

/**
 * @brief Sprawdza, czy dany wiersz jest pasem drogowym.
 * @param wiersz Numer wiersza do sprawdzenia.
 * @param ustawienia Biezaca konfiguracja poziomu.
 * @return true gdy wiersz nalezy do listy pasow.
 */
bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia);
