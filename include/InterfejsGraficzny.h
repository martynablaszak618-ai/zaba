// Ta dyrektywa zapobiega wielokrotnemu dolaczaniu pliku.
#pragma once

// Dolaczamy silnik logiki gry, ktory bedzie obslugiwany przez GUI.
#include "Gra.h"

// Qt: mierzenie czasu miedzy klatkami.
#include <QElapsedTimer>
// Qt: prostokat (np. obszar przycisku).
#include <QRect>
// Qt: typ tekstowy.
#include <QString>
// Qt: timer do odswiezania gry.
#include <QTimer>
// Qt: bazowa klasa widzetu (okna).
#include <QWidget>

// Klasa reprezentuje glowne okno aplikacji i caly interfejs.
class InterfejsGraficzny : public QWidget {
public:
    // Konstruktor okna; mozna podac rodzica Qt (domyslnie brak).
    explicit InterfejsGraficzny(QWidget* rodzic = nullptr);

protected:
    // Metoda wywolywana przez Qt, gdy okno trzeba narysowac.
    void paintEvent(QPaintEvent* zdarzenie) override;
    // Metoda obsluguje klikniecia myszy.
    void mousePressEvent(QMouseEvent* zdarzenie) override;
    // Metoda obsluguje klawisze klawiatury.
    void keyPressEvent(QKeyEvent* zdarzenie) override;

private:
    // Aktualizuje logike gry i odswieza ekran.
    void odswiezSymulacje();
    // Rysuje ekran menu glownego.
    void rysujMenu(class QPainter& rysownik);
    // Rysuje plansze i elementy aktywnej rozgrywki.
    void rysujRozgrywke(class QPainter& rysownik);
    // Rysuje nakladke koncowa (wygrana/przegrana).
    void rysujEkranKoncowy(class QPainter& rysownik, bool czyWygrana);
    // Rysuje jeden przycisk o podanym tekcie.
    void rysujPrzycisk(class QPainter& rysownik, const QRect& przycisk, const QString& tekst);
    // Zamienia enum trudnosci na tekst wyswietlany uzytkownikowi.
    QString tekstPoziomu(PoziomTrudnosci poziom) const;

    // Obiekt logiki gry sterowany przez interfejs.
    Gra gra;
    // Timer Qt uruchamiajacy regularne odswiezanie.
    QTimer timerPetli;
    // Zegar klatek do obliczania delta czasu.
    QElapsedTimer zegarKlatek;

    // Prostokat klikalny dla przycisku "Latwy".
    QRect przyciskLatwy;
    // Prostokat klikalny dla przycisku "Sredni".
    QRect przyciskSredni;
    // Prostokat klikalny dla przycisku "Trudny".
    QRect przyciskTrudny;
    // Prostokat klikalny dla przycisku powrotu do menu.
    QRect przyciskPowrot;
};
