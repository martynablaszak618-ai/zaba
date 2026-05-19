#include "ZegarGry.h"

void ZegarGry::start() {
    startCzasu = std::chrono::steady_clock::now();
    zatrzymany = false;
}

void ZegarGry::stop() {
    if (!zatrzymany) {
        czasZatrzymania = std::chrono::steady_clock::now();
        zatrzymany = true;
    }
}

int ZegarGry::pobierzSekundy() const {
    const auto koniec = zatrzymany ? czasZatrzymania : std::chrono::steady_clock::now();
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::seconds>(koniec - startCzasu).count());
}
