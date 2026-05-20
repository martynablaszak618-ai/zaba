// Dolaczamy deklaracje klasy ZegarGry.
#include "ZegarGry.h"

// Rozpoczyna pomiar czasu od aktualnej chwili.
void ZegarGry::start() {
    // Zapamietujemy punkt startowy.
    startCzasu = std::chrono::steady_clock::now();
    // Flaga mowi, ze zegar znowu pracuje.
    zatrzymany = false;
}

// Zatrzymuje pomiar czasu.
void ZegarGry::stop() {
    // Zatrzymujemy tylko raz, zeby nie nadpisywac czasu zatrzymania.
    if (!zatrzymany) {
        // Zapamietujemy moment stop.
        czasZatrzymania = std::chrono::steady_clock::now();
        // Flaga mowi, ze zegar jest zatrzymany.
        zatrzymany = true;
    }
}

// Zwraca ilosc sekund od startu.
int ZegarGry::pobierzSekundy() const {
    // Jesli zegar stoi, koncem jest czas zatrzymania; w przeciwnym razie "teraz".
    const auto koniec = zatrzymany ? czasZatrzymania : std::chrono::steady_clock::now();
    // Obliczamy roznice czasu i zamieniamy na cale sekundy.
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::seconds>(koniec - startCzasu).count());
}
