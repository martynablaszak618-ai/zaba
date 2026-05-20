// Dolaczamy deklaracje klasy PasRuchu.
#include "PasRuchu.h"

// Dolaczamy funkcje pomocnicze (np. std::max, std::clamp).
#include <algorithm>
// Dolaczamy funkcje matematyczne (np. std::abs).
#include <cmath>

// Konstruktor ustawia wszystkie parametry jednego pasa.
PasRuchu::PasRuchu(float yPasa,
                   Kierunek kierunek,
                   float predkoscAut,
                   float interwalTworzeniaAut,
                   float szerokoscPlanszyPiksele,
                   float minimalnyOdstepAut,
                   int autaNaStarcieMinParam,
                   int autaNaStarcieMaxParam,
                   int maksAutNaPasieParam,
                   const ScenariuszRuchu& scenariusz)
    : y(yPasa),
      kierunekRuchu(kierunek),
      predkoscSamochodow(predkoscAut * scenariusz.mnoznikPredkosci),
      interwalSpawnu(interwalTworzeniaAut * scenariusz.mnoznikInterwalu),
      szerokoscPlanszy(szerokoscPlanszyPiksele),
      licznikDoSpawnu(interwalTworzeniaAut * scenariusz.mnoznikInterwalu),
      minimalnyOdstep(minimalnyOdstepAut),
      autaStartMin(autaNaStarcieMinParam),
      autaStartMax(autaNaStarcieMaxParam),
      maksAutNaPasie(std::max(2, maksAutNaPasieParam)),
      scenariuszRuchu(scenariusz) {}

// Aktualizuje ruch i spawn aut na pasie.
void PasRuchu::aktualizuj(float deltaSekundy, std::mt19937& generator) {
    // Przy pierwszym wywolaniu przygotowujemy faze startowa.
    if (!czyRuchStartowyZrobiony) {
        std::uniform_real_distribution<float> losFaza(0.0f, scenariuszRuchu.maksOpoznienieFazy);
        licznikDoSpawnu = interwalSpawnu * losFaza(generator);
        dodajRuchPoczatkowy(generator);
        czyRuchStartowyZrobiony = true;
    }

    // Przesuwamy wszystkie auta na pasie.
    for (auto& autoNaPasie : samochody) {
        autoNaPasie.aktualizuj(deltaSekundy, wspolczynnikGestosciRuchu);
    }
    // Korygujemy pozycje aut po zapetleniu i pilnujemy widocznosci ruchu.
    normalizujPozycjeAut();
    utrzymijWidocznyRuch(generator);

    // Co pewien czas losowo zmieniamy gestosc ruchu.
    czasDoZmianyGestosci -= deltaSekundy;
    if (czasDoZmianyGestosci <= 0.0f) {
        std::uniform_real_distribution<float> losGestosc(scenariuszRuchu.minGestosc,
                                                           scenariuszRuchu.maxGestosc);
        std::uniform_real_distribution<float> losCzas(0.9f, 1.8f);
        wspolczynnikGestosciRuchu = losGestosc(generator);
        czasDoZmianyGestosci = losCzas(generator);
    }

    // Odliczamy czas do nastepnego spawnu.
    licznikDoSpawnu -= deltaSekundy;
    if (licznikDoSpawnu <= 0.0f) {
        // Dodajemy auto tylko wtedy, gdy nie naruszy to minimalnych odstepow.
        if (czyMoznaDodacAuto()) {
            dodajSamochod();
        }
        // Ustawiamy kolejny spawn z lekka losowoscia opoznienia.
        licznikDoSpawnu =
            (interwalSpawnu * wspolczynnikGestosciRuchu) + losujDodatkoweOpoznienie(generator);
    }
}

const std::vector<Samochod>& PasRuchu::pobierzSamochody() const {
    return samochody;
}

// Ogranicza pozycje X, aby auta startowe nie byly zbyt blisko krawedzi.
float PasRuchu::ograniczXNaPasie(float x) const {
    const float margines = 28.0f;
    return std::clamp(x, margines, szerokoscPlanszy - margines);
}

// Dodaje jedno auto na punkt spawnu (zalezny od kierunku pasa).
void PasRuchu::dodajSamochod() {
    const float xStart =
        (kierunekRuchu == Kierunek::PRAWO) ? -28.0f : (szerokoscPlanszy + 28.0f);
    const int wariantKoloru = static_cast<int>(samochody.size() % 3);
    samochody.emplace_back(xStart, y, predkoscSamochodow, kierunekRuchu, szerokoscPlanszy,
                           wariantKoloru);
}

