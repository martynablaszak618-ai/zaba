#pragma once

#include "Samochod.h"
#include "ScenariuszRuchu.h"

#include <random>
#include <vector>

// Jeden poziomy pas ruchu: trzyma samochody i zarzadza ich dodawaniem.
class PasRuchu {
public:
    PasRuchu(float yPasa,
             Kierunek kierunek,
             float predkoscAut,
             float interwalTworzeniaAut,
             float szerokoscPlanszyPiksele,
             float minimalnyOdstepAut,
             int autaNaStarcieMin,
             int autaNaStarcieMax,
             int maksAutNaPasie,
             const ScenariuszRuchu& scenariusz);

    void aktualizuj(float deltaSekundy, std::mt19937& generator);
    const std::vector<Samochod>& pobierzSamochody() const;
    bool czyPasMaWidoczneAuto() const;
    void utrzymijWidocznyRuch(std::mt19937& generator);

private:
    void dodajSamochod();
    void dodajRuchPoczatkowy(std::mt19937& generator);
    bool czyMoznaDodacAuto() const;
    bool losujWolneMiejsceNaPasie(std::mt19937& generator, float& xOut) const;
    float losujDodatkoweOpoznienie(std::mt19937& generator) const;
    float znormalizujX(float x) const;
    void normalizujPozycjeAut();
    float ograniczXNaPasie(float x) const;
    bool czyOdlegloscWystarczajaca(float x1, float x2) const;

    float y = 0.0f;
    Kierunek kierunekRuchu = Kierunek::PRAWO;
    float predkoscSamochodow = 100.0f;
    float interwalSpawnu = 1.0f;
    float szerokoscPlanszy = 800.0f;
    float licznikDoSpawnu = 0.0f;
    float minimalnyOdstep = 150.0f;
    int autaStartMin = 1;
    int autaStartMax = 2;
    int maksAutNaPasie = 3;
    bool czyRuchStartowyZrobiony = false;
    float wspolczynnikGestosciRuchu = 1.0f;
    float czasDoZmianyGestosci = 1.4f;
    ScenariuszRuchu scenariuszRuchu{};
    std::vector<Samochod> samochody;
};
