#pragma once

#include "Typy.h"

#include <vector>

// Parametry poziomu trudnosci uzywane do konfiguracji calej rozgrywki.
struct UstawieniaTrudnosci {
    int wysokoscSiatki = 5;
    std::vector<int> wierszePasow;
    float predkoscSamochodow = 100.0f;   // piksele/sekunde
    float interwalTworzeniaAuta = 1.2f;  // sekundy
    float minimalnyOdstepAut = 150.0f;   // piksele
    int autaNaStarcieMin = 1;
    int autaNaStarcieMax = 2;
    int maksAutNaPasie = 3;
};

// Fabryka ustawien dla poziomu wybranego przez gracza.
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom);

// Ostatni wiersz z droga (asfalt).
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia);

// Pierwszy zielony wiersz za ostatnim pasem drogi (strefa mety).
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia);

bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia);
