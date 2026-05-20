// Ta dyrektywa gwarantuje pojedyncze dolaczenie naglowka.
#pragma once

// Uzywamy biblioteki czasu z C++.
#include <chrono>

// Klasa mierzy czas trwania rozgrywki.
class ZegarGry {
public:
    // Rozpoczyna (lub restartuje) pomiar czasu.
    void start();
    // Zatrzymuje pomiar czasu.
    void stop();
    // Zwraca liczbe sekund od startu do teraz (albo do zatrzymania).
    int pobierzSekundy() const;

private:
    // Znacznik chwili, gdy rozgrywka wystartowala.
    std::chrono::steady_clock::time_point startCzasu = std::chrono::steady_clock::now();
    // Znacznik chwili, gdy rozgrywka zostala zatrzymana.
    std::chrono::steady_clock::time_point czasZatrzymania = std::chrono::steady_clock::now();
    // Flaga informuje, czy zegar juz zostal zatrzymany.
    bool zatrzymany = false;
};
