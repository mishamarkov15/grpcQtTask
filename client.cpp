#include <QApplication>
#include "include/client/ClientMainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    ClientMainWindow w;
    w.show();
    return QApplication::exec();
}