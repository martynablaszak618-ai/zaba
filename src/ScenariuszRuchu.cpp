#include "ScenariuszRuchu.h"

ScenariuszRuchu wylosujScenariusz(std::mt19937& generator, PoziomTrudnosci poziom) {
    std::uniform_int_distribution<int> wybor(0, 4);

    ScenariuszRuchu scenariusz;
    scenariusz.identyfikator = wybor(generator);

    switch (scenariusz.identyfikator) {
        case 0:
            scenariusz.nazwa = "Ruch umiarkowany";
            scenariusz.mnoznikPredkosci = 1.0f;
            scenariusz.mnoznikInterwalu = 1.0f;
            scenariusz.rozrzutStartuPiksele = 25.0f;
            scenariusz.maksOpoznienieFazy = 0.5f;
            break;
        case 1:
            scenariusz.nazwa = "Szybki ruch";
            scenariusz.mnoznikPredkosci = 1.22f;
            scenariusz.mnoznikInterwalu = 1.08f;
            scenariusz.minGestosc = 0.95f;
            scenariusz.maxGestosc = 1.45f;
            scenariusz.rozrzutStartuPiksele = 40.0f;
            scenariusz.maksOpoznienieFazy = 0.35f;
            break;
        case 2:
            scenariusz.nazwa = "Gęsty ruch";
            scenariusz.mnoznikPredkosci = 0.92f;
            scenariusz.mnoznikInterwalu = 0.82f;
            scenariusz.minGestosc = 0.55f;
            scenariusz.maxGestosc = 1.55f;
            scenariusz.rozrzutStartuPiksele = 70.0f;
            scenariusz.maksOpoznienieFazy = 0.9f;
            break;
        case 3:
            scenariusz.nazwa = "Rozproszone auta";
            scenariusz.mnoznikPredkosci = 1.05f;
            scenariusz.mnoznikInterwalu = 1.18f;
            scenariusz.minGestosc = 0.70f;
            scenariusz.maxGestosc = 1.20f;
            scenariusz.rozrzutStartuPiksele = 110.0f;
            scenariusz.maksOpoznienieFazy = 1.2f;
            break;
        default:
            scenariusz.nazwa = "Ruch zmienny";
            scenariusz.mnoznikPredkosci = 1.12f;
            scenariusz.mnoznikInterwalu = 0.95f;
            scenariusz.minGestosc = 0.45f;
            scenariusz.maxGestosc = 1.65f;
            scenariusz.rozrzutStartuPiksele = 55.0f;
            scenariusz.maksOpoznienieFazy = 1.4f;
            break;
    }

    if (poziom == PoziomTrudnosci::TRUDNY) {
        scenariusz.mnoznikPredkosci *= 1.05f;
        scenariusz.mnoznikInterwalu *= 0.94f;
    } else if (poziom == PoziomTrudnosci::LATWY) {
        scenariusz.mnoznikPredkosci *= 0.94f;
        scenariusz.mnoznikInterwalu *= 1.06f;
    }

    return scenariusz;
}
