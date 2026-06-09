# Przewodnik po plikach .h — gra „Żaba na ulicy”

Ten dokument wyjaśnia **każdą linijkę** w plikach nagłówkowych (`.h`) w najprostszy możliwy sposób.  
Plik `.h` to jak **spis treści / instrukcja** — mówi, *co dana część programu potrafi*, ale prawdziwa praca dzieje się w plikach `.cpp` o tej samej nazwie.

---

## Jak czytać ten przewodnik

| Słowo w kodzie | Co to znaczy po ludzku |
|---|---|
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

**Gdzie szukać działania?**  
Nagłówek (`.h`) mówi *co jest*. Implementacja (`.cpp`) mówi *jak to działa linijka po linijce*.

---

# 1. `include/Typy.h` — podstawowe „etykiety” gry

Ten plik **nie rysuje nic** i **nie porusza niczym**.  
To słownik nazw — program wie, że gra może być w menu, w trakcie, po wygranej itd.

---

### Linia 1
```cpp
// Ta dyrektywa sprawia, ze ten plik zostanie dolaczony tylko raz.
```
**Komentarz** — wyjaśnienie dla programisty. Kompilator tego nie wykonuje.

### Linia 2
```cpp
#pragma once
```
**Zabezpieczenie.** Gdy wiele plików chce wczytać `Typy.h`, ten plik trafi do programu tylko jeden raz. Bez tego mogłyby powstać błędy „zdefiniowano dwa razy”.

### Linia 3
*(pusta)*  
Oddzielenie wizualne — nic nie robi.

### Linia 4
```cpp
// Ten enum opisuje, na jakim ekranie/stanie aktualnie jest gra.
```
Komentarz: za chwilę zdefiniujemy **stan gry** — czy widzisz menu, czy grasz, czy skończyłaś.

### Linie 5–10
```cpp
enum class StanGry {
    MENU,       // Gracz widzi menu glowne i wybiera poziom.
    W_TRAKCIE,  // Trwa aktywna rozgrywka.
    WYGRANA,    // Gra zakonczona sukcesem.
    PRZEGRANA   // Gra zakonczona porazka (np. kolizja).
};
```

**`enum class StanGry`** — lista 4 możliwych „trybów” gry:

| Wartość | Znaczenie | Gdzie to widać w grze |
|---|---|---|
| `MENU` | Ekran startowy | Przyciski Łatwy / Średni / Trudny |
| `W_TRAKCIE` | Normalna rozgrywka | Żaba, droga, samochody |
| `WYGRANA` | Dotarłaś na metę | Ekran „wygrana” |
| `PRZEGRANA` | Kolizja z autem | Ekran „przegrana” |

**Gdzie to się zmienia w kodzie?**  
→ `Gra.h` / `Gra.cpp` — pole `stan` i funkcje `rozpocznijGre`, `sprawdzWarunkiKonca`  
→ `InterfejsGraficzny.cpp` — rysuje menu albo grę w zależności od stanu

### Linia 11
*(pusta)*

### Linia 12
```cpp
// Ten enum przechowuje poziom trudnosci wybrany przez gracza.
```

### Linie 13–17
```cpp
enum class PoziomTrudnosci {
    LATWY,   // Najlatwiejsza konfiguracja.
    SREDNI,  // Srednia konfiguracja.
    TRUDNY   // Najtrudniejsza konfiguracja.
};
```

**Poziom trudności** — wybór z menu:

| Wartość | Co zmienia w grze |
|---|---|
| `LATWY` | Mniej pasów, wolniejsze auta |
| `SREDNI` | Więcej pasów, „bezpieczna trawa” między drogami |
| `TRUDNY` | Najwięcej pasów, szybsze i gęstsze auta |

**Gdzie to ustawia liczby?**  
→ `UstawieniaTrudnosci.cpp` — funkcja `pobierzUstawieniaTrudnosci`

### Linia 18
*(pusta)*

