# Przewodnik po plikach .cpp — gra „Żaba na ulicy”

**Ostatnia aktualizacja:** czerwiec 2025

Ten dokument wyjaśnia **każdą linijkę** w plikach źródłowych (`.cpp`) w najprostszy możliwy sposób.

**Różnica między `.h` a `.cpp`:**
- Plik **`.h`** = „co ta część programu potrafi” (deklaracja + komentarze Doxygen)
- Plik **`.cpp`** = „jak to dokładnie działa” (prawdziwy kod, który się wykonuje)

**Powiązane dokumenty:**

| Plik | Zawartość |
|---|---|
| `PRZEWODNIK_PLIKI_H.md` | Przewodnik po nagłówkach (zaktualizowany pod Doxygen) |
| `DOKUMENTACJA_OPISOWA.md` | Dokumentacja do oddania projektu |
| `SPRAWDZENIE_WYMAGAN.md` | Checklist zgodności z wymaganiami PDF |
| `Doxyfile` | Generowanie HTML: `doxygen Doxyfile` |

**Struktura projektu (pliki źródłowe i testy):**
```
include/     — nagłówki .h (z komentarzami Doxygen)
src/         — implementacje .cpp + main.cpp
tests/       — TestyLogiki.cpp (logika bez GUI, CTest)
docs/        — dokumentacja (ten plik i pozostałe)
Doxyfile     — konfiguracja Doxygen
```

---

## Kolejność czytania (od najprostszych do najtrudniejszych)

1. `main.cpp` — start programu  
2. `Zaba.cpp` — ruch gracza  
3. `Samochod.cpp` — ruch jednego auta  
4. `UstawieniaTrudnosci.cpp` — liczby poziomów  
5. `Droga.cpp` — budowa wszystkich pasów  
6. `WykrywaczKolizji.cpp` — sprawdzanie zderzeń  
7. `PasRuchu.cpp` — auta na jednym pasie  
8. `Gra.cpp` — cała logika gry  
9. `InterfejsGraficzny.cpp` — okno, rysowanie, klawiatura, mysz  
10. `TestyLogiki.cpp` — automatyczne testy (bez GUI)

---

# 1. `src/main.cpp` — punkt startowy programu

To **najkrótszy plik**. Uruchamia aplikację Qt i pokazuje okno gry. Nic tu nie ma o żabie, autach ani kolizjach — tylko „włącz program”.

---

### Linia 1
```cpp
// Dolaczamy klase glownego okna aplikacji.
```
Komentarz: za chwilę wczytamy plik z oknem gry.

### Linia 2
```cpp
#include "InterfejsGraficzny.h"
```
**„Weź plik z oknem gry.”** Dzięki temu program wie, że istnieje klasa `InterfejsGraficzny` (główne okno).

### Linia 4–5
```cpp
// Dolaczamy klase QApplication (wymagana w kazdej aplikacji Qt).
#include <QApplication>
```
**Qt** to biblioteka do okien. `QApplication` to obowiązkowy „silnik” każdej aplikacji Qt — bez niego okno nie zadziała.

### Linia 7
```cpp
// Punkt startowy programu.
```
Komentarz: funkcja `main` to miejsce, od którego zaczyna się **każdy** program w C++.

### Linia 8
```cpp
int main(int argc, char* argv[]) {
```
**`main`** — pierwsza funkcja, która się wykonuje po uruchomieniu gry.  
- `argc`, `argv` — argumenty z linii poleceń (np. gdybyś uruchamiała grę z terminala). W tej grze ich nie używamy, ale muszą być w sygnaturze.

### Linia 9–10
```cpp
    // Tworzymy obiekt aplikacji Qt i przekazujemy argumenty z linii polecen.
    QApplication aplikacja(argc, argv);
```
Tworzymy **obiekt aplikacji Qt**. To jak „włącznik całego systemu okienkowego”.

### Linia 11–12
```cpp
    // Tworzymy glowne okno gry.
    InterfejsGraficzny okno;
```
Tworzymy **główne okno** gry. W konstruktorze (`InterfejsGraficzny.cpp`) ustawiane są rozmiar, timer, przyciski itd.

### Linia 13–14
```cpp
    // Pokazujemy okno uzytkownikowi.
    okno.show();
```
**Pokazujemy okno** na ekranie. Bez `show()` okno istniałoby, ale byłoby niewidoczne.

### Linia 15–16
```cpp
    // Uruchamiamy petle zdarzen Qt (program dziala dopoki okno nie zostanie zamkniete).
    return aplikacja.exec();
```
**`exec()`** — uruchamia „pętlę zdarzeń”: program czeka na kliknięcia, klawisze, odświeżanie ekranu. Działa, dopóki nie zamkniesz okna.  
`return` zwraca kod wyjścia do systemu operacyjnego.

### Linia 17
```cpp
}
```
Koniec funkcji `main`.

---

**Podsumowanie `main.cpp`:**  
`main` → stwórz Qt → stwórz okno → pokaż okno → czekaj na zdarzenia użytkownika.

**Gdzie dalej?** Cała reszta dzieje się w `InterfejsGraficzny` i `Gra`.

---

# 2. `src/Zaba.cpp` — ruch żaby (gracza)

Implementacja klasy `Zaba` z `Zaba.h`. Żaba ma tylko pozycję `(x, y)` i proste operacje na niej.

---

### Linie 1–5
```cpp
#include "Zaba.h"
#include <algorithm>
```
- `Zaba.h` — deklaracja klasy  
- `<algorithm>` — biblioteka z funkcją `std::clamp` (ograniczanie liczby do zakresu)

