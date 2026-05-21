// Dolaczamy deklaracje klasy interfejsu graficznego.
#include "InterfejsGraficzny.h"

// Funkcje pomocnicze STL.
#include <algorithm>
// Qt: obsluga czcionek.
#include <QFont>
// Qt: obsluga zdarzen klawiatury.
#include <QKeyEvent>
// Qt: gradienty tla i przyciskow.
#include <QLinearGradient>
// Qt: obsluga zdarzen myszy.
#include <QMouseEvent>
// Qt: narzedzie rysujace.
#include <QPainter>

// Konstruktor przygotowuje okno, przyciski i petle odswiezania.
InterfejsGraficzny::InterfejsGraficzny(QWidget* rodzic) : QWidget(rodzic) {
    setWindowTitle(QStringLiteral("Żaba na ulicy - Qt GUI"));
    setFixedSize(960, 720);
    setFocusPolicy(Qt::StrongFocus);

    QFont czcionka(QStringLiteral("Segoe UI"));
    czcionka.setStyleHint(QFont::SansSerif);
    setFont(czcionka);

    // Przyciski menu i ekranu koncowego.
    przyciskLatwy = QRect(370, 250, 220, 62);
    przyciskSredni = QRect(370, 340, 220, 62);
    przyciskTrudny = QRect(370, 430, 220, 62);
    przyciskPowrot = QRect(340, 470, 280, 64);

    timerPetli.setInterval(16);  // 16 ms = 60 Hz
    connect(&timerPetli, &QTimer::timeout, this, &InterfejsGraficzny::odswiezSymulacje);
    timerPetli.start();
    zegarKlatek.start();
}

// Qt wywoluje te metode przy kazdym odrysowaniu okna.
void InterfejsGraficzny::paintEvent(QPaintEvent* zdarzenie) {
    (void)zdarzenie;
    QPainter rysownik(this);
    rysownik.setRenderHint(QPainter::Antialiasing, true);

    if (gra.pobierzStan() == StanGry::MENU) {
        rysujMenu(rysownik);
    } else if (gra.pobierzStan() == StanGry::W_TRAKCIE) {
        rysujRozgrywke(rysownik);
    } else {
        rysujRozgrywke(rysownik);
        rysujEkranKoncowy(rysownik, gra.pobierzStan() == StanGry::WYGRANA);
    }
}

// Obsluguje klikniecia myszy w menu i na ekranie koncowym.
void InterfejsGraficzny::mousePressEvent(QMouseEvent* zdarzenie) {
    if (zdarzenie->button() != Qt::LeftButton) {
        return;
    }

    const QPoint pozycja = zdarzenie->pos();
    if (gra.pobierzStan() == StanGry::MENU) {
        if (przyciskLatwy.contains(pozycja)) {
            gra.rozpocznijGre(PoziomTrudnosci::LATWY);
        } else if (przyciskSredni.contains(pozycja)) {
            gra.rozpocznijGre(PoziomTrudnosci::SREDNI);
        } else if (przyciskTrudny.contains(pozycja)) {
            gra.rozpocznijGre(PoziomTrudnosci::TRUDNY);
        }
    } else if ((gra.pobierzStan() == StanGry::WYGRANA || gra.pobierzStan() == StanGry::PRZEGRANA) &&
               przyciskPowrot.contains(pozycja)) {
        gra.przejdzDoMenu();
    }

    update();
}

// Obsluguje sterowanie klawiatura podczas gry.
void InterfejsGraficzny::keyPressEvent(QKeyEvent* zdarzenie) {
    if (gra.pobierzStan() != StanGry::W_TRAKCIE) {
        QWidget::keyPressEvent(zdarzenie);
        return;
    }

    // Sterowanie uproszczone: tylko W/A/S/D (dx, dy = kierunek ruchu).
    if (zdarzenie->key() == Qt::Key_W) {
        gra.ruch(0, 1);
    } else if (zdarzenie->key() == Qt::Key_S) {
        gra.ruch(0, -1);
    } else if (zdarzenie->key() == Qt::Key_A) {
        gra.ruch(-1, 0);
    } else if (zdarzenie->key() == Qt::Key_D) {
        gra.ruch(1, 0);
    } else if (zdarzenie->key() == Qt::Key_Escape) {
        gra.przejdzDoMenu();
    }

    update();
}