### Linia 19
```cpp
// Ten enum mowi, w ktora strone porusza sie samochod.
```

### Linie 20–23
```cpp
enum class Kierunek {
    LEWO,   // Ruch samochodu w lewo.
    PRAWO   // Ruch samochodu w prawo.
};
```

**Kierunek samochodu** — każdy pas ma auta jadące w lewo albo w prawo (jak w Froggerze).

**Gdzie to używane?**  
→ `Samochod.cpp` — przy ruchu auta  
→ `PasRuchu.cpp` — przy tworzeniu pasa  
→ `Droga.cpp` — przy układaniu pasów na planszy

---

# 2. `include/UstawieniaTrudnosci.h` — liczby opisujące poziom

Ten plik mówi: **jakie liczby opisują dany poziom trudności** (ile wierszy, jak szybko jadą auta itd.).

---

### Linia 1
Komentarz o `#pragma once`.

### Linia 2
```cpp
#pragma once
```
Jak wyżej — wczytaj raz.

### Linia 3
*(pusta)*

### Linia 4–5
```cpp
// Potrzebujemy enumu PoziomTrudnosci z typow wspolnych.
#include "Typy.h"
```
Bierzemy z `Typy.h` listę `LATWY / SREDNI / TRUDNY`.

### Linia 7–8
```cpp
// Potrzebujemy wektora do listy numerow wierszy drogowych.
#include <vector>
```
`vector` = **dynamiczna lista** (np. lista numerów wierszy, które są drogą: 2, 3, 4…).

### Linia 10
```cpp
// Ta struktura trzyma wszystkie liczby opisujace poziom trudnosci.
```

### Linie 11–28 — struktura `UstawieniaTrudnosci`

To **pudełko na ustawienia** jednego poziomu:

| Linia | Pole | Co to znaczy | Przykład |
|---|---|---|---|
| 13 | `wysokoscSiatki` | Ile wierszy ma plansza (pionowo) | 5, 12, 16… |
| 15 | `wierszePasow` | **Które wiersze** to asfalt z autami | np. wiersz 2 i 3 |
| 17 | `predkoscSamochodow` | Jak szybko jadą auta (piksele/sek) | 100.0 |
| 19 | `interwalTworzeniaAuta` | Co ile sekund pojawia się nowe auto | 1.2 s |
| 21 | `minimalnyOdstepAut` | Minimalna odległość między autami | 150 px |
| 23 | `autaNaStarcieMin` | Min. aut na pasie na starcie | 1 |
| 25 | `autaNaStarcieMax` | Max. aut na pasie na starcie | 2 |
| 27 | `maksAutNaPasie` | Ile aut max. może być naraz na jednym pasie | 3 |

**`= 5`, `= 100.0f` itd.** — wartości domyślne, gdyby ktoś nie ustawił inaczej.

**Gdzie te liczby są wypełniane?**  
→ `UstawieniaTrudnosci.cpp` — funkcja `pobierzUstawieniaTrudnosci` (tu jest różnica Łatwy/Średni/Trudny)

### Linie 30–31
```cpp
// Funkcja zwraca komplet ustawien dla wybranego poziomu trudnosci.
UstawieniaTrudnosci pobierzUstawieniaTrudnosci(PoziomTrudnosci poziom);
```
**Deklaracja funkcji** — „daj mi poziom (ŁATWY/ŚREDNI/TRUDNY), a zwrócę cały zestaw liczb”.  
**Implementacja:** `UstawieniaTrudnosci.cpp`

### Linie 33–34
```cpp
int pobierzOstatniPasDrogi(const UstawieniaTrudnosci& ustawienia);
```
Zwraca numer **ostatniego wiersza, który jest drogą** — potrzebne, żeby wiedzieć, gdzie kończy się asfalt.

### Linie 36–37
```cpp
int pobierzWierszMety(const UstawieniaTrudnosci& ustawienia);
```
Zwraca numer wiersza **mety** (zielone pole za drogą).  
**Gdzie sprawdzana wygrana?** → `Gra.cpp` — `sprawdzWarunkiKonca`