### Linie 7–12 — `ustawPozycjeStartowa`
```cpp
void Zaba::ustawPozycjeStartowa(int xStart, int yStart) {
    x = xStart;
    y = yStart;
}
```
**Co robi:** ustawia żabę na podane współrzędne.  
**Kiedy:** przy starcie gry — `Gra.cpp` linia 26 ustawia żabę na środku dolnego wiersza `(szerokoscSiatki/2, 0)`.

| Parametr | Znaczenie |
|---|---|
| `xStart` | kolumna (0 = lewa krawędź) |
| `yStart` | wiersz (0 = dół planszy w logice gry) |

### Linie 14–19 — `ruch`
```cpp
void Zaba::ruch(int dx, int dy, int krok) {
    x += dx * krok;
    y += dy * krok;
}
```
**Co robi:** przesuwa żabę o `krok` pól w kierunku `(dx, dy)`.

| Sterowanie | dx | dy | Efekt |
|---|---|---|---|
| W (góra) | 0 | 1 | y rośnie → żaba idzie w górę planszy |
| S (dół) | 0 | -1 | y maleje |
| A (lewo) | -1 | 0 | x maleje |
| D (prawo) | 1 | 0 | x rośnie |

**Kto woła:** `Gra::ruch` → `InterfejsGraficzny::keyPressEvent`

### Linie 21–27 — `ograniczDoPlanszy`
```cpp
void Zaba::ograniczDoPlanszy(int szerokoscPlanszy, int wysokoscPlanszy) {
    x = std::clamp(x, 0, szerokoscPlanszy - 1);
    y = std::clamp(y, 0, wysokoscPlanszy - 1);
}
```
**Co robi:** nie pozwala żabie wyjść poza planszę.  
`std::clamp(wartość, min, max)` — jeśli wartość za mała → min, za duża → max.

Przykład: plansza 16 kolumn (indeksy 0–15). Jeśli x = -1, zostanie 0. Jeśli x = 20, zostanie 15.

### Linie 29–33 — gettery
```cpp
int Zaba::pobierzX() const { return x; }
int Zaba::pobierzY() const { return y; }
```
Zwracają aktualną pozycję. Używane przy rysowaniu, kolizjach i sprawdzaniu mety.

---

# 3. `src/Samochod.cpp` — jedno auto

Jeden samochód porusza się **poziomo** (Y się nie zmienia). Gdy wyjedzie poza ekran, „wraca” z drugiej strony (jak w Froggerze).

---

### Linie 1–2
```cpp
#include "Samochod.h"
```

### Linie 4–12 — konstruktor
```cpp
Samochod::Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
                   int wariantKoloruParam)
    : x(xStart),
      y(yStale),
      ...
      wariantKoloru(wariantKoloruParam % 3) {}
```
**Lista inicjalizacyjna** (`: x(...), y(...)`) — od razu ustawia pola obiektu.

| Parametr | Znaczenie |
|---|---|
| `xStart` | pozycja startowa w poziomie |
| `yStale` | wysokość pasa (nie zmienia się) |
| `predkosc` | piksele na sekundę |
| `kierunek` | LEWO lub PRAWO |
| `szerokosc` | szerokość planszy (do zawijania) |
| `wariantKoloruParam % 3` | kolor 0, 1 lub 2 (reszta z dzielenia przez 3) |

### Linie 14–37 — `aktualizuj`
```cpp
void Samochod::aktualizuj(float deltaSekundy, float mnoznikTempa) {
    const float dystans = predkoscPikseleNaSek * mnoznikTempa * deltaSekundy;
    const float marginesPozaPlansza = 36.0f;
```

**`deltaSekundy`** — ile sekund minęło od ostatniej klatki (np. 0.016 ≈ 60 FPS).  
**`mnoznikTempa`** — czasem auta jadą szybciej/wolniej (losowo z `PasRuchu`).  
**`dystans`** — o ile pikseli przesunąć auto w tej klatce.

**`marginesPozaPlansza = 36`** — auto może trochę „wyjechać” poza ekran, zanim zostanie przeniesione na drugą stronę (żeby zniknięcie/wjazd wyglądało naturalnie).

**Jazda w prawo (linie 22–28):**
```cpp
    if (kierunekRuchu == Kierunek::PRAWO) {
        x += dystans;
        if (x > szerokoscPlanszyPiksele + marginesPozaPlansza) {
            x = -marginesPozaPlansza;
        }
```
Auto jedzie w prawo. Gdy całkiem zniknie za prawą krawędzią → pojawia się z lewej strony.

**Jazda w lewo (linie 29–36):**
```cpp
    } else {
        x -= dystans;
        if (x < -marginesPozaPlansza) {
            x = szerokoscPlanszyPiksele + marginesPozaPlansza;
        }
    }
```
Odwrócona logika — znika z lewej, wraca z prawej.

### Linie 39–49 — gettery i setter
Proste zwracanie/ustawianie `x`, `y`, koloru.

---

# 4. `src/UstawieniaTrudnosci.cpp` — liczby dla każdego poziomu

Tu są **konkretne liczby** różniące Łatwy, Średni i Trudny.

---

### Linie 1–5
Include nagłówka i `<algorithm>` (funkcja `max_element`).

### Linie 7–27 — `pobierzUstawieniaTrudnosci`

```cpp
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom) {
    switch (poziom) {
```

`switch` — wybiera zestaw liczb w zależności od poziomu.

