// Ta dyrektywa pilnuje pojedynczego dolaczenia pliku naglowkowego.
#pragma once

// Dolaczamy klase Droga (zarzadzanie pasami i autami).
#include "Droga.h"
// Dolaczamy strukture scenariusza ruchu.
#include "ScenariuszRuchu.h"
// Dolaczamy podstawowe typy enum (stan, trudnosc, kierunek).
#include "Typy.h"
// Dolaczamy konfiguracje poziomu.
#include "UstawieniaTrudnosci.h"
// Dolaczamy detektor kolizji.
#include "WykrywaczKolizji.h"
// Dolaczamy klase gracza (zaby).
#include "Zaba.h"
// Dolaczamy licznik czasu rozgrywki.
#include "ZegarGry.h"

// Dolaczamy generator liczb losowych.
#include <random>

// Ta klasa to "serce" logiki gry, niezalezne od GUI.
class Gra {
public:
    // Konstruktor przygotowuje generator losowy i stan poczatkowy.
    Gra();
    // Startuje nowa gre na podanym poziomie trudnosci.
    void rozpocznijGre(PoziomTrudnosci poziom);
    // Wraca do menu glownego.
    void przejdzDoMenu();

    // Metody ruchu wywolywane po nacisnieciu klawiszy sterowania.
    void ruchWGore();
    void ruchWDol();
    void ruchWLewo();
    void ruchWPrawo();

    // Aktualizuje swiat gry o krok czasu (deltaSekundy).
    void aktualizujKrok(float deltaSekundy);

    // Zwraca aktualny stan gry (menu/trwa/koniec).
    StanGry pobierzStan() const;
    // Zwraca aktualny poziom trudnosci.
    PoziomTrudnosci pobierzPoziomTrudnosci() const;
    // Zwraca obiekt zaby (tylko do odczytu).
    const Zaba& pobierzZabe() const;
    // Zwraca obiekt drogi (tylko do odczytu).
    const Droga& pobierzDroge() const;
    // Zwraca liczbe sekund rozgrywki.
    int pobierzCzasSekundy() const;
    // Zwraca liczbe kolumn planszy.
    int pobierzSzerokoscSiatki() const;
    // Zwraca liczbe wierszy planszy.
    int pobierzWysokoscSiatki() const;
    // Zwraca rozmiar jednego pola planszy w pikselach.
    float pobierzRozmiarPola() const;
    // Zwraca nazwe aktualnie aktywnego scenariusza ruchu.
    const std::string& pobierzNazweScenariusza() const;

private:
    // Sprawdza, czy nastapila kolizja albo warunek wygranej.
    void sprawdzWarunkiKonca();
    // Konczy "oczekujaca" wygrana po dodatkowej klatce.
    void finalizujOczekujacaWygrana();

    // Aktualny stan aplikacji.
    StanGry stan = StanGry::MENU;
    // Zapamietany poziom trudnosci.
    PoziomTrudnosci poziomTrudnosci = PoziomTrudnosci::LATWY;
    // Biezace parametry poziomu.
    UstawieniaTrudnosci ustawienia{};
    // Obiekt gracza.
    Zaba zaba;
    // Obiekt drogi z pasami ruchu.
    Droga droga;
    // Narzedzie do sprawdzania kolizji.
    WykrywaczKolizji wykrywaczKolizji;
    // Zegar gry.
    ZegarGry zegar;

    // Liczba kolumn planszy.
    int szerokoscSiatki = 16;
    // Liczba wierszy planszy.
    int wysokoscSiatki = 12;
    // Generator losowy uzywany w calej logice.
    std::mt19937 generator;
    // Rozmiar jednego pola planszy w pikselach.
    float rozmiarPola = 60.0f;
    // Aktualny scenariusz ruchu aut.
    ScenariuszRuchu scenariuszRuchu{};
    // Flaga opozniajaca ekran wygranej o jedna klatke.
    bool czekaNaKlatkeMety = false;
};