### Linie 39–40
```cpp
bool czyWierszJestPasem(int wiersz, const UstawieniaTrudnosci& ustawienia);
```
Odpowiada **tak/nie**: czy dany wiersz (np. wiersz 3) to pas z autami.

---

# 3. `include/Zaba.h` — gracz (żaba)

Opisuje **tylko żabę** — gdzie stoi i jak się rusza. Nie rysuje jej — to robi `InterfejsGraficzny.cpp`.

---

### Linie 1–2
Komentarz + `#pragma once`.

### Linie 4–5
```cpp
// Ta klasa reprezentuje gracza (czyli abe) i jej ruch.
class Zaba {
```
**Klasa Żaba** — obiekt gracza.

### `public` — co inne pliki mogą wywołać

| Linie | Metoda | Co robi | Gdzie wywoływane |
|---|---|---|---|
| 8 | `ustawPozycjeStartowa(x, y)` | Stawia żabę na starcie (dół planszy) | `Gra.cpp` — `rozpocznijGre` |
| 11 | `ruch(dx, dy, krok)` | Przesuwa żabę o pola: W=góra, S=dół, A=lewo, D=prawo | `Gra.cpp` — `ruch` |
| 14 | `ograniczDoPlanszy(szer, wys)` | Nie pozwala wyjść poza krawędzie | `Gra.cpp` — po ruchu |
| 17 | `pobierzX()` | Aktualna kolumna żaby | Rysowanie, kolizje |
| 19 | `pobierzY()` | Aktualny wiersz żaby | Rysowanie, kolizje, meta |

**`krok = 1`** — domyślnie rusza się o 1 pole; można podać inny krok.

### `private` — wewnętrzne dane żaby

| Linia | Pole | Znaczenie |
|---|---|---|
| 23 | `int x = 0` | Pozycja w poziomie (kolumna) |
| 25 | `int y = 0` | Pozycja w pionie (wiersz) |

**Implementacja ruchu:** `Zaba.cpp`  
**Sterowanie klawiszami W/A/S/D:** `InterfejsGraficzny.cpp` → `keyPressEvent` → `Gra::ruch`

---

# 4. `include/Samochod.h` — jedno auto

Jeden samochód na jednym pasie. Auta **same się poruszają** — gracz nimi nie steruje.

---

### Linie 1–5
Komentarz, `#pragma once`, `#include "Typy.h"` (dla `Kierunek`).

### Linie 8–12 — konstruktor
```cpp
Samochod(float xStart, float yStale, float predkosc, Kierunek kierunek, float szerokosc,
         int wariantKoloru);
```
Tworzy nowe auto z parametrami:
- **xStart** — gdzie zaczyna w poziomie
- **yStale** — na której wysokości (pasie) jedzie (Y się nie zmienia)
- **predkosc** — szybkość
- **kierunek** — LEWO lub PRAWO
- **szerokosc** — szerokość planszy (do „zawijania” auta na drugi brzeg)
- **wariantKoloru** — który kolor narysować (0, 1, 2…)

**Tworzenie aut:** `PasRuchu.cpp` — `dodajSamochod`

### Linie 14–15 — `aktualizuj`
```cpp
void aktualizuj(float deltaSekundy, float mnoznikTempa);
```
Co klatkę przesuwa auto. `deltaSekundy` = ile czasu minęło od ostatniej klatki.  
**Implementacja:** `Samochod.cpp`

### Linie 17–24 — gettery i setter
| Metoda | Po co |
|---|---|
| `pobierzX()`, `pobierzY()` | Pozycja do rysowania i kolizji |
| `pobierzWariantKoloru()` | Kolor auta na ekranie |
| `ustawX(nowyX)` | Korekta pozycji (np. po zawinięciu pasa) |

### `private` — pola wewnętrzne (linie 27–38)