#### Poziom ŁATWY (linie 11–14)
```cpp
        case PoziomTrudnosci::LATWY:
            return UstawieniaTrudnosci{
                11, {1, 2, 4, 5}, 118.0f, 0.82f, 120.0f, 2, 4, 4};
```

| Liczba | Pole | Znaczenie |
|---|---|---|
| `11` | wysokoscSiatki | 11 wierszy planszy |
| `{1, 2, 4, 5}` | wierszePasow | Wiersze 1,2,4,5 to asfalt. Wiersz 3 to **trawa** między drogami |
| `118.0f` | predkoscSamochodow | Auta jadą ~118 px/s |
| `0.82f` | interwalTworzeniaAuta | Nowe auto co ~0.82 s |
| `120.0f` | minimalnyOdstepAut | Min. 120 px między autami |
| `2` | autaNaStarcieMin | Min. 2 auta na pasie na starcie |
| `4` | autaNaStarcieMax | Max. 4 auta na starcie |
| `4` | maksAutNaPasie | Max. 4 auta naraz na pasie |

**Układ łatwy:** 2 „ulice” — pasy 1–2 (pierwsza droga) i 4–5 (druga droga), między nimi trawa (wiersz 3).

#### Poziom ŚREDNI (linie 15–18)
```cpp
        case PoziomTrudnosci::SREDNI:
            return UstawieniaTrudnosci{
                11, {1, 2, 3, 4, 6, 7, 8, 9}, 128.0f, 0.68f, 102.0f, 2, 4, 4};
```
- **8 pasów** drogi: 1–4 i 6–9  
- Wiersz **5** to bezpieczna trawa między drogami  
- Szybsze auta, krótszy interwał spawnu, mniejszy odstęp

#### Poziom TRUDNY (linie 19–22)
```cpp
        case PoziomTrudnosci::TRUDNY:
            return UstawieniaTrudnosci{
                15, {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}, 168.0f, 0.58f, 78.0f, 3, 4, 4};
```
- **15 wierszy** planszy  
- **12 pasów** — najgęstszy ruch  
- Wiersz **7** to trawa między drogami  
- Najwyższa prędkość, najkrótszy interwał, najmniejszy odstęp

#### Zabezpieczenie (linie 25–26)
```cpp
    return UstawieniaTrudnosci{};
```
Gdyby kiedykolwiek przyszedł nieznany poziom — zwróć domyślne ustawienia.

### Linie 29–38 — `pobierzOstatniPasDrogi`
```cpp
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia) {
    if (ustawienia.wierszePasow.empty()) {
        return ustawienia.wysokoscSiatki - 2;
    }
    return *std::max_element(ustawienia.wierszePasow.begin(), ustawienia.wierszePasow.end());
}
```
Zwraca **numer najwyższego wiersza**, który jest drogą.  
Np. dla łatwego: max z {1,2,4,5} = **5**.

### Linie 40–44 — `pobierzWierszMety`
```cpp
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia) {
    return pobierzOstatniPasDrogi(ustawienia) + 1;
}
```
**Meta = jeden wiersz za ostatnią drogą.**  
Łatwy: ostatni pas = 5 → meta = **6**.

### Linie 46–57 — `czyWierszJestPasem`
```cpp
bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia) {
    for (const int pas : ustawienia.wierszePasow) {
        if (pas == wiersz) {
            return true;
        }
    }
    return false;
}
```
Przechodzi listę pasów. Jeśli `wiersz` jest na liście → `true` (to asfalt). Inaczej → `false` (trawa lub meta).

**Ważne:** kolizja z autem sprawdzana jest **tylko** gdy żaba stoi na pasie (`WykrywaczKolizji.cpp`).

---

# 5. `src/Droga.cpp` — budowa całej drogi

Łączy wiele pasów (`PasRuchu`) w jedną drogę.

---

### Linie 4–8 — początek `skonfiguruj`
```cpp
void Droga::skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                        float szerokoscPlanszy,
                        float wysokoscPlanszy,
                        float wysokoscPola) {
```
Wywoływane przy starcie gry z `Gra::rozpocznijGre`.

### Linie 9–14
```cpp
    pasy.clear();
    wierszePasow = ustawienia.wierszePasow;
    pasy.reserve(wierszePasow.size());
```
- `clear()` — usuń stare pasy (np. po poprzedniej grze)  
- skopiuj listę wierszy drogowych  
- `reserve` — zarezerwuj pamięć z góry (szybciej)

### Linie 16–17
```cpp
    const int liczbaWierszy = static_cast<int>(wysokoscPlanszy / wysokoscPola);
```
Ile wierszy mieści się na ekranie w pikselach.

### Linie 18–35 — pętla tworząca pasy
```cpp
    for (size_t i = 0; i < wierszePasow.size(); ++i) {
```

Dla **każdego** wiersza drogowego tworzymy jeden `PasRuchu`.

#### Linie 21–25 — przeliczenie wiersza na piksele
```cpp
        const int wierszLogiki = wierszePasow[i];
        const float wierszEkranu = static_cast<float>((liczbaWierszy - 1) - wierszLogiki);
        const float yPasa = (wierszEkranu + 0.5f) * wysokoscPola;
```

**Problem:** w logice gry Y=0 to **dół**, na ekranie Y=0 to **góra**.  
Dlatego odwracamy: `wierszEkranu = (liczbaWierszy - 1) - wierszLogiki`.  
`+ 0.5f` — środek wiersza, nie jego górna krawędź.

