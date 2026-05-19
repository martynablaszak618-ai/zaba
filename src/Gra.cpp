#include "Gra.h"

Gra::Gra() : generator(std::random_device{}()) {}

void Gra::rozpocznijGre(PoziomTrudnosci poziom) {
    poziomTrudnosci = poziom;
    ustawienia = pobierzUstawieniaTrudnosci(poziom);
    wysokoscSiatki = ustawienia.wysokoscSiatki;
    rozmiarPola = 660.0f / static_cast<float>(wysokoscSiatki);

    const float szerokoscPlanszy = static_cast<float>(szerokoscSiatki) * rozmiarPola;
    const float wysokoscPlanszy = static_cast<float>(wysokoscSiatki) * rozmiarPola;
    scenariuszRuchu = wylosujScenariusz(generator, poziom);
    droga.skonfiguruj(ustawienia, szerokoscPlanszy, wysokoscPlanszy, rozmiarPola, scenariuszRuchu);

    zaba.ustawPozycjeStartowa(szerokoscSiatki / 2, 0);
    czekaNaKlatkeMety = false;
    zegar.start();
    stan = StanGry::W_TRAKCIE;
}

void Gra::przejdzDoMenu() {
    czekaNaKlatkeMety = false;
    stan = StanGry::MENU;
}

void Gra::ruchWGore() {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    zaba.ruchWGore(1);
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    sprawdzWarunkiKonca();
}

void Gra::ruchWDol() {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    zaba.ruchWDol(1);
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    sprawdzWarunkiKonca();
}

void Gra::ruchWLewo() {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    zaba.ruchWLewo(1);
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    sprawdzWarunkiKonca();
}

void Gra::ruchWPrawo() {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    zaba.ruchWPrawo(1);
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    sprawdzWarunkiKonca();
}

void Gra::aktualizujKrok(float deltaSekundy) {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }

    if (czekaNaKlatkeMety) {
        finalizujOczekujacaWygrana();
        return;
    }

    sprawdzWarunkiKonca();
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }

    droga.aktualizuj(deltaSekundy, generator);
    sprawdzWarunkiKonca();
}

void Gra::sprawdzWarunkiKonca() {
    if (wykrywaczKolizji.czyJestKolizja(zaba, droga, rozmiarPola, szerokoscSiatki, wysokoscSiatki,
                                        ustawienia)) {
        stan = StanGry::PRZEGRANA;
        zegar.stop();
        return;
    }

    const int wierszZaby = zaba.pobierzPozycje().pobierzY();
    const int wierszMety = pobierzWierszMety(ustawienia);

    // Najpierw pokaz klatke z zaba na zielonym polu mety, potem ekran koncowy.
    if (wierszZaby == wierszMety) {
        czekaNaKlatkeMety = true;
    }
}

void Gra::finalizujOczekujacaWygrana() {
    if (!czekaNaKlatkeMety) {
        return;
    }

    czekaNaKlatkeMety = false;
    stan = StanGry::WYGRANA;
    zegar.stop();
}

const std::string& Gra::pobierzNazweScenariusza() const {
    return scenariuszRuchu.nazwa;
}

StanGry Gra::pobierzStan() const { return stan; }

PoziomTrudnosci Gra::pobierzPoziomTrudnosci() const { return poziomTrudnosci; }

const Zaba& Gra::pobierzZabe() const { return zaba; }

const Droga& Gra::pobierzDroge() const { return droga; }

int Gra::pobierzCzasSekundy() const { return zegar.pobierzSekundy(); }

int Gra::pobierzSzerokoscSiatki() const { return szerokoscSiatki; }

int Gra::pobierzWysokoscSiatki() const { return wysokoscSiatki; }

float Gra::pobierzRozmiarPola() const { return rozmiarPola; }
