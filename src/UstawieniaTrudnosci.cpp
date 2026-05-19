#include "UstawieniaTrudnosci.h"

#include <algorithm>

UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom) {
    switch (poziom) {
        case PoziomTrudnosci::LATWY:
            // Latwy: wiecej aut i czestszy spawn niz wczesniej.
            return UstawieniaTrudnosci{
                11, {1, 2, 4, 5}, 118.0f, 0.82f, 120.0f, 2, 4, 4};
        case PoziomTrudnosci::SREDNI:
            // Sredni: wyzsza gestosc ruchu na wszystkich pasach.
            return UstawieniaTrudnosci{
                11, {1, 2, 3, 4, 6, 7, 8, 9}, 128.0f, 0.68f, 102.0f, 2, 4, 4};
        case PoziomTrudnosci::TRUDNY:
            // Trudny: najwieksza gestosc, najkrotszy odstep miedzy autami.
            return UstawieniaTrudnosci{
                15, {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}, 168.0f, 0.58f, 78.0f, 3, 4, 4};
    }

    return UstawieniaTrudnosci{};
}

int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia) {
    if (ustawienia.wierszePasow.empty()) {
        return ustawienia.wysokoscSiatki - 2;
    }

    return *std::max_element(ustawienia.wierszePasow.begin(), ustawienia.wierszePasow.end());
}

int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia) {
    return pobierzOstatniPasDrogi(ustawienia) + 1;
}

bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia) {
    for (const int pas : ustawienia.wierszePasow) {
        if (pas == wiersz) {
            return true;
        }
    }
    return false;
}