#### Linie 26–27 — kierunek naprzemiennie
```cpp
        const Kierunek kierunek = (i % 2 == 0) ? Kierunek::PRAWO : Kierunek::LEWO;
```
Pas 0 → prawo, pas 1 → lewo, pas 2 → prawo… (jak w klasycznym Froggerze).

#### Linie 28–30 — lekka różnica prędkości
```cpp
        const float predkoscPasowa =
            ustawienia.predkoscSamochodow + 8.0f * static_cast<float>(i % 3);
```
Każdy pas trochę inaczej szybki (+0, +8 lub +16 px/s) — ruch mniej monotonny.

#### Linie 31–34 — tworzenie pasa
```cpp
        pasy.emplace_back(yPasa, kierunek, predkoscPasowa, ustawienia.interwalTworzeniaAuta,
                          szerokoscPlanszy, ustawienia.minimalnyOdstepAut, ustawienia.autaNaStarcieMin,
                          ustawienia.autaNaStarcieMax, ustawienia.maksAutNaPasie);
```
`emplace_back` — dodaje nowy `PasRuchu` na końcu listy.

### Linie 38–44 — `aktualizuj`
```cpp
void Droga::aktualizuj(float deltaSekundy, std::mt19937& generator) {
    for (auto& pas : pasy) {
        pas.aktualizuj(deltaSekundy, generator);
    }
}
```
Co klatkę aktualizuje **każdy pas** osobno.

### Linie 46–54 — gettery
Zwracają listę pasów i listę numerów wierszy.

---

# 6. `src/WykrywaczKolizji.cpp` — czy żaba uderzyła w auto

---

### Linie 11–19
```cpp
bool WykrywaczKolizji::czyJestKolizja(...) const {
    (void)szerokoscSiatki;
    (void)wysokoscSiatki;
```
Parametry są w sygnaturze „na przyszłość”, ale na razie nieużywane. `(void)...` — wycisza ostrzeżenie kompilatora.

### Linie 21–26 — czy żaba w ogóle jest na drodze
```cpp
    const int wierszZaby = zaba.pobierzY();
    if (!czyWierszJestPasem(wierszZaby, ustawienia)) {
        return false;
    }
```
**Na trawie lub mecie nie ma kolizji z autem** — od razu `false`.

### Linie 28–36 — „rozmiary” do testu zderzenia
```cpp
    const float srodekZabyX =
        (static_cast<float>(zaba.pobierzX()) + 0.5f) * rozmiarPola;
    const float polowaSzerokosciZaby = rozmiarPola * 0.16f;
    const float polowaSzerokosciAuta = rozmiarPola * 0.34f;
    const float minimalnyZachod = polowaSzerokosciZaby + polowaSzerokosciAuta;
```

Uproszczony test: traktujemy żabę i auto jak **kółka** o pewnej „szerokości”.  
Kolizja, gdy odległość środków jest mniejsza niż suma promieni.

| Wartość | Znaczenie |
|---|---|
| `srodekZabyX` | środek żaby w pikselach (X) |
| `0.16f * rozmiarPola` | „połowa szerokości” żaby |
| `0.34f * rozmiarPola` | „połowa szerokości” auta |
| `minimalnyZachod` | próg — bliżej = kolizja |

### Linie 38–57 — sprawdzanie aut
```cpp
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
```

1. Dla każdego pasa — **pomiń**, jeśli pas nie jest na wierszu żaby  
2. Dla każdego auta na tym pasie — sprawdź odległość w poziomie  
3. Za blisko → **kolizja** (`true`)

### Linia 60
```cpp
    return false;
```
Żadne auto nie trafiło w żabę.

**Kto woła:** `Gra::sprawdzWarunkiKonca` — po ruchu żaby i po ruchu aut.

---

# 7. `src/PasRuchu.cpp` — jeden pas z wieloma autami

Najdłuższy plik logiki ruchu. Zarządza spawnem, odstępami, gęstością i widocznością aut na **jednym** pasie.

---

### Linie 9–17 — stałe (ukryty „namespace”)
```cpp
namespace {
constexpr float MIN_GESTOSC_RUCHU = 0.75f;
constexpr float MAX_GESTOSC_RUCHU = 1.35f;
constexpr float MAKS_OPOZNIENIE_FAZY = 0.5f;
}
```

| Stała | Znaczenie |
|---|---|
| `MIN_GESTOSC_RUCHU` | Auta mogą jechać min. 75% normalnej prędkości |
| `MAX_GESTOSC_RUCHU` | Max. 135% prędkości |
| `MAKS_OPOZNIENIE_FAZY` | Losowe opóźnienie startu pasa (0–0.5 s) |

`namespace { }` bez nazwy — te stałe widoczne tylko w tym pliku.

### Linie 19–38 — konstruktor
Ustawia wszystkie pola pasa. Ważne:
```cpp
      maksAutNaPasie(std::max(2, maksAutNaPasieParam)) {}
```
Zawsze **min. 2** auta na pasie (nawet gdyby config miał mniej).

### Linie 40–78 — `aktualizuj` (serce pasa)

#### Faza startowa (linie 42–48)
```cpp
    if (!czyRuchStartowyZrobiony) {
        std::uniform_real_distribution<float> losFaza(0.0f, MAKS_OPOZNIENIE_FAZY);
        licznikDoSpawnu = interwalSpawnu * losFaza(generator);
        dodajRuchPoczatkowy(generator);
        czyRuchStartowyZrobiony = true;
    }
```
**Pierwsze wywołanie:** losowe opóźnienie + początkowy zestaw aut na pasie.

