# Przewodnik po plikach .h — gra „Żaba na ulicy”

**Ostatnia aktualizacja:** czerwiec 2025 (zgodna z wersją z komentarzami Doxygen)

Ten dokument wyjaśnia **każdą linijkę** w plikach nagłówkowych (`.h`) w najprostszy możliwy sposób.  
Plik `.h` to jak **spis treści / instrukcja** — mówi, *co dana część programu potrafi*, ale prawdziwa praca dzieje się w plikach `.cpp` o tej samej nazwie.

**Powiązane dokumenty:**
| Plik | Zawartość |
|---|---|
| `PRZEWODNIK_PLIKI_CPP.md` | Ten sam poziom szczegółowości, ale dla plików `.cpp` |
| `DOKUMENTACJA_OPISOWA.md` | Dokumentacja do oddania projektu (wymagania, GUI, diagram klas) |
| `SPRAWDZENIE_WYMAGAN.md` | Checklist zgodności z PDF prowadzącego |
| `Doxyfile` + `doxygen Doxyfile` | Automatyczna dokumentacja HTML z komentarzy w `.h` |

---

## Jak czytać ten przewodnik

| Słowo w kodzie | Co to znaczy po ludzku |
|---|---|
| `@file`, `@brief`, `@param`, `@return` | Tagi **Doxygen** — służą do generowania dokumentacji HTML |
| `#pragma once` | „Wczytaj ten plik tylko raz” — zabezpieczenie przed powtórkami |
| `#include` | „Weź też inny plik, bo go potrzebuję” |
| `enum class` | Lista nazwanych opcji do wyboru (jak menu z 3–4 pozycjami) |
| `struct` | Pudełko na kilka powiązanych liczb / ustawień |
| `class` | Opis obiektu w grze (np. żaba, samochód) — co ma i co potrafi |
| `void` | Funkcja, która coś robi, ale nic nie zwraca |
| `int` | Liczba całkowita (1, 2, 3…) |
| `float` | Liczba z przecinkiem (np. 100.5) |
| `bool` | Prawda albo fałsz (tak / nie) |
| `const` | „Tylko do odczytu — nie zmieniaj” |
| `public` | Rzeczy, z których inne części programu mogą korzystać |
| `private` | Rzeczy tylko dla tej klasy — „wewnętrzna kuchnia” |
| `override` | Nadpisuje metodę z klasy bazowej (Qt) |

**Gdzie szukać działania?**  
Nagłówek (`.h`) mówi *co jest*. Implementacja (`.cpp`) mówi *jak to działa* — opis w `PRZEWODNIK_PLIKI_CPP.md`.

**Blok Doxygen na początku każdego pliku** (linie 1–4) wygląda tak:
```cpp
/**
 * @file NazwaPliku.h
 * @brief Krotki opis calego pliku.
 */
```
Kompilator tego nie wykonuje — to dokumentacja dla człowieka i dla `doxygen`.

---

# 1. `include/Typy.h` — podstawowe „etykiety” gry (28 linii)

Ten plik **nie rysuje nic** i **nie porusza niczym**.  
To słownik nazw — program wie, że gra może być w menu, w trakcie, po wygranej itd.

---

### Linie 1–4 — nagłówek Doxygen
```cpp
/**
 * @file Typy.h
 * @brief Wspolne typy wyliczeniowe gry (stan, trudnosc, kierunek).
 */
```
Opis całego pliku dla dokumentacji Doxygen.

### Linia 6
```cpp
#pragma once
```
**Zabezpieczenie.** Plik wczytywany tylko raz.

### Linie 8–14 — `enum class StanGry`
```cpp
/** @brief Stan aplikacji / ekranu gry. */
enum class StanGry {
    MENU,       // Gracz widzi menu glowne i wybiera poziom.
    W_TRAKCIE,  // Trwa aktywna rozgrywka.
    WYGRANA,    // Gra zakonczona sukcesem.
    PRZEGRANA   // Gra zakonczona porazka (np. kolizja).
};
```

| Wartość | Znaczenie | Gdzie widać w grze |
|---|---|---|
| `MENU` | Ekran startowy | Przyciski Łatwy / Średni / Trudny |
| `W_TRAKCIE` | Normalna rozgrywka | Żaba, droga, samochody |
| `WYGRANA` | Dotarłaś na metę | Ekran „wygrana” |
| `PRZEGRANA` | Kolizja z autem | Ekran „przegrana” |

**Gdzie się zmienia:** `Gra.cpp` — pole `stan`; `InterfejsGraficzny.cpp` — rysowanie wg stanu.

### Linie 16–21 — `enum class PoziomTrudnosci`
```cpp
/** @brief Poziom trudnosci wybrany przez gracza. */
enum class PoziomTrudnosci {
    LATWY, SREDNI, TRUDNY
};
```

