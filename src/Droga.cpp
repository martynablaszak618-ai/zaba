#include "Droga.h"

#include <random>

void Droga::skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                        float szerokoscPlanszy,
                        float wysokoscPlanszy,
                        float wysokoscPola,
                        const ScenariuszRuchu& scenariusz) {
    pasy.clear();
    wierszePasow = ustawienia.wierszePasow;
    pasy.reserve(wierszePasow.size());

    const int liczbaWierszy = static_cast<int>(wysokoscPlanszy / wysokoscPola);
    for (size_t i = 0; i < wierszePasow.size(); ++i) {
        // Logika gry ma os Y rosnaca do gory, a ekran GUI do dolu - tutaj robimy mapowanie.
        const int wierszLogiki = wierszePasow[i];
        const float wierszEkranu =
            static_cast<float>((liczbaWierszy - 1) - wierszLogiki);
        const float yPasa = (wierszEkranu + 0.5f) * wysokoscPola;
        const Kierunek kierunek = (i % 2 == 0) ? Kierunek::PRAWO : Kierunek::LEWO;
        const float predkoscPasowa =
            ustawienia.predkoscSamochodow + 8.0f * static_cast<float>(i % 3);
        pasy.emplace_back(yPasa, kierunek, predkoscPasowa, ustawienia.interwalTworzeniaAuta,
                          szerokoscPlanszy, ustawienia.minimalnyOdstepAut, ustawienia.autaNaStarcieMin,
                          ustawienia.autaNaStarcieMax, ustawienia.maksAutNaPasie, scenariusz);
    }
}

void Droga::aktualizuj(float deltaSekundy, std::mt19937& generator) {
    for (auto& pas : pasy) {
        pas.aktualizuj(deltaSekundy, generator);
    }
    utrzymujStaleNaDrodze(generator);
}

bool Droga::czyJestWidoczneAutoNaDrodze() const {
    for (const auto& pas : pasy) {
        if (pas.czyPasMaWidoczneAuto()) {
            return true;
        }
    }
    return false;
}

void Droga::utrzymujStaleNaDrodze(std::mt19937& generator) {
    if (pasy.empty()) {
        return;
    }

    std::uniform_int_distribution<size_t> losPas(0, pasy.size() - 1);
    for (int proba = 0; proba < 4 && !czyJestWidoczneAutoNaDrodze(); ++proba) {
        pasy[losPas(generator)].utrzymijWidocznyRuch(generator);
    }
}

const std::vector<PasRuchu>& Droga::pobierzPasy() const {
    return pasy;
}

const std::vector<int>& Droga::pobierzWierszePasow() const {
    return wierszePasow;
}