| Pole | Znaczenie |
|---|---|
| `x`, `y` | Pozycja (float = dokładniejsza niż int) |
| `predkoscPikseleNaSek` | Szybkość jazdy |
| `kierunekRuchu` | LEWO / PRAWO |
| `szerokoscPlanszyPiksele` | Do obliczeń zawijania |
| `wariantKoloru` | Numer koloru |

---

# 5. `include/PasRuchu.h` — jeden pas drogi z autami

**Pas** = jeden poziomy „pasek” asfaltu, po którym jadą samochody w jednym kierunku.  
Ten plik zarządza **wszystkimi autami na jednym pasie**.

---

### Linie 1–10
`#pragma once`, `#include "Samochod.h"`, `<random>`, `<vector>`.

### Linie 16–24 — konstruktor `PasRuchu`
Przyjmuje **wszystkie parametry pasa** z ustawień trudności:
- `yPasa` — wysokość pasa na ekranie
- `kierunek` — lewo/prawo
- `predkoscAut`, `interwalTworzeniaAut`, `minimalnyOdstepAut`
- `autaNaStarcieMin/Max`, `maksAutNaPasie`
- `szerokoscPlanszyPiksele`

**Tworzenie pasów:** `Droga.cpp` — `skonfiguruj`

### `public` — główne operacje

| Linie | Metoda | Co robi |
|---|---|---|
| 27 | `aktualizuj(...)` | Rusza auta, liczy spawn, zmienia gęstość |
| 29 | `pobierzSamochody()` | Lista aut (do rysowania i kolizji) |
| 31 | `czyPasMaWidoczneAuto()` | Czy na pasie widać choć jedno auto |
| 33 | `utrzymijWidocznyRuch(...)` | Jeśli pas pusty — dokłada auto, żeby nie było pusto |

### `private` — metody pomocnicze (linie 36–53)

| Metoda | Po co |
|---|---|
| `dodajSamochod()` | Wstawia nowe auto na pas |
| `dodajRuchPoczatkowy()` | Na starcie gry ustawia pierwsze auta |
| `czyMoznaDodacAuto()` | Czy jest miejsce (odstęp od innych aut) |
| `losujWolneMiejsceNaPasie()` | Losuje X, gdzie auto nie koliduje |
| `losujDodatkoweOpoznienie()` | Losowe opóźnienie między spawnami |
| `znormalizujX()` | „Zawija” pozycję X wokół planszy |
| `normalizujPozycjeAut()` | Naprawia auta, które wyszły poza zakres |
| `ograniczXNaPasie()` | Trzyma X w sensownym zakresie |
| `czyOdlegloscWystarczajaca()` | Czy dwa auta nie są za blisko |

### `private` — pola (linie 55–82)

| Pole | Znaczenie |
|---|---|
| `y` | Wysokość pasa |
| `kierunekRuchu` | Kierunek aut na tym pasie |
| `predkoscSamochodow` | Bazowa prędkość |
| `interwalSpawnu` | Jak często nowe auto |
| `szerokoscPlanszy` | Szerokość do zawijania |
| `licznikDoSpawnu` | Odliczanie do następnego auta |
| `minimalnyOdstep` | Min. dystans między autami |
| `autaStartMin/Max` | Ile aut na start |
| `maksAutNaPasie` | Limit aut |
| `czyRuchStartowyZrobiony` | Czy startowy zestaw aut już dodany |
| `wspolczynnikGestosciRuchu` | Czasem auta jadą szybciej/wolniej (losowo) |
| `czasDoZmianyGestosci` | Kiedy zmienić gęstość |
| `samochody` | **Lista wszystkich aut na tym pasie** |

**Cała logika ruchu aut na jednym pasie:** `PasRuchu.cpp`

---

# 6. `include/Droga.h` — cała droga (wiele pasów)

**Droga** = zbiór wszystkich pasów ruchu na planszy. Łączy pasy w jedną całość.

---

### Linie 1–12
Include: `PasRuchu.h`, `UstawieniaTrudnosci.h`, `<random>`, `<vector>`.

