#include "InterfejsGraficzny.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication aplikacja(argc, argv);
    InterfejsGraficzny okno;
    okno.show();
    return aplikacja.exec();
}
