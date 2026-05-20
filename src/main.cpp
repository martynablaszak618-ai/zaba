// Dolaczamy klase glownego okna aplikacji.
#include "InterfejsGraficzny.h"

// Dolaczamy klase QApplication (wymagana w kazdej aplikacji Qt).
#include <QApplication>

// Punkt startowy programu.
int main(int argc, char* argv[]) {
    // Tworzymy obiekt aplikacji Qt i przekazujemy argumenty z linii polecen.
    QApplication aplikacja(argc, argv);
    // Tworzymy glowne okno gry.
    InterfejsGraficzny okno;
    // Pokazujemy okno uzytkownikowi.
    okno.show();
    // Uruchamiamy petle zdarzen Qt (program dziala dopoki okno nie zostanie zamkniete).
    return aplikacja.exec();
}
