#pragma once

#include "Typy.h"

#include <random>
#include <string>

// Parametry jednego wariantu ruchu aut (losowany na start rozgrywki).
struct ScenariuszRuchu {
    int identyfikator = 0;
    std::string nazwa;
    float mnoznikPredkosci = 1.0f;
    float mnoznikInterwalu = 1.0f;
    float minGestosc = 0.75f;
    float maxGestosc = 1.35f;
    float rozrzutStartuPiksele = 0.0f;
    float maksOpoznienieFazy = 0.0f;
};

ScenariuszRuchu wylosujScenariusz(std::mt19937& generator, PoziomTrudnosci poziom);
