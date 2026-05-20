// Ta dyrektywa zabezpiecza przed wielokrotnym dolaczaniem pliku.
#pragma once

// Potrzebujemy enumu PoziomTrudnosci, dlatego dolaczamy wspolne typy.
#include "Typy.h"

// Biblioteka do losowania parametrow.
#include <random>
// Biblioteka do przechowywania tekstu (nazwy scenariusza).
#include <string>

// Struktura opisuje jeden wariant "zachowania ruchu" samochodow.
struct ScenariuszRuchu {
    // Unikalny numer scenariusza.
    int identyfikator = 0;
    // Nazwa wyswietlana na pasku statusu.
    std::string nazwa;
    // Mnoznik predkosci aut (1.0 = bez zmian).
    float mnoznikPredkosci = 1.0f;
    // Mnoznik interwalu spawnu (1.0 = bez zmian).
    float mnoznikInterwalu = 1.0f;
    // Minimalna wartosc chwilowej gestosci ruchu.
    float minGestosc = 0.75f;
    // Maksymalna wartosc chwilowej gestosci ruchu.
    float maxGestosc = 1.35f;
    // Jak bardzo rozstrzelone moga byc pozycje startowe aut.
    float rozrzutStartuPiksele = 0.0f;
    // Maksymalne opoznienie fazy ruchu na starcie pasa.
    float maksOpoznienieFazy = 0.0f;
};

// Funkcja losuje scenariusz ruchu na podstawie generatora i trudnosci.
ScenariuszRuchu wylosujScenariusz(std::mt19937& generator, PoziomTrudnosci poziom);