#### Ruch aut (linie 50–56)
```cpp
    for (auto& autoNaPasie : samochody) {
        autoNaPasie.aktualizuj(deltaSekundy, wspolczynnikGestosciRuchu);
    }
    normalizujPozycjeAut();
    utrzymijWidocznyRuch(generator);
```
Rusz wszystkie auta → popraw pozycje po zawijaniu → upewnij się, że coś widać.

#### Losowa gęstość (linie 58–65)
```cpp
    czasDoZmianyGestosci -= deltaSekundy;
    if (czasDoZmianyGestosci <= 0.0f) {
        ...
        wspolczynnikGestosciRuchu = losGestosc(generator);
        czasDoZmianyGestosci = losCzas(generator);
    }
```
Co jakiś czas (0.9–1.8 s) losowo zmienia tempo aut na pasie.

#### Spawn nowych aut (linie 67–77)
```cpp
    licznikDoSpawnu -= deltaSekundy;
    if (licznikDoSpawnu <= 0.0f) {
        if (czyMoznaDodacAuto()) {
            dodajSamochod();
        }
        licznikDoSpawnu =
            (interwalSpawnu * wspolczynnikGestosciRuchu) + losujDodatkoweOpoznienie(generator);
    }
```
Odliczanie do nowego auta. Gdy czas minie i jest miejsce → dodaj auto → ustaw następny timer.

### Linie 84–88 — `ograniczXNaPasie`
Trzyma pozycję X w środkowej części planszy (margines 28 px od krawędzi).

### Linie 90–97 — `dodajSamochod`
```cpp
    const float xStart =
        (kierunekRuchu == Kierunek::PRAWO) ? -28.0f : (szerokoscPlanszy + 28.0f);
```
Nowe auto **wjedzie z boku**:
- jadą w prawo → startuje z lewej (x = -28)  
- jadą w lewo → startuje z prawej (x = szerokość + 28)

### Linie 99–103 — `czyOdlegloscWystarczajaca`
```cpp
    const float minOdleglosc = minimalnyOdstep * 0.72f;
    return std::abs(x1 - x2) >= minOdleglosc;
```
Dwa auta muszą być co najmniej ~72% `minimalnyOdstep` od siebie.

### Linie 105–126 — `losujWolneMiejsceNaPasie`
Próbuje do **24 razy** wylosować pozycję X, która nie koliduje z innymi autami.  
Zakres: 12%–88% szerokości planszy.

### Linie 128–149 — `dodajRuchPoczatkowy`
```cpp
    std::uniform_int_distribution<int> liczbaAut(autaStartMin, autaStartMax);
    const int ileAut = liczbaAut(generator);
```
Na starcie losuje **ile** aut (między min a max), potem dla każdego losuje wolne miejsce.  
Jeśli losowanie się nie uda — pozycja awaryjna.  
Na końcu: jeśli nic nie widać → `dodajSamochod()`.

### Linie 151–169 — `czyMoznaDodacAuto`
1. Za dużo aut na pasie? → nie  
2. Sprawdź odległość od punktu spawnu (lewa lub prawa krawędź)  
3. Uwzględnij zawijanie planszy (odległość „wokół” ekranu)

### Linie 171–175 — `losujDodatkoweOpoznienie`
Losowe 0.04–0.35 s dodane do interwału spawnu.

### Linie 177–188 — `znormalizujX`
„Zawija” X wokół planszy — jak modulo, ale z marginesem 36 px.

### Linie 190–199 — `normalizujPozycjeAut`
Dla każdego auta: jeśli X za daleko poza ekranem → popraw przez `znormalizujX`.

### Linie 201–210 — `czyPasMaWidoczneAuto`
Czy choć jedno auto ma X między 0 a szerokością planszy (widać je na ekranie).

### Linie 212–221 — `utrzymijWidocznyRuch`
Jeśli **żadne** auto nie jest widoczne → dodaj nowe (żeby pas nie był pusty).

---

# 8. `src/Gra.cpp` — mózg całej gry

Łączy żabę, drogę, kolizje, stan gry i zegar. **Nie rysuje** — tylko liczy.

---

### Linia 5 — konstruktor
```cpp
Gra::Gra() : generator(std::random_device{}()) {}
```
Tworzy generator losowy z „losowym ziarnem” (każda gra trochę inna).

### Linie 7–33 — `rozpocznijGre`

| Linie | Co się dzieje |
|---|---|
| 10 | Zapamiętaj poziom (ŁATWY/ŚREDNI/TRUDNY) |
| 12 | Pobierz liczby z `UstawieniaTrudnosci.cpp` |
| 14 | Ustaw wysokość siatki z configu |
| 16 | `rozmiarPola = 660 / wysokoscSiatki` — plansza ma 660 px wysokości |
| 19–21 | Szerokość i wysokość w pikselach |
| 23 | Zbuduj drogę i pasy |
| 26 | Żaba na środku dołu: `(szerokoscSiatki/2, 0)` |
| 28 | Wyczyść flagę wygranej |
| 30 | Start zegara |
| 32 | Stan → `W_TRAKCIE` |

### Linie 35–41 — `przejdzDoMenu`
Reset flagi wygranej, stan → `MENU`.

### Linie 43–55 — `ruch`
```cpp
void Gra::ruch(int dx, int dy) {
    if (stan != StanGry::W_TRAKCIE) {
        return;
    }
    zaba.ruch(dx, dy, 1);
    zaba.ograniczDoPlanszy(szerokoscSiatki, wysokoscSiatki);
    sprawdzWarunkiKonca();
}
```
1. Ignoruj, jeśli nie grasz  
2. Rusz żabą  
3. Nie wypuszczaj poza planszę  
4. Sprawdź kolizję / metę