### Linie 18–21 — `skonfiguruj`
```cpp
void skonfiguruj(const UstawieniaTrudnosci& ustawienia,
                 float szerokoscPlanszy,
                 float wysokoscPlanszy,
                 float wysokoscPola);
```
**Buduje drogę** na podstawie poziomu trudności i rozmiaru okna.  
Tworzy tyle pasów, ile mówi `wierszePasow` w ustawieniach.  
**Implementacja:** `Droga.cpp`

### Linie 23–28 — pozostałe `public`

| Metoda | Co robi |
|---|---|
| `aktualizuj` | Aktualizuje **każdy pas** naraz |
| `pobierzPasy` | Zwraca listę pasów (do rysowania/kolizji) |
| `pobierzWierszePasow` | Numery wierszy siatki, które są drogą |

### `private` (linie 31–34)

| Pole | Znaczenie |
|---|---|
| `pasy` | Lista obiektów `PasRuchu` |
| `wierszePasow` | Które wiersze planszy to asfalt |

**Wywołanie:** `Gra.cpp` — `aktualizujKrok` woła `droga.aktualizuj(...)`

---

# 7. `include/WykrywaczKolizji.h` — czy żaba trafiła w auto

Bardzo wąski plik: **tylko sprawdzanie zderzeń**. Nic nie rysuje, nic nie rusza.

---

### Linie 1–9
Include: `Droga.h`, `UstawieniaTrudnosci.h`, `Zaba.h`.

### Linie 11–12
```cpp
// Ta klasa odpowiada tylko za wykrywanie kolizji zaby z autem.
class WykrywaczKolizji {
```

### Linie 15–20 — jedyna publiczna metoda
```cpp
bool czyJestKolizja(const Zaba& zaba,
                    const Droga& droga,
                    float rozmiarPola,
                    int szerokoscSiatki,
                    int wysokoscSiatki,
                    const UstawieniaTrudnosci& ustawienia) const;
```

**Wejście:** pozycja żaby, wszystkie pasy z autami, rozmiar pola, wymiary planszy, ustawienia.  
**Wyjście:** `true` = kolizja (przegrana), `false` = bezpiecznie.

**Implementacja (jak dokładnie liczy kolizję):** `WykrywaczKolizji.cpp`  
**Kto woła:** `Gra.cpp` — `sprawdzWarunkiKonca`

**Uwaga z README:** kolizja odświeża się co ~16 ms (~60 Hz).

---

# 8. `include/Gra.h` — „mózg” gry (bez rysowania)

To **najważniejszy plik logiki**. Łączy żabę, drogę, kolizje, stan gry i czas.  
**Nie wie nic o oknie Qt** — działa „w tle”; GUI tylko go pyta i daje rozkazy.

---

### Linie 1–18 — include
- `Droga.h` — auta i pasy
- `Typy.h` — stany, trudność, kierunek
- `UstawieniaTrudnosci.h` — liczby poziomu
- `WykrywaczKolizji.h` — kolizje
- `Zaba.h` — gracz
- `<chrono>` — pomiar czasu gry
- `<random>` — losowość (auta, gęstość)

### `public` — co GUI i reszta programu robi z grą

| Linie | Metoda | Co robi | Kiedy |
|---|---|---|---|
| 24 | `Gra()` | Konstruktor — startowy stan MENU | Przy starcie aplikacji |
| 26 | `rozpocznijGre(poziom)` | Nowa gra: ustawia poziom, żabę, drogę, stan W_TRAKCIE | Klik w Łatwy/Średni/Trudny |
| 28 | `przejdzDoMenu()` | Wraca do MENU | Przycisk powrotu |
| 31 | `ruch(dx, dy)` | Rusza żabą | W/A/S/D |
| 34 | `aktualizujKrok(delta)` | Co klatkę: auta, kolizje, meta, zegar | Timer w GUI |
| 37 | `pobierzStan()` | MENU / W_TRAKCIE / WYGRANA / PRZEGRANA | Co narysować |
| 39 | `pobierzPoziomTrudnosci()` | Aktualny poziom | Tekst na ekranie |
| 41 | `pobierzZabe()` | Dane żaby do rysowania | `rysujRozgrywke` |
| 43 | `pobierzDroge()` | Pasy i auta do rysowania | `rysujRozgrywke` |
| 45 | `pobierzCzasSekundy()` | Ile sekund grasz | HUD / ekran końcowy |
| 47–49 | `pobierzSzerokosc/WysokoscSiatki()` | Wymiary planszy | Rysowanie siatki |
| 51 | `pobierzRozmiarPola()` | Wielkość jednego kwadratu w px | Skalowanie |