// Wywolywane przez timer: liczy delta czasu i aktualizuje logike gry.
void InterfejsGraficzny::odswiezSymulacje() {
    // Obliczamy delta i aktualizujemy silnik gry co bardzo krotki krok czasu.
    const qint64 ms = zegarKlatek.restart();
    const float deltaSekundy = static_cast<float>(ms) / 1000.0f;
    gra.aktualizujKrok(deltaSekundy);
    update();
}

// Rysuje ekran menu wraz z przyciskami poziomow.
void InterfejsGraficzny::rysujMenu(QPainter& rysownik) {
    QLinearGradient tlo(0, 0, 0, height());
    tlo.setColorAt(0.0, QColor(26, 34, 44));
    tlo.setColorAt(1.0, QColor(16, 20, 28));
    rysownik.fillRect(rect(), tlo);

    rysownik.setPen(QColor(235, 242, 245));
    rysownik.setFont(QFont(font().family(), 36, QFont::Bold));
    rysownik.drawText(QRect(0, 56, width(), 80), Qt::AlignHCenter, QStringLiteral("Żaba na ulicy"));
    rysownik.setFont(QFont(font().family(), 14));
    rysownik.setPen(QColor(184, 196, 204));
    rysownik.drawText(QRect(0, 114, width(), 40), Qt::AlignHCenter,
                      QStringLiteral("Wybierz poziom trudności"));

    rysujPrzycisk(rysownik, przyciskLatwy, QStringLiteral("Łatwy"));
    rysujPrzycisk(rysownik, przyciskSredni, QStringLiteral("Średni"));
    rysujPrzycisk(rysownik, przyciskTrudny, "Trudny");
}

