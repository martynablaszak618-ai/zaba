// Dolaczamy glowna logike gry do testowania.
#include "Gra.h"
// Dolaczamy funkcje pomocnicze ustawien poziomu.
#include "UstawieniaTrudnosci.h"

// Dolaczamy std::exit do natychmiastowego zakonczenia testu przy bledzie.
#include <cstdlib>
// Dolaczamy strumien bledow i wyjscia.
#include <iostream>
// Dolaczamy std::string do opisow bledow.
#include <string>

namespace {

// Pomocnicza asercja: konczy program, gdy warunek jest falszywy.
void oczekuj(bool warunek, const std::string& wiadomosc) {
    if (!warunek) {
        std::cerr << "BLAD TESTU: " << wiadomosc << "\n";
        std::exit(1);
    }
}

// Test sprawdza podstawowe parametry poziomow trudnosci.
void testUstawienTrudnosci() {
    const UstawieniaTrudnosci latwy = pobierzUstawieniaTrudnosci(PoziomTrudnosci::LATWY);
    const UstawieniaTrudnosci sredni = pobierzUstawieniaTrudnosci(PoziomTrudnosci::SREDNI);
    const UstawieniaTrudnosci trudny = pobierzUstawieniaTrudnosci(PoziomTrudnosci::TRUDNY);

    oczekuj(latwy.wierszePasow.size() == 4, "Poziom latwy powinien miec 2 ulice po 2 pasy");
    oczekuj(sredni.wierszePasow.size() == 8, "Poziom sredni powinien miec 2 drogi po 4 pasy");
    oczekuj(trudny.wierszePasow.size() == 12, "Poziom trudny powinien miec 2 drogi po 6 pasow");
    oczekuj(latwy.predkoscSamochodow < sredni.predkoscSamochodow &&
                sredni.predkoscSamochodow < trudny.predkoscSamochodow,
            "Predkosc samochodow powinna rosnac wraz z trudnoscia");
}

// Test sprawdza, czy zaba nie moze wyjsc poza plansze.
void testRuchuZabyIGranicPlanszy() {
    Gra gra;
    gra.rozpocznijGre(PoziomTrudnosci::LATWY);

    // Ruch do dolu od dolnej granicy nie moze zejsc ponizej planszy.
    for (int i = 0; i < 10; ++i) {
        gra.ruch(0, -1);
    }
    oczekuj(gra.pobierzZabe().pobierzY() == 0, "Zaba zeszla ponizej planszy");

    // Ruch do lewej od lewej granicy nie moze zejsc poza plansze.
    for (int i = 0; i < 100; ++i) {
        gra.ruch(-1, 0);
    }
    oczekuj(gra.pobierzZabe().pobierzX() == 0, "Zaba wyszla poza lewa granice");
}

// Test sprawdza, czy na trawie nie dochodzi do falszywej kolizji.
void testBrakKolizjiNaTrawie() {
    Gra gra;
    gra.rozpocznijGre(PoziomTrudnosci::LATWY);

    // Wiersz 3 to trawa miedzy dwiema ulicami (pasy: 1,2,4,5).
    for (int i = 0; i < 3; ++i) {
        gra.ruch(0, 1);
    }
    for (int i = 0; i < 120; ++i) {
        gra.aktualizujKrok(0.016f);
    }
    oczekuj(gra.pobierzStan() == StanGry::W_TRAKCIE,
            "Na trawie nie powinna pojawiac sie przegrana bez kontaktu z autem");
}

// Test sprawdza, czy wygrana pojawia sie dopiero na wierszu mety.
void testWarunkuWygranej() {
    const UstawieniaTrudnosci latwy = pobierzUstawieniaTrudnosci(PoziomTrudnosci::LATWY);
    const UstawieniaTrudnosci sredni = pobierzUstawieniaTrudnosci(PoziomTrudnosci::SREDNI);
    const int wierszMetyLatwy = pobierzWierszMety(latwy);
    const int wierszMetySredni = pobierzWierszMety(sredni);
    const int ostatniPasSredni = pobierzOstatniPasDrogi(sredni);
    const int ostatniPasLatwy = pobierzOstatniPasDrogi(latwy);

    Gra graLatwa;
    graLatwa.rozpocznijGre(PoziomTrudnosci::LATWY);
    for (int i = 0; i < ostatniPasLatwy; ++i) {
        graLatwa.ruch(0, 1);
    }
    oczekuj(graLatwa.pobierzStan() == StanGry::W_TRAKCIE,
            "Latwy: na ostatnim pasie drogi nie powinno byc wygranej");
    graLatwa.ruch(0, 1);
    graLatwa.aktualizujKrok(0.0f);
    oczekuj(graLatwa.pobierzStan() == StanGry::WYGRANA,
            "Latwy: wygrana na pierwszym zielonym polu za ostatnia droga");

    Gra graSrednia;
    graSrednia.rozpocznijGre(PoziomTrudnosci::SREDNI);
    for (int i = 0; i < ostatniPasSredni; ++i) {
        graSrednia.ruch(0, 1);
    }
    oczekuj(graSrednia.pobierzStan() == StanGry::W_TRAKCIE,
            "Sredni: na ostatnim pasie drogi nie powinno byc wygranej");
    graSrednia.ruch(0, 1);
    graSrednia.aktualizujKrok(0.0f);
    oczekuj(graSrednia.pobierzStan() == StanGry::WYGRANA,
            "Sredni: wygrana dopiero po wejsciu na zielony teren mety");
    oczekuj(graSrednia.pobierzZabe().pobierzY() == wierszMetySredni,
            "Sredni: wygrana powinna byc na wierszu mety, nie na pasie drogi");
}

}  // namespace

// Punkt startowy testow uruchamianych przez CTest.
int main() {
    testUstawienTrudnosci();
    testRuchuZabyIGranicPlanszy();
    testBrakKolizjiNaTrawie();
    testWarunkuWygranej();

    std::cout << "OK: Wszystkie testy przeszly.\n";
    return 0;
}