### `private` — wewnętrzna logika

| Linie | Metoda | Co robi |
|---|---|---|
| 55 | `sprawdzWarunkiKonca()` | Kolizja → PRZEGRANA; meta → WYGRANA |
| 57 | `finalizujOczekujacaWygrana()` | Opóźnia ekran wygranej o 1 klatkę |
| 59 | `uruchomZegar()` | Start licznika czasu |
| 61 | `zatrzymajZegar()` | Stop przy wygranej/przegranej |

### `private` — pola stanu gry (linie 63–92)

| Pole | Znaczenie |
|---|---|
| `stan` | MENU / W_TRAKCIE / WYGRANA / PRZEGRANA |
| `poziomTrudnosci` | LATWY / SREDNI / TRUDNY |
| `ustawienia` | Wszystkie liczby poziomu |
| `zaba` | Obiekt gracza |
| `droga` | Wszystkie pasy i auta |
| `wykrywaczKolizji` | Sprawdzanie zderzeń |
| `startCzasu`, `czasZatrzymania`, `zegarZatrzymany` | Licznik czasu rozgrywki |
| `szerokoscSiatki`, `wysokoscSiatki` | Rozmiar planszy (domyślnie 16×12) |
| `generator` | Losowość |
| `rozmiarPola` | 60 px na pole (domyślnie) |
| `czekaNaKlatkeMety` | Flaga opóźnienia wygranej |

**Cała implementacja:** `Gra.cpp`

---

# 9. `include/InterfejsGraficzny.h` — okno gry (to, co widzisz)

Łączy **Qt (okno, mysz, klawiatura, rysowanie)** z **logiką `Gra`**.  
To tutaj jest menu, plansza, przyciski i obsługa W/A/S/D.

---

### Linie 1–16
- `#include "Gra.h"` — mózg gry
- `QElapsedTimer` — mierzy czas między klatkami
- `QRect` — prostokąt (np. obszar przycisku)
- `QString` — tekst
- `QTimer` — „budzik” odświeżający grę co chwilę
- `QWidget` — bazowa klasa okna

### Linia 19
```cpp
class InterfejsGraficzny : public QWidget {
```
**Okno aplikacji** — dziedziczy po `QWidget` (standardowe okno Qt).

### `public` (linie 21–22)
```cpp
explicit InterfejsGraficzny(QWidget* rodzic = nullptr);
```
Konstruktor — tworzy okno, timer, podpina zdarzenia.  
**Wywołanie:** `main.cpp` — tworzy to okno i je pokazuje.

### `protected` — reakcje Qt na zdarzenia użytkownika

| Linie | Metoda | Kiedy się wywołuje | Co robi |
|---|---|---|---|
| 26 | `paintEvent` | Qt chce przerysować okno | Rysuje menu / grę / ekran końcowy |
| 28 | `mousePressEvent` | Klik myszą | Wybór poziomu, powrót do menu |
| 30 | `keyPressEvent` | Naciśnięty klawisz | W/A/S/D → ruch żaby |

**Implementacja rysowania i kliknięć:** `InterfejsGraficzny.cpp`

### `private` — metody pomocnicze GUI