| Wartość | Co zmienia |
|---|---|
| `LATWY` | 4 pasy, wolniejsze auta |
| `SREDNI` | 8 pasów, trawa między drogami |
| `TRUDNY` | 12 pasów, najszybsze auta |

**Gdzie ustawiane liczby:** `UstawieniaTrudnosci.cpp` — `pobierzUstawieniaTrudnosci`

### Linie 23–27 — `enum class Kierunek`
```cpp
/** @brief Kierunek ruchu samochodu na pasie. */
enum class Kierunek { LEWO, PRAWO };
```

**Gdzie używane:** `Samochod.cpp`, `PasRuchu.cpp`, `Droga.cpp`

---

# 2. `include/UstawieniaTrudnosci.h` — liczby poziomów (62 linie)

---

### Linie 1–4 — Doxygen
`@file UstawieniaTrudnosci.h` — parametry poziomów trudności.

### Linie 6, 9, 12
`#pragma once`, `#include "Typy.h"`, `#include <vector>`.

### Linie 14–32 — `struct UstawieniaTrudnosci`
```cpp
/** @brief Zestaw parametrow opisujacych jeden poziom trudnosci. */
struct UstawieniaTrudnosci { ... };
```

| Linia | Pole | Znaczenie |
|---|---|---|
| 17 | `wysokoscSiatki` | Ile wierszy ma plansza |
| 19 | `wierszePasow` | Które wiersze to asfalt (lista) |
| 21 | `predkoscSamochodow` | Piksele/sekundę |
| 23 | `interwalTworzeniaAuta` | Co ile sekund nowe auto |
| 25 | `minimalnyOdstepAut` | Min. odległość między autami [px] |
| 27 | `autaNaStarcieMin` | Min. aut na starcie |
| 29 | `autaNaStarcieMax` | Max. aut na starcie |
| 31 | `maksAutNaPasie` | Limit aut na pasie |

**Wypełnianie wartości:** `UstawieniaTrudnosci.cpp` linie 11–22.

### Linie 34–39 — `pobierzUstawieniaTrudnosci`
```cpp
/**
 * @brief Zwraca komplet ustawien dla wybranego poziomu trudnosci.
 * @param poziom Poziom LATWY, SREDNI lub TRUDNY.
 * @return Struktura UstawieniaTrudnosci z parametrami planszy i ruchu aut.
 */
```
**Implementacja:** `UstawieniaTrudnosci.cpp`

### Linie 41–46 — `pobierzOstatniPasDrogi`
Zwraca numer **ostatniego wiersza drogi**.

### Linie 48–53 — `pobierzWierszMety`
Meta = ostatni pas + 1. **Wygrana:** `Gra.cpp` — `sprawdzWarunkiKonca`.

### Linie 55–61 — `czyWierszJestPasem`
`true` = wiersz to asfalt. Używane w `WykrywaczKolizji.cpp` — brak kolizji na trawie.

---

# 3. `include/Zaba.h` — gracz (36 linii)

---

### Linie 1–4 — Doxygen
`@file Zaba.h` — pozycja i ruch gracza.

### Linie 8–9 — klasa
```cpp
/** @brief Reprezentuje gracza i obsluguje jego ruch po planszy. */
class Zaba {
```

### `public` — metody

| Linie | Metoda | Co robi | Gdzie wywoływane |
|---|---|---|---|
| 11–12 | `ustawPozycjeStartowa` | Start na dole planszy | `Gra.cpp` — `rozpocznijGre` |
| 14–20 | `ruch(dx, dy, krok)` | Ruch W/A/S/D | `Gra.cpp` — `ruch` |
| 22–23 | `ograniczDoPlanszy` | Granice planszy | `Gra.cpp` — po ruchu |
| 25–28 | `pobierzX`, `pobierzY` | Aktualna pozycja | Rysowanie, kolizje, meta |

### `private` — pola (linie 30–34)

| Linia | Pole | Znaczenie |
|---|---|---|
| 32 | `int x = 0` | Kolumna |
| 34 | `int y = 0` | Wiersz |

**Implementacja:** `Zaba.cpp` | **Sterowanie:** `InterfejsGraficzny.cpp` → `keyPressEvent`

---

# 4. `include/Samochod.h` — jedno auto (56 linii)

---

### Linie 1–4 — Doxygen | Linie 8–9 — `#include "Typy.h"`

### Linie 11–12 — klasa
```cpp
/** @brief Samochod poruszajacy sie po jednym pasie drogi. */
class Samochod {
```

### Linie 14–24 — konstruktor (z `@param` dla każdego argumentu)
Tworzy auto: pozycja X/Y, prędkość, kierunek, szerokość planszy, kolor (0–2).