### Linie 57–81 — `aktualizujKrok`
Wywoływane **co klatkę** z timera GUI (~60 razy na sekundę).

```cpp
    if (stan != StanGry::W_TRAKCIE) return;

    if (czekaNaKlatkeMety) {
        finalizujOczekujacaWygrana();
        return;
    }

    sprawdzWarunkiKonca();
    if (stan != StanGry::W_TRAKCIE) return;

    droga.aktualizuj(deltaSekundy, generator);
    sprawdzWarunkiKonca();
```

**Kolejność:**
1. Jeśli czekamy na klatkę mety → sfinalizuj wygraną  
2. Sprawdź koniec (kolizja?)  
3. Rusz autami  
4. Sprawdź koniec ponownie (auto mogło wjechać w żabę)

### Linie 83–102 — `sprawdzWarunkiKonca`

**Kolizja (linie 85–91):**
```cpp
    if (wykrywaczKolizji.czyJestKolizja(...)) {
        stan = StanGry::PRZEGRANA;
        zatrzymajZegar();
        return;
    }
```

**Meta (linie 93–101):**
```cpp
    const int wierszMety = pobierzWierszMety(ustawienia);
    if (wierszZaby == wierszMety) {
        czekaNaKlatkeMety = true;
    }
```
Żaba weszła na wiersz mety → **nie od razu wygrana**, tylko flaga. Wygrana w **następnej** klatce (żeby gracz zobaczył żabę na mecie).

### Linie 104–117 — `finalizujOczekujacaWygrana`
Czyści flagę, stan → `WYGRANA`, zatrzymuje zegar.

### Linie 119–136 — zegar
- `uruchomZegar` — zapisuje `startCzasu`, zegar działa  
- `zatrzymajZegar` — zapisuje `czasZatrzymania` (tylko raz)

### Linie 150–157 — `pobierzCzasSekundy`
```cpp
    const auto koniec = zegarZatrzymany ? czasZatrzymania : std::chrono::steady_clock::now();
    return static_cast<int>(... koniec - startCzasu ...);
```
Jeśli gra trwa → czas do „teraz”. Jeśli skończona → czas do momentu zatrzymania.

### Linie 138–166 — pozostałe gettery
Proste zwracanie stanu, poziomu, żaby, drogi, wymiarów planszy.

---

# 9. `src/InterfejsGraficzny.cpp` — okno, rysowanie, sterowanie

Największy plik wizualny. Łączy Qt z logiką `Gra`.

---

## Część A: Konstruktor (linie 17–37)

```cpp
InterfejsGraficzny::InterfejsGraficzny(QWidget* rodzic) : QWidget(rodzic) {
    setWindowTitle(QStringLiteral("Żaba na ulicy - Qt GUI"));
    setFixedSize(960, 720);
    setFocusPolicy(Qt::StrongFocus);
```
- Tytuł okna  
- Stały rozmiar 960×720 px  
- `StrongFocus` — okno łapie klawisze (W/A/S/D)

```cpp
    przyciskLatwy = QRect(370, 250, 220, 62);
    przyciskSredni = QRect(370, 340, 220, 62);
    przyciskTrudny = QRect(370, 430, 220, 62);
    przyciskPowrot = QRect(340, 470, 280, 64);
```
**Prostokąty przycisków** — (x, y, szerokość, wysokość) w pikselach. Używane przy klikaniu myszą.

```cpp
    timerPetli.setInterval(16);  // 16 ms = 60 Hz
    connect(&timerPetli, &QTimer::timeout, this, &InterfejsGraficzny::odswiezSymulacje);
    timerPetli.start();
    zegarKlatek.start();
```
Timer co **16 ms** (~60 klatek/s) woła `odswiezSymulacje` — aktualizuje grę i przerysowuje ekran.

---

## Część B: `paintEvent` (linie 39–53) — co rysować

```cpp
void InterfejsGraficzny::paintEvent(QPaintEvent* zdarzenie) {
    QPainter rysownik(this);
    rysownik.setRenderHint(QPainter::Antialiasing, true);

    if (gra.pobierzStan() == StanGry::MENU) {
        rysujMenu(rysownik);
    } else if (gra.pobierzStan() == StanGry::W_TRAKCIE) {
        rysujRozgrywke(rysownik);
    } else {
        rysujRozgrywke(rysownik);
        rysujEkranKoncowy(rysownik, gra.pobierzStan() == StanGry::WYGRANA);
    }
}
```

| Stan | Co na ekranie |
|---|---|
| MENU | Tylko menu |
| W_TRAKCIE | Plansza gry |
| WYGRANA / PRZEGRANA | Plansza + półprzezroczysta nakładka z wynikiem |

---

## Część C: `mousePressEvent` (linie 55–76) — kliknięcia

```cpp
    if (gra.pobierzStan() == StanGry::MENU) {
        if (przyciskLatwy.contains(pozycja)) {
            gra.rozpocznijGre(PoziomTrudnosci::LATWY);
        } else if ...
```
Sprawdza, czy kliknięto w prostokąt przycisku → startuje grę na danym poziomie.

```cpp
    } else if ((gra.pobierzStan() == StanGry::WYGRANA || ...) &&
               przyciskPowrot.contains(pozycja)) {
        gra.przejdzDoMenu();
    }
    update();
```
Na ekranie końcowym — klik „Powrót do menu”. `update()` — przerysuj okno.

---

## Część D: `keyPressEvent` (linie 78–99) — klawiatura

