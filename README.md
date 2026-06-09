# Zaba na ulicy (C++ + GUI)

Gra dziala w oknie GUI (Qt Widgets) i realizuje wymagania projektu:
- menu glowne z wyborem poziomu (`Latwy`, `Sredni`, `Trudny`),
- sterowanie zaba (`W/A/S/D`),
- automatyczny ruch samochodow,
- kolizja = przegrana, dotarcie do mety = wygrana,
- ekran koncowy z przyciskiem powrotu do menu.

## Uklad poziomow
- `Latwy`: 2 ulice (2 pasy + 2 pasy), umiarkowany ruch.
- `Sredni`: 2 drogi po 4 pasy, pomiedzy nimi bezpieczna strefa trawy (`safe space`).
- `Trudny`: 2 drogi po 6 pasow, wiecej aut i wyzsza dynamika ruchu.

Samochody startuja od razu po rozpoczeciu gry, poruszaja sie losowo (predkosc/gestosc), ale
nie powinny najezdzac na siebie na tym samym pasie.

## Struktura plikow
- `main.cpp` - tylko uruchomienie aplikacji.
- `Gra.h/.cpp` - glowna petla, stany gry i obsluga zdarzen.
- `InterfejsGraficzny.h/.cpp` - rysowanie GUI.
- `Zaba.h/.cpp`, `Samochod.h/.cpp`, `PasRuchu.h/.cpp`, `Droga.h/.cpp` - model i ruch obiektow.
- `WykrywaczKolizji.h/.cpp` - sprawdzanie zderzen.
- `UstawieniaTrudnosci.h/.cpp` - parametry poziomow.
- `Typy.h` - enumy (stan gry, trudnosc, kierunek).
- Licznik czasu jest w `Gra` (bez osobnego pliku).

## Budowanie i uruchamianie
Wymagane: zainstalowane Qt 6 (modul `Widgets`).

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/zaba_na_ulicy
```

Jesli CMake nie znajduje Qt, podaj sciezke do instalacji:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="/sciezka/do/Qt/6.x.x/macos"
cmake --build build
```

Dla instalacji z Homebrew dziala:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH="/usr/local/opt/qt"
cmake --build build
ctest --test-dir build --output-on-failure
```

## Dokumentacja projektu (oddanie na zajecia)

| Plik | Zawartosc |
|---|---|
| `docs/DOKUMENTACJA_OPISOWA.md` | Dokumentacja opisowa: zalozenia, wymagania, GUI, diagram klas, plan testow |
| `docs/SPRAWDZENIE_WYMAGAN.md` | Checklist zgodnosci z wymaganiami PDF |
| `docs/PRZEWODNIK_PLIKI_H.md` | Przewodnik po plikach naglowkowych |
| `docs/PRZEWODNIK_PLIKI_CPP.md` | Przewodnik po plikach zrodlowych |
| `docs/screenshots/` | Zrzuty ekranu (do uzupelnienia przed prezentacja) |
| `Doxyfile` | Konfiguracja dokumentacji Doxygen |

Generowanie dokumentacji Doxygen:

```bash
doxygen Doxyfile
open docs/doxygen/html/index.html
```

## Uwagi
- Detektor kolizji odswieza sie co `16 ms` (`~60 Hz`) - krotki krok odpowiedni dla gry mobilnej.
- Kod ma polskie nazwy klas i metody oraz komentarze opisujace odpowiedzialnosc sekcji.