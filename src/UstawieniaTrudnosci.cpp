// Dolaczamy deklaracje funkcji i struktury ustawien.
#include "UstawieniaTrudnosci.h"

// Dolaczamy algorytmy STL (tu: max_element).
#include <algorithm>

// Zwraca gotowy zestaw liczb dla wybranego poziomu trudnosci.
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom) {
    // Wybieramy konfiguracje zalezn ie od enumu trudnosci.
    switch (poziom) {
        case PoziomTrudnosci::LATWY:
            // Latwy: mniej pasow i lagodniejsze parametry.
            return UstawieniaTrudnosci{
                11, {1, 2, 4, 5}, 118.0f, 0.82f, 120.0f, 2, 4, 4};
        case PoziomTrudnosci::SREDNI:
            // Sredni: wiecej pasow i gestszy ruch niz na latwym.
            return UstawieniaTrudnosci{
                11, {1, 2, 3, 4, 6, 7, 8, 9}, 128.0f, 0.68f, 102.0f, 2, 4, 4};
        case PoziomTrudnosci::TRUDNY:
            // Trudny: najwiecej pasow i najwyzsza dynamika ruchu.
            return UstawieniaTrudnosci{
                15, {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}, 168.0f, 0.58f, 78.0f, 3, 4, 4};
    }

    // Zabezpieczenie awaryjne (teoretycznie nie powinno byc potrzebne).
    return UstawieniaTrudnosci{};
}

// Wyznacza numer ostatniego wiersza, ktory nalezy do drogi.
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia) {
    // Jesli lista pasow jest pusta, przyjmujemy domyslnie przedostatni wiersz.
    if (ustawienia.wierszePasow.empty()) {
        return ustawienia.wysokoscSiatki - 2;
    }

    // W przeciwnym razie bierzemy maksymalny numer wiersza z listy pasow.
    return *std::max_element(ustawienia.wierszePasow.begin(), ustawienia.wierszePasow.end());
}

// Wyznacza numer wiersza mety (pierwszy zielony za droga).
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia) {
    // Meta to jeden wiersz za ostatnim pasem drogi.
    return pobierzOstatniPasDrogi(ustawienia) + 1;
}

// Sprawdza, czy dany numer wiersza jest pasem drogowym.
bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia) {
    // Przegladamy wszystkie wiersze pasow zapisane w konfiguracji.
    for (const int pas : ustawienia.wierszePasow) {
        // Gdy znajdziemy dopasowanie, zwracamy prawde.
        if (pas == wiersz) {
            return true;
        }
    }
    // Jesli nie znaleziono dopasowania, to nie jest pas drogi.
    return false;
}
