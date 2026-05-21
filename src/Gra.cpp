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
    // Budujemy droge i pasy (predkosc i spawn z ustawien poziomu trudnosci).
    droga.skonfiguruj(ustawienia, szerokoscPlanszy, wysokoscPlanszy, rozmiarPola);

    // Ustawiamy abe na pozycji startowej (srodek dolnego wiersza).
    zaba.ustawPozycjeStartowa(szerokoscSiatki / 2, 0);
    // Czyscimy ewentualna flage oczekiwania na finalizacje wygranej.
    czekaNaKlatkeMety = false;
    // Uruchamiamy licznik czasu gry.
    uruchomZegar();
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

// Obsluguje ruch zaby o jedno pole w podanym kierunku (dx, dy).
void Gra::ruch(int dx, int dy) {
    // Jesli gra nie trwa, ignorujemy sterowanie.
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    // Przesuwamy abe.
    zaba.ruch(dx, dy, 1);
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
        zatrzymajZegar();
        return;
    }

    // Pobieramy aktualny wiersz zaby.
    const int wierszZaby = zaba.pobierzY();
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
    zatrzymajZegar();
}

// Rozpoczyna pomiar czasu od aktualnej chwili.
void Gra::uruchomZegar() {
    // Zapamietujemy punkt startowy.
    startCzasu = std::chrono::steady_clock::now();
    // Flaga mowi, ze zegar znowu pracuje.
    zegarZatrzymany = false;
}

// Zatrzymuje pomiar czasu.
void Gra::zatrzymajZegar() {
    // Zatrzymujemy tylko raz, zeby nie nadpisywac czasu zatrzymania.
    if (!zegarZatrzymany) {
        // Zapamietujemy moment stop.
        czasZatrzymania = std::chrono::steady_clock::now();
        // Flaga mowi, ze zegar jest zatrzymany.
        zegarZatrzymany = true;
    }
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
int Gra::pobierzCzasSekundy() const {
    // Jesli zegar stoi, koncem jest czas zatrzymania; w przeciwnym razie "teraz".
    const auto koniec = zegarZatrzymany ? czasZatrzymania : std::chrono::steady_clock::now();
    // Obliczamy roznice czasu i zamieniamy na cale sekundy.
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::seconds>(koniec - startCzasu).count());
}

// Getter: zwraca szerokosc planszy (w polach).
int Gra::pobierzSzerokoscSiatki() const { return szerokoscSiatki; }

// Getter: zwraca wysokosc planszy (w polach).
int Gra::pobierzWysokoscSiatki() const { return wysokoscSiatki; }

// Getter: zwraca rozmiar jednego pola w pikselach.
float Gra::pobierzRozmiarPola() const { return rozmiarPola; }
