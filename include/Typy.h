#pragma once

// Stany aplikacji, zgodnie z przeplywem: menu -> gra -> ekran koncowy.
enum class StanGry {
    MENU,
    W_TRAKCIE,
    WYGRANA,
    PRZEGRANA
};

// Poziom trudnosci wybierany przez gracza w menu.
enum class PoziomTrudnosci {
    LATWY,
    SREDNI,
    TRUDNY
};

// Kierunek ruchu samochodu na danym pasie.
enum class Kierunek {
    LEWO,
    PRAWO
};