| Metoda | Co rysuje / robi |
|---|---|
| `odswiezSymulacje()` | Liczy delta czasu → `gra.aktualizujKrok` → `update()` |
| `rysujMenu` | Tytuł + 3 przyciski poziomu |
| `rysujRozgrywke` | Tło, trawa, droga, auta, żaba, czas |
| `rysujEkranKoncowy` | Nakładka wygrana/przegrana + przycisk powrotu |
| `rysujPrzycisk` | Jeden prostokąt z napisem |
| `tekstPoziomu` | „Łatwy” / „Średni” / „Trudny” z enuma |

### `private` — pola (linie 46–60)

| Pole | Znaczenie |
|---|---|
| `gra` | **Obiekt całej logiki** — serce pod spodem GUI |
| `timerPetli` | Timer ~60 FPS — co tick: `odswiezSymulacje` |
| `zegarKlatek` | Mierzy `deltaSekundy` między klatkami |
| `przyciskLatwy` | Gdzie na ekranie kliknąć „Łatwy” |
| `przyciskSredni` | Obszar „Średni” |
| `przyciskTrudny` | Obszar „Trudny” |
| `przyciskPowrot` | Obszar „Powrót do menu” na ekranie końcowym |

**Uwaga:** współrzędne przycisków ustawiane są przy rysowaniu w `.cpp` — nagłówek tylko **deklaruje**, że takie pola istnieją.

---

# Mapa: „Szukam kodu odpowiedzialnego za X”

| Chcę znaleźć… | Plik .h (deklaracja) | Plik .cpp (działanie) |
|---|---|---|
| Menu i wybór poziomu | `InterfejsGraficzny.h` (`rysujMenu`, przyciski) | `InterfejsGraficzny.cpp` |
| Sterowanie W/A/S/D | `InterfejsGraficzny.h` (`keyPressEvent`) | `InterfejsGraficzny.cpp` → `Gra::ruch` |
| Ruch żaby | `Zaba.h` | `Zaba.cpp` |
| Ruch samochodów | `Samochod.h`, `PasRuchu.h` | `Samochod.cpp`, `PasRuchu.cpp` |
| Pojawianie się aut | `PasRuchu.h` (spawn, odstępy) | `PasRuchu.cpp` |
| Układ pasów (łatwy/średni/trudny) | `UstawieniaTrudnosci.h` | `UstawieniaTrudnosci.cpp` |
| Budowa całej drogi | `Droga.h` | `Droga.cpp` |
| Kolizja z autem | `WykrywaczKolizji.h` | `WykrywaczKolizji.cpp` |
| Wygrana (meta) | `Gra.h` (`sprawdzWarunkiKonca`) | `Gra.cpp` + `UstawieniaTrudnosci.cpp` (`pobierzWierszMety`) |
| Przegrana | `Gra.h`, `WykrywaczKolizji.h` | `Gra.cpp`, `WykrywaczKolizji.cpp` |
| Licznik czasu | `Gra.h` (zegar w polach) | `Gra.cpp` |
| Stany MENU/W_TRAKCIE/WYGRANA | `Typy.h` (`StanGry`) | `Gra.cpp` |
| Start aplikacji | — | `main.cpp` |

---

# Kolejność plików (od najprostszych do najważniejszych)

1. **`Typy.h`** — słownik nazw (stany, poziomy, kierunki)  
2. **`UstawieniaTrudnosci.h`** — liczby poziomów  
3. **`Zaba.h`** — gracz  
4. **`Samochod.h`** — jedno auto  
5. **`PasRuchu.h`** — jeden pas z wieloma autami  
6. **`Droga.h`** — wszystkie pasy  
7. **`WykrywaczKolizji.h`** — kolizje  
8. **`Gra.h`** — cała logika  
9. **`InterfejsGraficzny.h`** — okno i rysowanie  

---

*Dokument wygenerowany dla projektu „Żaba na ulicy”. Część 1: pliki `.h`. W kolejnej części można opisać pliki `.cpp` z tą samą dokładnością.*
