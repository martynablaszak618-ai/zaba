#pragma once

#include <chrono>

// Prosty licznik czasu rozgrywki do paska statusu.
class ZegarGry {
public:
    void start();
    void stop();
    int pobierzSekundy() const;

private:
    std::chrono::steady_clock::time_point startCzasu = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point czasZatrzymania = std::chrono::steady_clock::now();
    bool zatrzymany = false;
};
