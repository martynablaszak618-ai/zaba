// Dolaczamy deklaracje klasy Droga.
#include "Droga.h"

// Buduje cala droge (zestaw pasow) na bazie ustawien poziomu.
void Droga::skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                        float szerokoscPlanszy,
                        float wysokoscPlanszy,
                        float wysokoscPola) {
    // Usuwamy ewentualne stare pasy (np. po poprzedniej grze).
    pasy.clear();
    // Kopiujemy liste wierszy drogowych.
    wierszePasow = ustawienia.wierszePasow;
    // Rezerwujemy pamiec, aby uniknac wielu realokacji.
    pasy.reserve(wierszePasow.size());

    // Obliczamy, ile lacznie jest wierszy na planszy.
    const int liczbaWierszy = static_cast<int>(wysokoscPlanszy / wysokoscPola);
    // Przechodzimy po kazdym wierszu drogowym i tworzymy osobny pas.
    for (size_t i = 0; i < wierszePasow.size(); ++i) {
        // W logice Y rosnie do gory, a na ekranie Y rosnie w dol - tu robimy konwersje.
        const int wierszLogiki = wierszePasow[i];
        // Przeliczamy numer wiersza logiki na numer wiersza na ekranie.
        const float wierszEkranu = static_cast<float>((liczbaWierszy - 1) - wierszLogiki);
        // Wyznaczamy pionowy srodek pasa w pikselach.
        const float yPasa = (wierszEkranu + 0.5f) * wysokoscPola;
        // Naprzemiennie ustawiamy kierunek ruchu: prawo, lewo, prawo, lewo...
        const Kierunek kierunek = (i % 2 == 0) ? Kierunek::PRAWO : Kierunek::LEWO;
        // Delikatnie roznicujemy predkosc pasow, zeby ruch byl mniej jednorodny.
        const float predkoscPasowa =
            ustawienia.predkoscSamochodow + 8.0f * static_cast<float>(i % 3);
        // Tworzymy i dodajemy pas do listy pasow drogi.
        pasy.emplace_back(yPasa, kierunek, predkoscPasowa, ustawienia.interwalTworzeniaAuta,
                          szerokoscPlanszy, ustawienia.minimalnyOdstepAut, ustawienia.autaNaStarcieMin,
                          ustawienia.autaNaStarcieMax, ustawienia.maksAutNaPasie);
    }
}

// Aktualizuje wszystkie pasy drogi o jedna klatke symulacji.
void Droga::aktualizuj(float deltaSekundy, std::mt19937& generator) {
    // Aktualizujemy kazdy pas osobno (kazdy pas sam pilnuje widocznych aut).
    for (auto& pas : pasy) {
        pas.aktualizuj(deltaSekundy, generator);
    }
}

// Getter: zwraca wszystkie pasy drogi.
const std::vector<PasRuchu>& Droga::pobierzPasy() const {
    return pasy;
}

// Getter: zwraca liste numerow wierszy pasow.
const std::vector<int>& Droga::pobierzWierszePasow() const {
    return wierszePasow;
}