// Rysuje cala aktywna scene gry: tlo, pasy, auta, abe i pasek statusu.
void InterfejsGraficzny::rysujRozgrywke(QPainter& rysownik) {
    const float rozmiarPola = gra.pobierzRozmiarPola();
    const int rozmiarPolaInt = static_cast<int>(rozmiarPola);
    const int szerokoscPlanszy =
        static_cast<int>(static_cast<float>(gra.pobierzSzerokoscSiatki()) * rozmiarPola);
    const int offsetX = (width() - szerokoscPlanszy) / 2;
    const int ostatniWiersz = gra.pobierzWysokoscSiatki() - 1;

    // Ciemne tlo po bokach (poza obszarem gry - nie trawa).
    rysownik.fillRect(QRect(0, 0, width(), 660), QColor(42, 48, 54));

    rysownik.save();
    rysownik.translate(offsetX, 0);

    // Tlo i strefy gry (meta/start) w bardziej realistycznych kolorach.
    QLinearGradient tlo(0, 0, 0, 660);
    tlo.setColorAt(0.0, QColor(133, 181, 219));
    tlo.setColorAt(1.0, QColor(74, 127, 173));
    rysownik.fillRect(QRect(0, 0, szerokoscPlanszy, 660), tlo);

    // Najpierw cala plansza to trawa.
    rysownik.fillRect(QRect(0, 0, szerokoscPlanszy, 660), QColor(126, 185, 103));

    // Rysujemy tylko te wiersze, ktore sa droga.
    int indeksPasa = 0;
    for (const int wierszDrogi : gra.pobierzDroge().pobierzWierszePasow()) {
        const int yPasa =
            static_cast<int>((static_cast<float>(ostatniWiersz - wierszDrogi)) * rozmiarPola);
        const QColor kolor = (indeksPasa % 2 == 0) ? QColor(72, 72, 76) : QColor(62, 62, 66);
        rysownik.fillRect(QRect(0, yPasa, szerokoscPlanszy, rozmiarPolaInt), kolor);

        // Przerywane linie drogowe.
        rysownik.setPen(QPen(QColor(236, 221, 133), 3));
        for (int x = 10; x < szerokoscPlanszy; x += 48) {
            rysownik.drawLine(QPoint(x, yPasa + (rozmiarPolaInt / 2)),
                              QPoint(std::min(x + 24, szerokoscPlanszy), yPasa + (rozmiarPolaInt / 2)));
        }
        ++indeksPasa;
    }

    // Samochody (tylko na obszarze drogi, bez rysowania na bocznych marginesach).
    rysownik.setClipRect(QRect(0, 0, szerokoscPlanszy, 660));
    rysownik.setPen(Qt::NoPen);
    for (const auto& pas : gra.pobierzDroge().pobierzPasy()) {
        for (const auto& autoNaPasie : pas.pobierzSamochody()) {
            const float szerokoscAuta = rozmiarPola * 0.80f;
            const float wysokoscAuta = rozmiarPola * 0.38f;
            const float srodekX = autoNaPasie.pobierzX();
            if (srodekX + (szerokoscAuta / 2.0f) < 0.0f ||
                srodekX - (szerokoscAuta / 2.0f) > static_cast<float>(szerokoscPlanszy)) {
                continue;
            }
            const QRectF autoR(srodekX - (szerokoscAuta / 2.0f),
                               autoNaPasie.pobierzY() - (wysokoscAuta / 2.0f), szerokoscAuta,
                               wysokoscAuta);
            QColor kolorNadwozia;
            switch (autoNaPasie.pobierzWariantKoloru()) {
                case 0:
                    kolorNadwozia = QColor(206, 74, 67);
                    break;
                case 1:
                    kolorNadwozia = QColor(65, 141, 206);
                    break;
                default:
                    kolorNadwozia = QColor(224, 164, 64);
                    break;
            }
            rysownik.setBrush(kolorNadwozia);
            rysownik.drawRoundedRect(autoR, 7.0, 7.0);

            // Szyby.
            rysownik.setBrush(QColor(189, 224, 245));
            rysownik.drawRoundedRect(QRectF(autoR.x() + (szerokoscAuta * 0.20f),
                                            autoR.y() + (wysokoscAuta * 0.18f),
                                            szerokoscAuta * 0.60f,
                                            wysokoscAuta * 0.38f),
                                     3.0, 3.0);

            // Kola.
            rysownik.setBrush(QColor(30, 32, 35));
            const float promienKola = std::max(3.5f, rozmiarPola * 0.08f);
            rysownik.drawEllipse(QPointF(autoR.x() + (szerokoscAuta * 0.18f), autoR.bottom()), promienKola,
                                 promienKola);
            rysownik.drawEllipse(QPointF(autoR.x() + (szerokoscAuta * 0.82f), autoR.bottom()), promienKola,
                                 promienKola);
        }
    }
    rysownik.setClipping(false);

    // Zaba (korpus + oczy + lapy), zeby wygladala mniej jak kolo.
    const int pozycjaX = gra.pobierzZabe().pobierzX();
    const int pozycjaY = gra.pobierzZabe().pobierzY();
    const float x = (static_cast<float>(pozycjaX) + 0.5f) * rozmiarPola;
    const float y = (static_cast<float>(ostatniWiersz - pozycjaY) + 0.5f) * rozmiarPola;
    const float promienKorpusuX = std::max(14.0f, rozmiarPola * 0.22f);
    const float promienKorpusuY = std::max(11.0f, rozmiarPola * 0.18f);
    const float promienOka = std::max(4.0f, rozmiarPola * 0.06f);
    const float przesuniecieOka = std::max(7.0f, rozmiarPola * 0.10f);
    const float przesuniecieLap = std::max(11.0f, rozmiarPola * 0.16f);

    // Ciemny obrys i cien poprawiaja widocznosc na trawie (szczegolnie na latwym).
    rysownik.setBrush(QColor(22, 58, 29, 190));
    rysownik.drawEllipse(QPointF(x, y + 2.5f), promienKorpusuX + 2.0f, promienKorpusuY + 2.0f);

    rysownik.setBrush(QColor(74, 192, 92));
    rysownik.setPen(QPen(QColor(14, 44, 20), 2));
    rysownik.drawEllipse(QPointF(x, y), promienKorpusuX, promienKorpusuY);
    rysownik.drawEllipse(QPointF(x - przesuniecieOka, y - przesuniecieOka), promienOka, promienOka);
    rysownik.drawEllipse(QPointF(x + przesuniecieOka, y - przesuniecieOka), promienOka, promienOka);
    rysownik.setBrush(QColor(18, 20, 22));
    rysownik.drawEllipse(QPointF(x - przesuniecieOka, y - przesuniecieOka),
                         std::max(1.8f, promienOka * 0.36f), std::max(1.8f, promienOka * 0.36f));
    rysownik.drawEllipse(QPointF(x + przesuniecieOka, y - przesuniecieOka),
                         std::max(1.8f, promienOka * 0.36f), std::max(1.8f, promienOka * 0.36f));
    rysownik.setBrush(QColor(61, 170, 77));
    rysownik.drawEllipse(QPointF(x - przesuniecieLap, y + (promienKorpusuY * 0.75f)),
                         std::max(4.0f, promienKorpusuX * 0.28f), std::max(3.0f, promienKorpusuY * 0.24f));
    rysownik.drawEllipse(QPointF(x + przesuniecieLap, y + (promienKorpusuY * 0.75f)),
                         std::max(4.0f, promienKorpusuX * 0.28f), std::max(3.0f, promienKorpusuY * 0.24f));

    rysownik.restore();

    // Pasek statusu.
    rysownik.fillRect(QRect(0, 660, width(), 60), QColor(18, 24, 30, 232));
    rysownik.setPen(QColor(234, 240, 243));
    rysownik.setFont(QFont(font().family(), 12));
    const QString status =
        QString("Poziom: %1   |   Czas: %2 s   |   Sterowanie: W/A/S/D")
            .arg(tekstPoziomu(gra.pobierzPoziomTrudnosci()))
            .arg(gra.pobierzCzasSekundy());
    rysownik.drawText(QRect(18, 676, width() - 36, 28), Qt::AlignLeft | Qt::AlignVCenter, status);
}

