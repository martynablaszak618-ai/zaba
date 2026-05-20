// Ta dyrektywa sprawia, ze ten plik zostanie dolaczony tylko raz.
#pragma once

// Ten enum opisuje, na jakim ekranie/stanie aktualnie jest gra.
enum class StanGry {
    MENU,       // Gracz widzi menu glowne i wybiera poziom.
    W_TRAKCIE,  // Trwa aktywna rozgrywka.
    WYGRANA,    // Gra zakonczona sukcesem.
    PRZEGRANA   // Gra zakonczona porazka (np. kolizja).
};

// Ten enum przechowuje poziom trudnosci wybrany przez gracza.
enum class PoziomTrudnosci {
    LATWY,   // Najlatwiejsza konfiguracja.
    SREDNI,  // Srednia konfiguracja.
    TRUDNY   // Najtrudniejsza konfiguracja.
};

// Ten enum mowi, w ktora strone porusza sie samochod.
enum class Kierunek {
    LEWO,   // Ruch samochodu w lewo.
    PRAWO   // Ruch samochodu w prawo.
};
