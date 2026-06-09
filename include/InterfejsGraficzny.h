/**
 * @file InterfejsGraficzny.h
 * @brief Glowne okno aplikacji Qt — rysowanie i obsluga wejscia.
 */

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

/**
 * @brief Glowne okno gry — warstwa prezentacji (Qt Widgets).
 * @details Deleguje logike do obiektu Gra; rysuje menu, plansze i ekran koncowy.
 */
class InterfejsGraficzny : public QWidget {
public:
    /** @brief Tworzy okno, timer odswiezania i obszary przyciskow. */
    explicit InterfejsGraficzny(QWidget* rodzic = nullptr);

protected:
    /** @brief Rysuje menu, rozgrywke lub ekran koncowy. */
    void paintEvent(QPaintEvent* zdarzenie) override;
    /** @brief Obsluguje klikniecia w menu i ekranie koncowym. */
    void mousePressEvent(QMouseEvent* zdarzenie) override;
    /** @brief Obsluguje sterowanie W/A/S/D i Escape. */
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