Działa **tylko** gdy `stan == W_TRAKCIE`:

| Klawisz | Wywołanie | Ruch |
|---|---|---|
| W | `gra.ruch(0, 1)` | góra |
| S | `gra.ruch(0, -1)` | dół |
| A | `gra.ruch(-1, 0)` | lewo |
| D | `gra.ruch(1, 0)` | prawo |
| Escape | `gra.przejdzDoMenu()` | powrót do menu |

---

## Część E: `odswiezSymulacje` (linie 101–108) — pętla gry

```cpp
void InterfejsGraficzny::odswiezSymulacje() {
    const qint64 ms = zegarKlatek.restart();
    const float deltaSekundy = static_cast<float>(ms) / 1000.0f;
    gra.aktualizujKrok(deltaSekundy);
    update();
}
```
1. Ile ms minęło od ostatniej klatki  
2. Przelicz na sekundy  
3. Zaktualizuj logikę (`auta`, kolizje…)  
4. Poproś Qt o przerysowanie

---

## Część F: `rysujMenu` (linie 110–128)

- Ciemne gradientowe tło  
- Tytuł „Żaba na ulicy”  
- Podtytuł „Wybierz poziom trudności”  
- 3 przyciski: Łatwy, Średni, Trudny

---

## Część G: `rysujRozgrywke` (linie 130–262) — najważniejsze rysowanie

### Przygotowanie (linie 132–137)
```cpp
    const float rozmiarPola = gra.pobierzRozmiarPola();
    const int offsetX = (width() - szerokoscPlanszy) / 2;
```
Plansza wyśrodkowana w oknie (ciemne boki po lewej i prawej).

### Tło i trawa (linie 139–152)
Najpierw ciemne tło, potem **cała plansza = zielona trawa**.

### Droga (linie 154–169)
```cpp
    for (const int wierszDrogi : gra.pobierzDroge().pobierzWierszePasow()) {
        const int yPasa = ... (ostatniWiersz - wierszDrogi) * rozmiarPola;
        const QColor kolor = (indeksPasa % 2 == 0) ? ... szary ... : ... ciemniejszy szary;
        rysownik.fillRect(...);  // asfalt
        // przerywane żółte linie
    }
```
Tylko wiersze z listy `wierszePasow` dostają szary asfalt i linie drogowe. Reszta zostaje trawą.

### Samochody (linie 171–217)
```cpp
    for (const auto& pas : gra.pobierzDroge().pobierzPasy()) {
        for (const auto& autoNaPasie : pas.pobierzSamochody()) {
            if (auto poza ekranem) continue;
            // prostokąt nadwozia (czerwony / niebieski / żółty)
            // szyby (jasnoniebieskie)
            // koła (czarne)
        }
    }
```

| wariantKoloru | Kolor nadwozia |
|---|---|
| 0 | czerwony |
| 1 | niebieski |
| 2 (default) | żółty/pomarańczowy |

### Żaba (linie 220–249)
```cpp
    const float x = (pozycjaX + 0.5f) * rozmiarPola;
    const float y = (ostatniWiersz - pozycjaY + 0.5f) * rozmiarPola;
```
Znów odwrócenie osi Y (logika vs ekran).

Rysowane elementy:
1. Cień (ciemnozielony, lekko w dół)  
2. Zielony owal — korpus  
3. Białe oczy + czarne źrenice  
4. Zielone „łapy” (elipty na dole)

### Pasek statusu (linie 253–261)
Ciemny pasek na dole okna: poziom, czas w sekundach, przypomnienie sterowania W/A/S/D.

---

## Część H: `rysujEkranKoncowy` (linie 264–279)

- Półprzezroczysta ciemna nakładka na całe okno  
- Duży napis **WYGRANA** (zielony) lub **PRZEGRANA** (czerwony)  
- Czas gry  
- Tekst „Kliknij przycisk…”  
- Przycisk „Powrót do menu”

---

## Część I: `rysujPrzycisk` (linie 281–292)

Niebieski gradient, zaokrąglone rogi, biały tekst na środku. Wspólny styl dla wszystkich przycisków.

---

## Część J: `tekstPoziomu` (linie 294–305)

Zamienia enum na polski tekst: Łatwy / Średni / Trudny.

---

# 10. `tests/TestyLogiki.cpp` — automatyczne testy

Ten plik **nie jest częścią gry**, którą widzisz w oknie. To program testowy uruchamiany przez `ctest` — sprawdza, czy logika działa poprawnie.

---

### Linie 13–21 — `oczekuj`
```cpp
void oczekuj(bool warunek, const std::string& wiadomosc) {
    if (!warunek) {
        std::cerr << "BLAD TESTU: " << wiadomosc << "\n";
        std::exit(1);
    }
}
```
Jeśli warunek fałszywy → wypisz błąd i zakończ z kodem 1 (test nie przeszedł).

### `testUstawienTrudnosci` (linie 23–35)
Sprawdza:
- Łatwy ma 4 pasy, Średni 8, Trudny 12  
- Prędkość rośnie: łatwy < średni < trudny

### `testRuchuZabyIGranicPlanszy` (linie 37–53)
- 10× ruch w dół od dołu → żaba zostaje na Y=0  
- 100× ruch w lewo → żaba zostaje na X=0

### `testBrakKolizjiNaTrawie` (linie 55–69)
Żaba idzie na trawę (wiersz 3 na łatwym), symulacja 120 klatek → **nadal W_TRAKCIE** (brak fałszywej przegranej).

