// Ta dyrektywa zapobiega wielokrotnemu dolaczeniu tego samego pliku naglowkowego.
#pragma once

// Dolaczamy wspolne typy (np. enum Kierunek), z ktorych korzysta klasa Samochod.
#include "Typy.h"

// Definicja klasy opisujacej jeden samochod poruszajacy sie po planszy.
class Samochod {
public:
    // Konstruktor: tworzy nowy obiekt samochodu z podanymi parametrami startowymi.
    Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
             int wariantKoloru);

    // Metoda przesuwa samochod w czasie gry (na podstawie czasu i tempa rozgrywki).
    void aktualizuj(float deltaSekundy, float mnoznikTempa);

    // Zwraca aktualna pozycje pozioma samochodu (os X).
    float pobierzX() const;
    // Zwraca aktualna pozycje pionowa samochodu (os Y).
    float pobierzY() const;
    // Zwraca numer wariantu koloru, aby interfejs wiedzial jak narysowac auto.
    int pobierzWariantKoloru() const;
    // Ustawia nowa pozycje pozioma samochodu (zmienia wspolrzedna X).
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
