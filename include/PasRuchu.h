// Ta dyrektywa chroni przed wielokrotnym dolaczeniem pliku.
#pragma once

// Dolaczamy definicje klasy Samochod.
#include "Samochod.h"

// Biblioteka do losowania.
#include <random>
// Biblioteka do dynamicznej listy samochodow.
#include <vector>

// Klasa opisuje jeden pas ruchu i zarzadza autami na tym pasie.
class PasRuchu {
public:
    // Konstruktor tworzy pas z pelna konfiguracja ruchu (parametry z poziomu trudnosci).
    PasRuchu(float yPasa,
             Kierunek kierunek,
             float predkoscAut,
             float interwalTworzeniaAut,
             float szerokoscPlanszyPiksele,
             float minimalnyOdstepAut,
             int autaNaStarcieMin,
             int autaNaStarcieMax,
             int maksAutNaPasie);

    // Aktualizuje caly pas: ruch, gestosc, spawn, porzadkowanie pozycji.
    void aktualizuj(float deltaSekundy, std::mt19937& generator);
    // Zwraca liste aut na pasie (tylko do odczytu).
    const std::vector<Samochod>& pobierzSamochody() const;
    // Sprawdza, czy co najmniej jedno auto jest widoczne na ekranie.
    bool czyPasMaWidoczneAuto() const;
    // W razie pustki doklada auto, aby ruch byl ciagly.
    void utrzymijWidocznyRuch(std::mt19937& generator);

private:
    // Dodaje nowe auto na poczatku pasa.
    void dodajSamochod();
    // Dodaje pakiet aut startowych przy pierwszej aktualizacji.
    void dodajRuchPoczatkowy(std::mt19937& generator);
    // Sprawdza, czy mozna bezpiecznie dodac kolejne auto.
    bool czyMoznaDodacAuto() const;
    // Losuje pozycje startowa, ktora nie koliduje z innymi autami.
    bool losujWolneMiejsceNaPasie(std::mt19937& generator, float& xOut) const;
    // Losuje drobne opoznienie miedzy kolejnymi spawnami.
    float losujDodatkoweOpoznienie(std::mt19937& generator) const;
    // Przelicza X do zakresu "zapetlonego" pasa.
    float znormalizujX(float x) const;
    // Naprawia pozycje aut, gdy wyjada poza zakres logiczny.
    void normalizujPozycjeAut();
    // Ogranicza X do sensownego zakresu pasa.
    float ograniczXNaPasie(float x) const;
    // Sprawdza, czy dystans miedzy dwoma autami jest wystarczajacy.
    bool czyOdlegloscWystarczajaca(float x1, float x2) const;

    // Stala pionowa pozycja pasa na ekranie.
    float y = 0.0f;
    // Kierunek ruchu aut na tym pasie.
    Kierunek kierunekRuchu = Kierunek::PRAWO;
    // Predkosc bazowa aut na pasie.
    float predkoscSamochodow = 100.0f;
    // Docelowy interwal miedzy spawnami.
    float interwalSpawnu = 1.0f;
    // Szerokosc calej planszy (do obliczen zapetlenia).
    float szerokoscPlanszy = 800.0f;
    // Aktualny licznik czasu do nastepnego spawnu.
    float licznikDoSpawnu = 0.0f;
    // Minimalny dystans miedzy autami.
    float minimalnyOdstep = 150.0f;
    // Minimalna liczba aut tworzonych na starcie.
    int autaStartMin = 1;
    // Maksymalna liczba aut tworzonych na starcie.
    int autaStartMax = 2;
    // Limit aut na pasie.
    int maksAutNaPasie = 3;
    // Flaga: czy etap startowego ruchu zostal juz wykonany.
    bool czyRuchStartowyZrobiony = false;
    // Chwilowy mnoznik tempa ruchu (dynamiczna gestosc).
    float wspolczynnikGestosciRuchu = 1.0f;
    // Ile czasu zostalo do kolejnej zmiany gestosci.
    float czasDoZmianyGestosci = 1.4f;
    // Lista wszystkich aut znajdujacych sie na pasie.
    std::vector<Samochod> samochody;
};