### `testWarunkuWygranej` (linie 71–105)
- Na **ostatnim pasie drogi** jeszcze nie ma wygranej  
- Dopiero **krok na metę** (wiersz za drogą) → WYGRANA  
- Osobno dla łatwego i średniego

### `main` testów (linie 110–118)
Uruchamia wszystkie testy po kolei. Jeśli wszystko OK → wypisuje „OK: Wszystkie testy przeszly.”

**Uruchomienie:** `ctest --test-dir build --output-on-failure`

---

# Mapa: „Szukam kodu odpowiedzialnego za X”

| Chcę znaleźć… | Plik .cpp | Funkcja / miejsce |
|---|---|---|
| Start programu | `main.cpp` | `main()` |
| Uruchomienie okna | `main.cpp` | `okno.show()`, `exec()` |
| Rozmiar okna 960×720 | `InterfejsGraficzny.cpp` | konstruktor, `setFixedSize` |
| Timer 60 FPS | `InterfejsGraficzny.cpp` | `timerPetli.setInterval(16)` |
| Menu główne | `InterfejsGraficzny.cpp` | `rysujMenu` |
| Klik w Łatwy/Średni/Trudny | `InterfejsGraficzny.cpp` | `mousePressEvent` |
| Sterowanie W/A/S/D | `InterfejsGraficzny.cpp` | `keyPressEvent` |
| Ruch żaby (logika) | `Zaba.cpp` | `ruch`, `ograniczDoPlanszy` |
| Pozycja startowa żaby | `Gra.cpp` | `rozpocznijGre` → `ustawPozycjeStartowa` |
| Rysowanie żaby | `InterfejsGraficzny.cpp` | `rysujRozgrywke` (linie 220–249) |
| Rysowanie aut | `InterfejsGraficzny.cpp` | `rysujRozgrywke` (linie 171–217) |
| Ruch aut | `Samochod.cpp` | `aktualizuj` |
| Spawn aut | `PasRuchu.cpp` | `dodajSamochod`, `aktualizuj` |
| Odstępy między autami | `PasRuchu.cpp` | `czyMoznaDodacAuto`, `czyOdlegloscWystarczajaca` |
| Układ pasów | `Droga.cpp` | `skonfiguruj` |
| Naprzemienny kierunek pasów | `Droga.cpp` | `i % 2 == 0` |
| Liczby poziomów | `UstawieniaTrudnosci.cpp` | `pobierzUstawieniaTrudnosci` |
| Które wiersze to trawa | `UstawieniaTrudnosci.cpp` | lista `wierszePasow` |
| Gdzie jest meta | `UstawieniaTrudnosci.cpp` | `pobierzWierszMety` |
| Kolizja | `WykrywaczKolizji.cpp` | `czyJestKolizja` |
| Wygrana | `Gra.cpp` | `sprawdzWarunkiKonca`, `finalizujOczekujacaWygrana` |
| Przegrana | `Gra.cpp` | `sprawdzWarunkiKonca` |
| Licznik czasu | `Gra.cpp` | `uruchomZegar`, `zatrzymajZegar`, `pobierzCzasSekundy` |
| Ekran WYGRANA/PRZEGRANA | `InterfejsGraficzny.cpp` | `rysujEkranKoncowy` |
| Powrót do menu | `Gra.cpp` + `InterfejsGraficzny.cpp` | `przejdzDoMenu` |
| Rysowanie trawy i asfaltu | `InterfejsGraficzny.cpp` | `rysujRozgrywke` |
| Testy automatyczne | `TestyLogiki.cpp` | `main()` testów |
| Dokumentacja Doxygen | wszystkie `.h` | `doxygen Doxyfile` → `docs/doxygen/html/` |
| Oddanie projektu (PDF) | `DOKUMENTACJA_OPISOWA.md` | założenia, wymagania, diagram klas |
| Zrzuty ekranu | `docs/screenshots/` | do uzupełnienia przed prezentacją |

---

# Jak pliki .cpp łączą się ze sobą (przepływ gry)

```
main.cpp
  └── tworzy InterfejsGraficzny
        ├── ma obiekt Gra (Gra.cpp)
        │     ├── Zaba (Zaba.cpp)
        │     ├── Droga (Droga.cpp)
        │     │     └── wiele PasRuchu (PasRuchu.cpp)
        │     │           └── wiele Samochod (Samochod.cpp)
        │     ├── WykrywaczKolizji (WykrywaczKolizji.cpp)
        │     └── UstawieniaTrudnosci (UstawieniaTrudnosci.cpp)
        │
        ├── timer co 16ms → odswiezSymulacje → Gra::aktualizujKrok
        ├── klawiatura → Gra::ruch → Zaba::ruch
        ├── mysz → Gra::rozpocznijGre / przejdzDoMenu
        └── paintEvent → rysujMenu / rysujRozgrywke / rysujEkranKoncowy

tests/TestyLogiki.cpp  (osobny program, bez Qt GUI)
  └── testuje klase Gra i UstawieniaTrudnosci
      └── uruchomienie: ctest --test-dir build
```

---

## Uwaga o plikach `.h`

Od czerwca 2025 wszystkie nagłówki w `include/` mają komentarze **Doxygen** (`@file`, `@brief`, `@param`, `@return`).  
Opis deklaracji klas i metod jest w `PRZEWODNIK_PLIKI_H.md` — numery linii tam odpowiadają aktualnej wersji plików.

---

*Część 2: pliki `.cpp`. Część 1: `PRZEWODNIK_PLIKI_H.md`. Dokumentacja projektu: `DOKUMENTACJA_OPISOWA.md`*