### Linie 26–31 — `aktualizuj`
`@param deltaSekundy` — czas klatki; `@param mnoznikTempa` — losowa gęstość (0.75–1.35).  
**Implementacja:** `Samochod.cpp`

### Linie 33–40 — gettery i `ustawX`

### `private` — pola (linie 42–54)

| Pole | Znaczenie |
|---|---|
| `x`, `y` | Pozycja [px] |
| `predkoscPikseleNaSek` | Szybkość |
| `kierunekRuchu` | LEWO / PRAWO |
| `szerokoscPlanszyPiksele` | Do zawijania |
| `wariantKoloru` | 0=czerwony, 1=niebieski, 2=żółty |

---

# 5. `include/PasRuchu.h` — jeden pas z autami (88 linii)

---

### Linie 1–4 — Doxygen | Linie 8–14 — include

### Linie 16–17 — klasa
```cpp
/** @brief Pas ruchu z wieloma samochodami jadacymi w jednym kierunku. */
```

### Linie 19–28 — konstruktor
Parametry: `yPasa`, kierunek, prędkość, interwał spawnu, szerokość, odstępy, limity aut.

### `public` (linie 30–37)

| Linie | Metoda | Co robi |
|---|---|---|
| 30–31 | `aktualizuj` | Ruch, spawn, gęstość |
| 32–33 | `pobierzSamochody` | Lista aut |
| 34–35 | `czyPasMaWidoczneAuto` | Czy coś widać |
| 36–37 | `utrzymijWidocznyRuch` | Dokłada auto gdy pas pusty |

### `private` — metody (linie 40–57)
`dodajSamochod`, `dodajRuchPoczatkowy`, `czyMoznaDodacAuto`, `losujWolneMiejsceNaPasie`, `znormalizujX`, itd.

### `private` — pola (linie 59–86)

| Linie | Pole | Znaczenie |
|---|---|---|
| 60 | `y` | Wysokość pasa |
| 62 | `kierunekRuchu` | LEWO/PRAWO |
| 64–72 | prędkość, spawn, odstępy | Parametry ruchu |
| 80 | `czyRuchStartowyZrobiony` | Flaga startu |
| 82–84 | gęstość, timer gęstości | Losowa dynamika |
| 86 | `samochody` | Lista aut na pasie |

**Implementacja:** `PasRuchu.cpp`

---

# 6. `include/Droga.h` — cała droga (46 linii)

---

### Linie 18–19 — klasa
```cpp
/** @brief Reprezentuje cala droge jako zbior pasow ruchu. */
```

### Linie 21–31 — `skonfiguruj` (z `@param` dla każdego argumentu)
Buduje pasy z `ustawienia.wierszePasow`. **Implementacja:** `Droga.cpp`

### Linie 33–38 — `public`
`aktualizuj`, `pobierzPasy`, `pobierzWierszePasow`

### `private` (linie 40–44)
`pasy` — lista `PasRuchu`; `wierszePasow` — numery wierszy.

---

# 7. `include/WykrywaczKolizji.h` — kolizje (35 linii)

---

### Linie 15–16 — klasa
```cpp
/** @brief Sprawdza kolizje zaby z samochodami na pasie drogi. */
```

### Linie 18–33 — `czyJestKolizja`
Jedyna publiczna metoda. `@return true` = kolizja.

| Parametr | Znaczenie |
|---|---|
| `zaba` | Pozycja gracza |
| `droga` | Wszystkie pasy i auta |
| `rozmiarPola` | Skala siatki [px] |
| `szerokoscSiatki`, `wysokoscSiatki` | Zarezerwowane (nieużywane w `.cpp`) |
| `ustawienia` | Lista pasów drogi |

**Implementacja:** `WykrywaczKolizji.cpp` | **Woła:** `Gra.cpp` — `sprawdzWarunkiKonca`

---

# 8. `include/Gra.h` — mózg gry (108 linii)

**Nie używa Qt** — `@details` mówi, że można testować bez GUI (`testy_logiki`).

---

### Linie 24–27 — klasa
```cpp
/**
 * @brief Serce logiki gry — stan, zegar, ruch i warunki konca.
 * @details Klasa nie uzywa Qt; moze byc testowana bez GUI (testy_logiki).
 */
```

### `public` — metody

| Linie | Metoda | Co robi |
|---|---|---|
| 30–31 | `Gra()` | Start: MENU, generator losowy |
| 32–33 | `rozpocznijGre` | Nowa gra, stan W_TRAKCIE |
| 34–35 | `przejdzDoMenu` | Powrót do menu |
| 37–42 | `ruch(dx, dy)` | Ruch żaby |
| 44–48 | `aktualizujKrok` | Co klatkę: auta, kolizje |
| 50–65 | gettery | stan, poziom, żaba, droga, czas, wymiary |

