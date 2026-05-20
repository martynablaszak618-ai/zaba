// Dolaczamy deklaracje klasy Gra.
#include "Gra.h"

// Konstruktor inicjalizuje generator losowy losowym ziarnem.
Gra::Gra() : generator(std::random_device{}()) {}

// Startuje nowa rozgrywke na wskazanym poziomie trudnosci.
void Gra::rozpocznijGre(PoziomTrudnosci poziom) {
    // Zapamietujemy poziom trudnosci.
    poziomTrudnosci = poziom;
    // Pobieramy parametry gry dla tego poziomu.
    ustawienia = pobierzUstawieniaTrudnosci(poziom);
    // Aktualizujemy wysokosc planszy logicznej.
    wysokoscSiatki = ustawienia.wysokoscSiatki;
    // Wyliczamy rozmiar jednego pola tak, aby plansza miala 660 px wysokosci.
    rozmiarPola = 660.0f / static_cast<float>(wysokoscSiatki);

    // Obliczamy szerokosc planszy w pikselach.
    const float szerokoscPlanszy = static_cast<float>(szerokoscSiatki) * rozmiarPola;
    // Obliczamy wysokosc planszy w pikselach.
    const float wysokoscPlanszy = static_cast<float>(wysokoscSiatki) * rozmiarPola;
    // Losujemy scenariusz ruchu samochodow na dana rozgrywke.
    scenariuszRuchu = wylosujScenariusz(generator, poziom);
    // Budujemy droge i pasy z pelnym zestawem parametrow.
    droga.skonfiguruj(ustawienia, szerokoscPlanszy, wysokoscPlanszy, rozmiarPola, scenariuszRuchu);

    // Ustawiamy abe na pozycji startowej (srodek dolnego wiersza).
    zaba.ustawPozycjeStartowa(szerokoscSiatki / 2, 0);
    // Czyscimy ewentualna flage oczekiwania na finalizacje wygranej.
    czekaNaKlatkeMety = false;
    // Uruchamiamy licznik czasu gry.
    zegar.start();
    // Przechodzimy do stanu aktywnej rozgrywki.
    stan = StanGry::W_TRAKCIE;
}

// Wraca do ekranu menu.
void Gra::przejdzDoMenu() {
    // Resetujemy flage oczekiwania na wygrana.
    czekaNaKlatkeMety = false;
    // Ustawiamy stan menu.
    stan = StanGry::MENU;
}

// Obsluguje ruch zaby o jedno pole w gore.
void Gra::ruchWGore() {
    // Jesli gra nie trwa, ignorujemy sterowanie.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    // Przesuwamy abe.
    zaba.ruchWGore(1);
    // Pilnujemy granic planszy.
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    // Po ruchu sprawdzamy warunki konca.
    sprawdzWarunkiKonca();
}

// Obsluguje ruch zaby o jedno pole w dol.
void Gra::ruchWDol() {
    // Jesli gra nie trwa, ignorujemy sterowanie.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    // Przesuwamy abe.
    zaba.ruchWDol(1);
    // Pilnujemy granic planszy.
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    // Po ruchu sprawdzamy warunki konca.
    sprawdzWarunkiKonca();
}

// Obsluguje ruch zaby o jedno pole w lewo.
void Gra::ruchWLewo() {
    // Jesli gra nie trwa, ignorujemy sterowanie.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    // Przesuwamy abe.
    zaba.ruchWLewo(1);
    // Pilnujemy granic planszy.
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    // Po ruchu sprawdzamy warunki konca.
    sprawdzWarunkiKonca();
}

// Obsluguje ruch zaby o jedno pole w prawo.
void Gra::ruchWPrawo() {
    // Jesli gra nie trwa, ignorujemy sterowanie.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    // Przesuwamy abe.
    zaba.ruchWPrawo(1);
    // Pilnujemy granic planszy.
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    // Po ruchu sprawdzamy warunki konca.
    sprawdzWarunkiKonca();
}

// Aktualizacja logiki wykonywana co klatke.
void Gra::aktualizujKrok(float deltaSekundy) {
    // Jesli gra nie trwa, nic nie aktualizujemy.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }

    // Jesli czekamy na finalna klatke mety, zamykamy wygrana i konczymy krok.
    if (czekaNaKlatkeMety) {
        finalizujOczekujacaWygrana();
        return;
    }

    // Najpierw sprawdzamy, czy nie ma juz stanu koncowego.
    sprawdzWarunkiKonca();
    // Jesli stan sie zmienil (przegrana/wygrana), przerywamy ten krok.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }

    // Aktualizujemy ruch na drodze.
    droga.aktualizuj(deltaSekundy, generator);
    // Po ruchu aut ponownie sprawdzamy warunki konca.
    sprawdzWarunkiKonca();
}

// Sprawdza wszystkie warunki koncowe rozgrywki.
void Gra::sprawdzWarunkiKonca() {
    // Kolizja z autem oznacza natychmiastowa przegrana.
    if (wykrywaczKolizji.czyJestKolizja(zaba, droga, rozmiarPola, szerokoscSiatki, wysokoscSiatki,
                                        ustawienia)) {
        stan = StanGry::PRZEGRANA;
        zegar.stop();
        return;
    }

    // Pobieramy aktualny wiersz zaby.
    const int wierszZaby = zaba.pobierzPozycje().pobierzY();
    // Pobieramy docelowy wiersz mety.
    const int wierszMety = pobierzWierszMety(ustawienia);

    // Gdy zaba wejdzie na mete, ustawiamy flage finalizacji w nastepnej klatce.
    if (wierszZaby == wierszMety) {
        czekaNaKlatkeMety = true;
    }
}

// Finalizuje wygrana po jednorazowym opoznieniu o jedna klatke.
void Gra::finalizujOczekujacaWygrana() {
    // Jesli flaga nie jest ustawiona, nie robimy nic.
    if (!czekaNaKlatkeMety) {
        return;
    }

    // Czyscimy flage oczekiwania.
    czekaNaKlatkeMety = false;
    // Ustawiamy stan wygranej.
    stan = StanGry::WYGRANA;
    // Zatrzymujemy licznik czasu.
    zegar.stop();
}

// Zwraca nazwe aktywnego scenariusza ruchu.
const std::string& Gra::pobierzNazweScenariusza() const {
    return scenariuszRuchu.nazwa;
}

// Getter: zwraca aktualny stan gry.
StanGry Gra::pobierzStan() const { return stan; }

// Getter: zwraca aktywny poziom trudnosci.
PoziomTrudnosci Gra::pobierzPoziomTrudnosci() const { return poziomTrudnosci; }

// Getter: zwraca obiekt zaby.
const Zaba& Gra::pobierzZabe() const { return zaba; }

// Getter: zwraca obiekt drogi.
const Droga& Gra::pobierzDroge() const { return droga; }

// Getter: zwraca czas gry w sekundach.
int Gra::pobierzCzasSekundy() const { return zegar.pobierzSekundy(); }

// Getter: zwraca szerokosc planszy (w polach).
int Gra::pobierzSzerokoscSiatki() const { return szerokoscSiatki; }

// Getter: zwraca wysokosc planszy (w polach).
int Gra::pobierzWysokoscSiatki() const { return wysokoscSiatki; }

// Getter: zwraca rozmiar jednego pola w pikselach.
float Gra::pobierzRozmiarPola() const { return rozmiarPola; }
