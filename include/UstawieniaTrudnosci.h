// Ta dyrektywa uniemozliwia wielokrotne dolaczenie tego pliku.
#pragma once

// Potrzebujemy enumu PoziomTrudnosci z typow wspolnych.
#include "Typy.h"

// Potrzebujemy wektora do listy numerow wierszy drogowych.
#include <vector>

// Ta struktura trzyma wszystkie liczby opisujace poziom trudnosci.
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

// Funkcja zwraca komplet ustawien dla wybranego poziomu trudnosci.
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom);

// Funkcja znajduje numer ostatniego wiersza, ktory jest droga.
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia);

// Funkcja zwraca numer pierwszego wiersza mety (zielony teren za droga).
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia);

// Funkcja sprawdza, czy konkretny wiersz nalezy do listy pasow drogowych.
bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia);
