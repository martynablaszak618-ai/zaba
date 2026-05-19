#pragma once

#include "Gra.h"

#include <QElapsedTimer>
#include <QRect>
#include <QString>
#include <QTimer>
#include <QWidget>

// Okno Qt z pelnym GUI: menu, rozgrywka, ekran koncowy.
class InterfejsGraficzny : public QWidget {
public:
    explicit InterfejsGraficzny(QWidget* rodzic = nullptr);

protected:
    void paintEvent(QPaintEvent* zdarzenie) override;
    void mousePressEvent(QMouseEvent* zdarzenie) override;
    void keyPressEvent(QKeyEvent* zdarzenie) override;

private:
    void odswiezSymulacje();
    void rysujMenu(class QPainter& rysownik);
    void rysujRozgrywke(class QPainter& rysownik);
    void rysujEkranKoncowy(class QPainter& rysownik, bool czyWygrana);
    void rysujPrzycisk(class QPainter& rysownik, const QRect& przycisk, const QString& tekst);
    QString tekstPoziomu(PoziomTrudnosci poziom) const;

    Gra gra;
    QTimer timerPetli;
    QElapsedTimer zegarKlatek;

    QRect przyciskLatwy;
    QRect przyciskSredni;
    QRect przyciskTrudny;
    QRect przyciskPowrot;
};
