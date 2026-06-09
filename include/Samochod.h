/**
 * @file Samochod.h
 * @brief Pojedynczy samochod poruszajacy sie poziomo po pasie.
 */

#pragma once

// Dolaczamy wspolne typy (np. enum Kierunek), z ktorych korzysta klasa Samochod.
#include "Typy.h"

/** @brief Samochod poruszajacy sie po jednym pasie drogi. */
class Samochod {
public:
    /**
     * @brief Tworzy samochod z parametrami startowymi.
     * @param xStart Pozycja poczatkowa X w pikselach.
     * @param yStale Stala wysokosc pasa (Y).
     * @param predkosc Predkosc w pikselach na sekunde.
     * @param kierunek LEWO lub PRAWO.
     * @param szerokosc Szerokosc planszy do zapetlenia.
     * @param wariantKoloru Indeks koloru nadwozia (0-2).
     */
    Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
             int wariantKoloru);

    /**
     * @brief Aktualizuje pozycje auta o krok czasu.
     * @param deltaSekundy Czas od poprzedniej klatki [s].
     * @param mnoznikTempa Mnoznik gestosci ruchu (np. 0.75-1.35).
     */
    void aktualizuj(float deltaSekundy, float mnoznikTempa);

    /** @return Pozycja X w pikselach. */
    float pobierzX() const;
    /** @return Pozycja Y w pikselach. */
    float pobierzY() const;
    /** @return Wariant koloru do rysowania (0, 1 lub 2). */
    int pobierzWariantKoloru() const;
    /** @brief Ustawia nowa pozycje X (np. po normalizacji). */
    void ustawX(float nowyX);

private:
    // Aktualna pozycja pozioma samochodu na planszy.
    float x = 0.0f;
    // Aktualna pozycja pionowa samochodu na planszy.
    float y = 0.0f;
    // Szybkosc jazdy samochodu wyrazona w pikselach na sekunde.
    float predkoscPikseleNaSek = 100.0f;
    // Kierunek, w ktorym porusza sie samochod (np. lewo albo prawo).
    Kierunek kierunekRuchu = Kierunek::PRAWO;
    // Szerokosc calej planszy w pikselach (potrzebna np. do zawijania pozycji).
    float szerokoscPlanszyPiksele = 800.0f;
    // Numer wariantu koloru samochodu (np. inny kolor dla roznych aut).
    int wariantKoloru = 0;
};