// Rysuje polprzezroczysta nakladke koncowa z wynikiem gry.
void InterfejsGraficzny::rysujEkranKoncowy(QPainter& rysownik, bool czyWygrana) {
    rysownik.fillRect(rect(), QColor(19, 24, 34, 185));
    rysownik.setFont(QFont(font().family(), 44, QFont::Bold));
    rysownik.setPen(czyWygrana ? QColor(70, 220, 90) : QColor(230, 85, 85));
    rysownik.drawText(QRect(0, 190, width(), 100), Qt::AlignHCenter, czyWygrana ? "WYGRANA" : "PRZEGRANA");
    rysownik.setFont(QFont(font().family(), 22));
    rysownik.setPen(QColor(210, 220, 230));
    rysownik.drawText(QRect(0, 300, width(), 50), Qt::AlignHCenter,
                      QString("Czas gry: %1 s").arg(gra.pobierzCzasSekundy()));
    rysownik.setFont(QFont(font().family(), 14));
    rysownik.setPen(QColor(170, 182, 194));
    rysownik.drawText(QRect(0, 350, width(), 40), Qt::AlignHCenter,
                      QStringLiteral("Kliknij przycisk, aby wrócić do menu"));
    rysujPrzycisk(rysownik, przyciskPowrot, QStringLiteral("Powrót do menu"));
}

// Rysuje pojedynczy przycisk o wspolnym stylu.
void InterfejsGraficzny::rysujPrzycisk(QPainter& rysownik, const QRect& przycisk, const QString& tekst) {
    QLinearGradient gradient(przycisk.topLeft(), przycisk.bottomLeft());
    gradient.setColorAt(0.0, QColor(111, 152, 236));
    gradient.setColorAt(1.0, QColor(75, 116, 204));
    rysownik.setPen(QPen(QColor(42, 64, 120), 2));
    rysownik.setBrush(gradient);
    rysownik.drawRoundedRect(przycisk, 8.0, 8.0);
    rysownik.setPen(QColor(245, 249, 255));
    rysownik.setFont(QFont(font().family(), 18, QFont::Bold));
    rysownik.drawText(przycisk, Qt::AlignCenter, tekst);
}

// Zamienia enum poziomu trudnosci na czytelny tekst.
QString InterfejsGraficzny::tekstPoziomu(PoziomTrudnosci poziom) const {
    switch (poziom) {
        case PoziomTrudnosci::LATWY:
            return QStringLiteral("Łatwy");
        case PoziomTrudnosci::SREDNI:
            return QStringLiteral("Średni");
        case PoziomTrudnosci::TRUDNY:
            return QStringLiteral("Trudny");
    }
    return QStringLiteral("Łatwy");
}
