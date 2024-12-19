#include "../../include/client/ClientMainWindow.h"

ClientMainWindow::ClientMainWindow(uint16_t portToListen, QWidget *parent) :
        QMainWindow(parent),
        centerWidget(std::make_shared<QWidget>()),
        mainLayout(std::make_shared<QGridLayout>()),
        udpSocket(std::make_shared<QUdpSocket>(this)),
        portToListen(portToListen) {
    setWindowTitle("gRPC client");
    initWidget();
    initLayout();
    initConnections();
    initStyles();
}

void ClientMainWindow::initWidget() {
    setCentralWidget(centerWidget.get());
    centerWidget->setLayout(mainLayout.get());

    udpSocket->bind(portToListen, QUdpSocket::ShareAddress);
}

void ClientMainWindow::initLayout() {

}

void ClientMainWindow::initConnections() {
    connect(udpSocket.get(), &QUdpSocket::readyRead, this, &ClientMainWindow::readPendingDatagrams);
}

void ClientMainWindow::initStyles() {

}

void ClientMainWindow::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        uint16_t senderPort;
        udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        qDebug() << "Reading from" << sender << senderPort << buffer;
    }
}