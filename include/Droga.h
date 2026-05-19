#pragma once

#include "PasRuchu.h"
#include "ScenariuszRuchu.h"
#include "UstawieniaTrudnosci.h"

#include <random>
#include <vector>

// Kontener wszystkich pasow ruchu; buduje droge wg poziomu trudnosci.
class Droga {
public:
    void skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                     float szerokoscPlanszy,
                     float wysokoscPlanszy,
                     float wysokoscPola,
                     const ScenariuszRuchu& scenariusz);

    void aktualizuj(float deltaSekundy, std::mt19937& generator);
    const std::vector<PasRuchu>& pobierzPasy() const;
    const std::vector<int>& pobierzWierszePasow() const;

private:
    bool czyJestWidoczneAutoNaDrodze() const;
    void utrzymujStaleNaDrodze(std::mt19937& generator);

    std::vector<PasRuchu> pasy;
    std::vector<int> wierszePasow;
};
