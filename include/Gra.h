/**
 * @file Gra.h
 * @brief Glowna logika gry — niezalezna od warstwy graficznej Qt.
 */

#pragma once

// Dolaczamy klase Droga (zarzadzanie pasami i autami).
#include "Droga.h"
// Dolaczamy podstawowe typy enum (stan, trudnosc, kierunek).
#include "Typy.h"
// Dolaczamy konfiguracje poziomu.
#include "UstawieniaTrudnosci.h"
// Dolaczamy detektor kolizji.
#include "WykrywaczKolizji.h"
// Dolaczamy klase gracza (zaby).
#include "Zaba.h"

// Dolaczamy pomiar czasu rozgrywki (wczesniej osobna klasa ZegarGry).
#include <chrono>
// Dolaczamy generator liczb losowych.
#include <random>

/**
 * @brief Serce logiki gry — stan, zegar, ruch i warunki konca.
 * @details Klasa nie uzywa Qt; moze byc testowana bez GUI (testy_logiki).
 */
class Gra {
public:
    /** @brief Inicjalizuje generator losowy i stan MENU. */
    Gra();
    /** @brief Rozpoczyna nowa gre na wybranym poziomie trudnosci. */
    void rozpocznijGre(PoziomTrudnosci poziom);
    /** @brief Przechodzi do menu glownego. */
    void przejdzDoMenu();

    /**
     * @brief Przesuwa zabe o jedno pole.
     * @param dx Kierunek poziomy (-1, 0, 1).
     * @param dy Kierunek pionowy (1 = gora, -1 = dol).
     */
    void ruch(int dx, int dy);

    /**
     * @brief Aktualizuje symulacje o jedna klatke.
     * @param deltaSekundy Czas od poprzedniej klatki [s].
     */
    void aktualizujKrok(float deltaSekundy);

    /** @return Aktualny stan gry (MENU, W_TRAKCIE, WYGRANA, PRZEGRANA). */
    StanGry pobierzStan() const;
    /** @return Wybrany poziom trudnosci. */
    PoziomTrudnosci pobierzPoziomTrudnosci() const;
    /** @return Obiekt zaby (tylko odczyt). */
    const Zaba& pobierzZabe() const;
    /** @return Obiekt drogi (tylko odczyt). */
    const Droga& pobierzDroge() const;
    /** @return Czas rozgrywki w sekundach. */
    int pobierzCzasSekundy() const;
    /** @return Liczba kolumn siatki. */
    int pobierzSzerokoscSiatki() const;
    /** @return Liczba wierszy siatki. */
    int pobierzWysokoscSiatki() const;
    /** @return Rozmiar jednego pola [px]. */
    float pobierzRozmiarPola() const;

private:
    // Sprawdza, czy nastapila kolizja albo warunek wygranej.
    void sprawdzWarunkiKonca();
    // Konczy "oczekujaca" wygrana po dodatkowej klatce.
    void finalizujOczekujacaWygrana();
    // Rozpoczyna pomiar czasu gry.
    void uruchomZegar();
    // Zatrzymuje pomiar czasu gry.
    void zatrzymajZegar();

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

    // Znacznik chwili startu rozgrywki (logika zegara w klasie Gra).
    std::chrono::steady_clock::time_point startCzasu = std::chrono::steady_clock::now();
    // Znacznik chwili zatrzymania zegara.
    std::chrono::steady_clock::time_point czasZatrzymania = std::chrono::steady_clock::now();
    // Flaga: czy zegar jest juz zatrzymany.
    bool zegarZatrzymany = false;

    // Liczba kolumn planszy.
    int szerokoscSiatki = 16;
    // Liczba wierszy planszy.
    int wysokoscSiatki = 12;
    // Generator losowy uzywany w calej logice.
    std::mt19937 generator;
    // Rozmiar jednego pola planszy w pikselach.
    float rozmiarPola = 60.0f;
    // Flaga opozniajaca ekran wygranej o jedna klatke.
    bool czekaNaKlatkeMety = false;
};
