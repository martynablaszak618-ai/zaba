#include "WykrywaczKolizji.h"

#include "UstawieniaTrudnosci.h"

#include <cmath>

bool WykrywaczKolizji::czyJestKolizja(const Zaba& zaba,
                                      const Droga& droga,
                                      float rozmiarPola,
                                      int szerokoscSiatki,
                                      int wysokoscSiatki,
                                      const UstawieniaTrudnosci& ustawienia) const {
    (void)szerokoscSiatki;
    (void)wysokoscSiatki;

    const int wierszZaby = zaba.pobierzPozycje().pobierzY();
    if (!czyWierszJestPasem(wierszZaby, ustawienia)) {
        return false;
    }

    const float srodekZabyX =
        (static_cast<float>(zaba.pobierzPozycje().pobierzX()) + 0.5f) * rozmiarPola;
    const float polowaSzerokosciZaby = rozmiarPola * 0.16f;
    const float polowaSzerokosciAuta = rozmiarPola * 0.34f;
    const float minimalnyZachod = polowaSzerokosciZaby + polowaSzerokosciAuta;

    const std::vector<PasRuchu>& pasy = droga.pobierzPasy();
    const std::vector<int>& wierszePasow = droga.pobierzWierszePasow();

    for (size_t indeksPasa = 0; indeksPasa < pasy.size(); ++indeksPasa) {
        if (wierszePasow[indeksPasa] != wierszZaby) {
            continue;
        }

        for (const auto& autoNaPasie : pasy[indeksPasa].pobierzSamochody()) {
            if (std::abs(srodekZabyX - autoNaPasie.pobierzX()) < minimalnyZachod) {
                return true;
            }
        }
    }

    return false;
}
