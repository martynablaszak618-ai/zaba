#pragma once

#include "Droga.h"
#include "ScenariuszRuchu.h"
#include "Typy.h"
#include "UstawieniaTrudnosci.h"
#include "WykrywaczKolizji.h"
#include "Zaba.h"
#include "ZegarGry.h"

#include <random>

// Ta klasa przechowuje sama logike gry, bez kodu GUI.
class Gra {
public:
    Gra();
    void rozpocznijGre(PoziomTrudnosci poziom);
    void przejdzDoMenu();

    // Reakcja na komendy ruchu z GUI.
    void ruchWGore();
    void ruchWDol();
    void ruchWLewo();
    void ruchWPrawo();

    // Aktualizacja swiata gry wykonywana stale co krotki krok czasu.
    void aktualizujKrok(float deltaSekundy);

    StanGry pobierzStan() const;
    PoziomTrudnosci pobierzPoziomTrudnosci() const;
    const Zaba& pobierzZabe() const;
    const Droga& pobierzDroge() const;
    int pobierzCzasSekundy() const;
    int pobierzSzerokoscSiatki() const;
    int pobierzWysokoscSiatki() const;
    float pobierzRozmiarPola() const;
    const std::string& pobierzNazweScenariusza() const;

private:
    void sprawdzWarunkiKonca();
    void finalizujOczekujacaWygrana();

    StanGry stan = StanGry::MENU;
    PoziomTrudnosci poziomTrudnosci = PoziomTrudnosci::LATWY;
    UstawieniaTrudnosci ustawienia{};
    Zaba zaba;
    Droga droga;
    WykrywaczKolizji wykrywaczKolizji;
    ZegarGry zegar;

    int szerokoscSiatki = 16;
    int wysokoscSiatki = 12;
    std::mt19937 generator;
    float rozmiarPola = 60.0f;
    ScenariuszRuchu scenariuszRuchu{};
    bool czekaNaKlatkeMety = false;
};
