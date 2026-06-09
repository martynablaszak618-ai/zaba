# Sprawdzenie zgodności z wymaganiami projektu (prog2_projekt_opis.pdf)

Data sprawdzenia: czerwiec 2025  
Projekt: **Żaba na ulicy**

---

## Wymagania z PDF + wiadomości prowadzącego

| # | Wymaganie | Status | Uwagi |
|---|---|---|---|
| 1 | Program obiektowy w C++ | ✅ | 9 klas, enumy, kompozycja |
| 2 | Graficzny interfejs użytkownika | ✅ | Qt 6 Widgets |
| 3 | 4 paradygmaty OOP | ✅ | Enkapsulacja, abstrakcja, dziedziczenie, polimorfizm |
| 4 | Dobre praktyki (moduły, notacja, dokumentacja) | ✅ | `.h`/`.cpp`, CMake, Doxygen |
| 5 | Odporność na sytuacje wyjątkowe | ⚠️ częściowo | Programowanie defensywne, brak `try/catch` |
| 6 | Oddzielenie logiki od GUI | ✅ | `Gra` bez Qt |
| 7 | Logika z interfejsem testowym tekstowym | ⚠️ częściowo | `testy_logiki` (CTest), nie interaktywna konsola |
| 8 | Źródła głównego projektu | ✅ | `src/`, `include/` |
| 9 | Testy | ✅ | `tests/TestyLogiki.cpp` |
| 10 | Dokumentacja Doxygen | ✅ po uzupełnieniu | `Doxyfile` + komentarze w `.h` |
| 11 | Dokumentacja opisowa | ✅ | `docs/DOKUMENTACJA_OPISOWA.md` |
| 12 | Założenia projektu | ✅ | Sekcja 1 dokumentacji opisowej |
| 13 | Model wymagań | ✅ | Sekcja 2 |
| 14 | Sytuacje wyjątkowe | ✅ | Sekcja 3 |
| 15 | Plan testów | ✅ | Sekcja 6 |
| 16 | Koncepcja GUI / opis GUI | ✅ | Sekcja 4 |
| 17 | Diagram klas | ✅ | Sekcja 5 (Mermaid) |
| 18 | Plany vs realizacja | ✅ | Tabele „etap 0 vs final” |
| 19 | Zrzuty ekranu | ❌ do zrobienia | Folder `docs/screenshots/` — uzupełnij przed prezentacją |

---

## Legenda

- ✅ — spełnione
- ⚠️ — spełnione częściowo (warto omówić na prezentacji)
- ❌ — wymaga działania studenta

---

## Co zrobić przed czwartkiem (checklist)

- [ ] Uruchomić grę i zrobić 5–6 zrzutów ekranu → `docs/screenshots/`
- [ ] Uruchomić `ctest` i zapisać wynik (zrzut terminala lub `.txt`)
- [ ] Wygenerować dokumentację Doxygen: `doxygen Doxyfile` → folder `docs/doxygen/`
- [ ] Przećwiczyć prezentację na żywo (menu → gra → wygrana/przegrana)
- [ ] Upewnić się, że obie osoby w zespole znają cały kod (pytania prowadzącego)

---

## Rekomendowane polecenia na prezentację

```bash
# Budowanie
cmake -S . -B build -DCMAKE_PREFIX_PATH="/usr/local/opt/qt"
cmake --build build

# Testy
ctest --test-dir build --output-on-failure

# Gra
./build/zaba_na_ulicy

# Dokumentacja Doxygen (jeśli zainstalowany: brew install doxygen)
doxygen Doxyfile
open docs/doxygen/html/index.html
```
