// Dolaczamy deklaracje klasy wykrywacza kolizji.
#include "WykrywaczKolizji.h"

// Dolaczamy narzedzia dotyczace ustawien planszy i pasow.
#include "UstawieniaTrudnosci.h"

// Dolaczamy funkcje matematyczne (tu: abs).
#include <cmath>

// Sprawdza, czy zaba zderzyla sie z jakimkolwiek autem.
bool WykrywaczKolizji::czyJestKolizja(const Zaba& zaba,
                                      const Droga& droga,
                                      float rozmiarPola,
                                      int szerokoscSiatki,
                                      int wysokoscSiatki,
                                      const UstawieniaTrudnosci& ustawienia) const {
    // Te dwa parametry sa obecnie nieuzywane, ale zostaly dla czytelnosci interfejsu.
    (void)szerokoscSiatki;
    (void)wysokoscSiatki;

    // Pobieramy wiersz, na ktorym stoi zaba.
    const int wierszZaby = zaba.pobierzY();
    // Jesli zaba nie stoi na drodze, to nie moze byc kolizji z autem.
    if (!czyWierszJestPasem(wierszZaby, ustawienia)) {
        return false;
    }

    // Obliczamy srodek zaby w pikselach w osi X.
    const float srodekZabyX =
        (static_cast<float>(zaba.pobierzX()) + 0.5f) * rozmiarPola;
    // Ustalony "polpromien" zaby do prostego testu nakladania.
    const float polowaSzerokosciZaby = rozmiarPola * 0.16f;
    // Ustalony "polpromien" auta do prostego testu nakladania.
    const float polowaSzerokosciAuta = rozmiarPola * 0.34f;
    // Minimalny dystans srodkow, przy ktorym obiekty zaczynaja na siebie nachodzic.
    const float minimalnyZachod = polowaSzerokosciZaby + polowaSzerokosciAuta;

    // Pobieramy wszystkie pasy drogi.
    const std::vector<PasRuchu>& pasy = droga.pobierzPasy();
    // Pobieramy liste numerow wierszy dla tych pasow.
    const std::vector<int>& wierszePasow = droga.pobierzWierszePasow();

    // Sprawdzamy kazdy pas.
    for (size_t indeksPasa = 0; indeksPasa < pasy.size(); ++indeksPasa) {
        // Interesuje nas tylko pas, ktory ma ten sam wiersz co zaba.
        if (wierszePasow[indeksPasa] != wierszZaby) {
            continue;
        }

        // Sprawdzamy kazde auto na tym pasie.
        for (const auto& autoNaPasie : pasy[indeksPasa].pobierzSamochody()) {
            // Gdy odleglosc miedzy srodkami jest mniejsza niz prog, uznajemy kolizje.
            if (std::abs(srodekZabyX - autoNaPasie.pobierzX()) < minimalnyZachod) {
                return true;
            }
        }
    }

    // Nie znaleziono zadnego zderzenia.
    return false;
}