// Sprawdza, czy dwa auta sa od siebie wystarczajaco daleko.
bool PasRuchu::czyOdlegloscWystarczajaca(float x1, float x2) const {
    const float minOdleglosc = minimalnyOdstep * 0.72f;
    return std::abs(x1 - x2) >= minOdleglosc;
}

// Losuje pozycje startowa, ktora nie jest zbyt blisko innych aut.
bool PasRuchu::losujWolneMiejsceNaPasie(std::mt19937& generator, float& xOut) const {
    const float minX = szerokoscPlanszy * 0.12f;
    const float maxX = szerokoscPlanszy * 0.88f;
    std::uniform_real_distribution<float> los(minX, maxX);

    for (int proba = 0; proba < 24; ++proba) {
        const float kandydat = los(generator);
        bool wolne = true;
        for (const auto& autoNaPasie : samochody) {
            if (!czyOdlegloscWystarczajaca(znormalizujX(autoNaPasie.pobierzX()), kandydat)) {
                wolne = false;
                break;
            }
        }
        if (wolne) {
            xOut = kandydat;
            return true;
        }
    }
    return false;
}

// Tworzy poczatkowy zestaw aut widocznych na pasie.
void PasRuchu::dodajRuchPoczatkowy(std::mt19937& generator) {
    std::uniform_int_distribution<int> liczbaAut(autaStartMin, autaStartMax);
    const int ileAut = liczbaAut(generator);

    for (int i = 0; i < ileAut; ++i) {
        float xStart = 0.0f;
        if (!losujWolneMiejsceNaPasie(generator, xStart)) {
            std::uniform_real_distribution<float> losAwaryjny(szerokoscPlanszy * 0.15f,
                                                              szerokoscPlanszy * 0.85f);
            xStart = losAwaryjny(generator);
        }
        xStart = ograniczXNaPasie(xStart);
        samochody.emplace_back(xStart, y, predkoscSamochodow, kierunekRuchu, szerokoscPlanszy,
                               i % 3);
    }

    // Dodatkowe zabezpieczenie: gdyby po losowaniu nic nie bylo widoczne.
    if (!czyPasMaWidoczneAuto() && czyMoznaDodacAuto()) {
        dodajSamochod();
    }
}

// Sprawdza, czy nowy spawn nie spowoduje "zlepienia" aut.
bool PasRuchu::czyMoznaDodacAuto() const {
    if (samochody.size() >= static_cast<size_t>(maksAutNaPasie)) {
        return false;
    }

    const float xSpawn = (kierunekRuchu == Kierunek::PRAWO) ? 0.0f : szerokoscPlanszy;
    for (const auto& autoNaPasie : samochody) {
        const float x = znormalizujX(autoNaPasie.pobierzX());
        float odleglosc = std::abs(x - xSpawn);
        if (odleglosc > (szerokoscPlanszy * 0.5f)) {
            odleglosc = szerokoscPlanszy - odleglosc;
        }
        if (odleglosc < minimalnyOdstep) {
            return false;
        }
    }
    return true;
}

// Zwraca drobne dodatkowe opoznienie do interwalu spawnu.
float PasRuchu::losujDodatkoweOpoznienie(std::mt19937& generator) const {
    std::uniform_real_distribution<float> los(0.04f, 0.35f);
    return los(generator);
}

// Sprowadza pozycje X do zapetlonego zakresu pasa.
float PasRuchu::znormalizujX(float x) const {
    const float margines = 36.0f;
    const float okres = szerokoscPlanszy + (2.0f * margines);
    while (x > szerokoscPlanszy + margines) {
        x -= okres;
    }
    while (x < -margines) {
        x += okres;
    }
    return x;
}

// Koryguje wszystkie auta, ktore wyszly za daleko poza zakres logiczny.
void PasRuchu::normalizujPozycjeAut() {
    const float margines = 36.0f;
    for (auto& autoNaPasie : samochody) {
        const float x = autoNaPasie.pobierzX();
        if (x > szerokoscPlanszy + margines || x < -margines) {
            autoNaPasie.ustawX(znormalizujX(x));
        }
    }
}

// Sprawdza, czy na pasie jest co najmniej jedno auto na widocznym obszarze.
bool PasRuchu::czyPasMaWidoczneAuto() const {
    for (const auto& autoNaPasie : samochody) {
        const float x = znormalizujX(autoNaPasie.pobierzX());
        if (x >= 0.0f && x <= szerokoscPlanszy) {
            return true;
        }
    }
    return false;
}

// Wymusza widoczny ruch na pasie, jesli chwilowo znikna wszystkie auta.
void PasRuchu::utrzymijWidocznyRuch(std::mt19937& generator) {
    if (czyPasMaWidoczneAuto()) {
        return;
    }

    if (czyMoznaDodacAuto()) {
        dodajSamochod();
    }
}