### `private` — metody (linie 67–75)
`sprawdzWarunkiKonca`, `finalizujOczekujacaWygrana`, `uruchomZegar`, `zatrzymajZegar`

### `private` — pola (linie 77–106)

| Linie | Pole | Znaczenie |
|---|---|---|
| 78 | `stan` | MENU / W_TRAKCIE / WYGRANA / PRZEGRANA |
| 80 | `poziomTrudnosci` | LATWY / SREDNI / TRUDNY |
| 82 | `ustawienia` | Parametry poziomu |
| 84–88 | `zaba`, `droga`, `wykrywaczKolizji` | Obiekty gry |
| 90–95 | zegar | `startCzasu`, `czasZatrzymania`, `zegarZatrzymany` |
| 97–104 | plansza | `szerokoscSiatki`=16, `wysokoscSiatki`, `rozmiarPola`, `generator` |
| 106 | `czekaNaKlatkeMety` | Opóźnienie ekranu wygranej o 1 klatkę |

**Implementacja:** `Gra.cpp`

---

# 9. `include/InterfejsGraficzny.h` — okno Qt (69 linii)

---

### Linie 22–25 — klasa
```cpp
/**
 * @brief Glowne okno gry — warstwa prezentacji (Qt Widgets).
 * @details Deleguje logike do obiektu Gra; rysuje menu, plansze i ekran koncowy.
 */
class InterfejsGraficzny : public QWidget {
```
**Dziedziczenie** po `QWidget` + **polimorfizm** przez `override`.

### `public` (linie 28–29)
Konstruktor — okno 960×720, timer 16 ms, przyciski.

### `protected` — zdarzenia Qt (linie 32–37)

| Linie | Metoda | Co robi |
|---|---|---|
| 33 | `paintEvent` | Rysuje ekran |
| 35 | `mousePressEvent` | Klik w menu / powrót |
| 37 | `keyPressEvent` | W/A/S/D, Escape |

### `private` — metody (linie 40–51)
`odswiezSymulacje`, `rysujMenu`, `rysujRozgrywke`, `rysujEkranKoncowy`, `rysujPrzycisk`, `tekstPoziomu`

### `private` — pola (linie 53–67)

| Linie | Pole | Znaczenie |
|---|---|---|
| 54 | `gra` | Logika gry |
| 56 | `timerPetli` | ~60 FPS |
| 58 | `zegarKlatek` | Delta czasu |
| 61–67 | `przyciskLatwy/Sredni/Trudny/Powrot` | Obszary kliknięć (`QRect`) |

Współrzędne przycisków ustawiane w konstruktorze: `InterfejsGraficzny.cpp` linie 28–31.

---

# Mapa: „Szukam kodu odpowiedzialnego za X”

| Chcę znaleźć… | Plik .h | Plik .cpp |
|---|---|---|
| Menu i wybór poziomu | `InterfejsGraficzny.h` | `InterfejsGraficzny.cpp` |
| Sterowanie W/A/S/D | `InterfejsGraficzny.h` | `InterfejsGraficzny.cpp` → `Gra::ruch` |
| Ruch żaby | `Zaba.h` | `Zaba.cpp` |
| Ruch samochodów | `Samochod.h`, `PasRuchu.h` | `Samochod.cpp`, `PasRuchu.cpp` |
| Spawn aut | `PasRuchu.h` | `PasRuchu.cpp` |
| Poziomy trudności | `UstawieniaTrudnosci.h` | `UstawieniaTrudnosci.cpp` |
| Droga i pasy | `Droga.h` | `Droga.cpp` |
| Kolizja | `WykrywaczKolizji.h` | `WykrywaczKolizji.cpp` |
| Wygrana / przegrana | `Gra.h` | `Gra.cpp` |
| Licznik czasu | `Gra.h` | `Gra.cpp` |
| Stany gry | `Typy.h` | `Gra.cpp` |
| Start aplikacji | — | `main.cpp` |
| Testy bez GUI | — | `tests/TestyLogiki.cpp` |
| Dokumentacja Doxygen | wszystkie `.h` | `doxygen Doxyfile` |

---

# Kolejność plików (od najprostszych)

1. `Typy.h` → 2. `UstawieniaTrudnosci.h` → 3. `Zaba.h` → 4. `Samochod.h` → 5. `PasRuchu.h` → 6. `Droga.h` → 7. `WykrywaczKolizji.h` → 8. `Gra.h` → 9. `InterfejsGraficzny.h`

---

*Część 1: pliki `.h`. Część 2: `PRZEWODNIK_PLIKI_CPP.md`*
