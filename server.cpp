#include <QApplication>
#include "include/udp/server/ServerMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ServerMainWindow w;
    w.show();
    return QApplication::exec();
}
