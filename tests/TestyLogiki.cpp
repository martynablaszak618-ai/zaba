#include "Gra.h"
#include "UstawieniaTrudnosci.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

void oczekuj(bool warunek, const std::string& wiadomosc) {
    if (!warunek) {
        std::cerr << "BLAD TESTU: " << wiadomosc << "\n";
        std::exit(1);
    }
}

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

void testRuchuZabyIGranicPlanszy() {
    Gra gra;
    gra.rozpocznijGre(PoziomTrudnosci::LATWY);

    // Ruch do dolu od dolnej granicy nie moze zejsc ponizej planszy.
    for (int i = 0; i < 10; ++i) {
        gra.ruchWDol();
    }
    oczekuj(gra.pobierzZabe().pobierzPozycje().pobierzY() == 0, "Zaba zeszla ponizej planszy");

    // Ruch do lewej od lewej granicy nie moze zejsc poza plansze.
    for (int i = 0; i < 100; ++i) {
        gra.ruchWLewo();
    }
    oczekuj(gra.pobierzZabe().pobierzPozycje().pobierzX() == 0, "Zaba wyszla poza lewa granice");
}

void testBrakKolizjiNaTrawie() {
    Gra gra;
    gra.rozpocznijGre(PoziomTrudnosci::LATWY);

    // Wiersz 3 to trawa miedzy dwiema ulicami (pasy: 1,2,4,5).
    for (int i = 0; i < 3; ++i) {
        gra.ruchWGore();
    }
    for (int i = 0; i < 120; ++i) {
        gra.aktualizujKrok(0.016f);
    }
    oczekuj(gra.pobierzStan() == StanGry::W_TRAKCIE,
            "Na trawie nie powinna pojawiac sie przegrana bez kontaktu z autem");
}

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
        graLatwa.ruchWGore();
    }
    oczekuj(graLatwa.pobierzStan() == StanGry::W_TRAKCIE,
            "Latwy: na ostatnim pasie drogi nie powinno byc wygranej");
    graLatwa.ruchWGore();
    graLatwa.aktualizujKrok(0.0f);
    oczekuj(graLatwa.pobierzStan() == StanGry::WYGRANA,
            "Latwy: wygrana na pierwszym zielonym polu za ostatnia droga");

    Gra graSrednia;
    graSrednia.rozpocznijGre(PoziomTrudnosci::SREDNI);
    for (int i = 0; i < ostatniPasSredni; ++i) {
        graSrednia.ruchWGore();
    }
    oczekuj(graSrednia.pobierzStan() == StanGry::W_TRAKCIE,
            "Sredni: na ostatnim pasie drogi nie powinno byc wygranej");
    graSrednia.ruchWGore();
    graSrednia.aktualizujKrok(0.0f);
    oczekuj(graSrednia.pobierzStan() == StanGry::WYGRANA,
            "Sredni: wygrana dopiero po wejsciu na zielony teren mety");
    oczekuj(graSrednia.pobierzZabe().pobierzPozycje().pobierzY() == wierszMetySredni,
            "Sredni: wygrana powinna byc na wierszu mety, nie na pasie drogi");
}

}  // namespace

int main() {
    testUstawienTrudnosci();
    testRuchuZabyIGranicPlanszy();
    testBrakKolizjiNaTrawie();
    testWarunkuWygranej();

    std::cout << "OK: Wszystkie testy przeszly.\n";
    return 0;
}
