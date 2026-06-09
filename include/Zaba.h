/**
 * @file Zaba.h
 * @brief Klasa gracza (zaba) — pozycja i ruch po siatce planszy.
 */

#pragma once

/** @brief Reprezentuje gracza i obsluguje jego ruch po planszy. */
class Zaba {
public:
    /** @brief Ustawia pozycje startowa zaby. @param xStart Kolumna. @param yStart Wiersz. */
    void ustawPozycjeStartowa(int xStart, int yStart);

    /**
     * @brief Przesuwa zabe o podany krok.
     * @param dx Przesuniecie w poziomie (-1 lewo, 1 prawo).
     * @param dy Przesuniecie w pionie (1 gora, -1 dol).
     * @param krok Liczba pol (domyslnie 1).
     */
    void ruch(int dx, int dy, int krok = 1);

    /** @brief Ogranicza pozycje zaby do granic planszy. */
    void ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy);

    /** @return Aktualna wspolrzedna X (kolumna). */
    int pobierzX() const;
    /** @return Aktualna wspolrzedna Y (wiersz). */
    int pobierzY() const;

private:
    // Pole przechowuje wspolrzedna pozioma.
    int x = 0;
    // Pole przechowuje wspolrzedna pionowa.
    int y = 0;
};
