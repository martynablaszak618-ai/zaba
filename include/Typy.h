/**
 * @file Typy.h
 * @brief Wspolne typy wyliczeniowe gry (stan, trudnosc, kierunek).
 */

#pragma once

/** @brief Stan aplikacji / ekranu gry. */
enum class StanGry {
    MENU,       // Gracz widzi menu glowne i wybiera poziom.
    W_TRAKCIE,  // Trwa aktywna rozgrywka.
    WYGRANA,    // Gra zakonczona sukcesem.
    PRZEGRANA   // Gra zakonczona porazka (np. kolizja).
};

/** @brief Poziom trudnosci wybrany przez gracza. */
enum class PoziomTrudnosci {
    LATWY,   // Najlatwiejsza konfiguracja.
    SREDNI,  // Srednia konfiguracja.
    TRUDNY   // Najtrudniejsza konfiguracja.
};

/** @brief Kierunek ruchu samochodu na pasie. */
enum class Kierunek {
    LEWO,   // Ruch samochodu w lewo.
    PRAWO   // Ruch samochodu w prawo.
};
