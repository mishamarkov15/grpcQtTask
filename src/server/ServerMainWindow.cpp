#include "../../include/server/ServerMainWindow.h"

ServerMainWindow::ServerMainWindow(uint16_t port, QWidget *parent)
        : QMainWindow(parent),
          centerWidget(std::make_shared<QWidget>()),
          mainLayout(std::make_shared<QGridLayout>()),
          messagesLogArea(std::make_shared<QTextEdit>()),
          portLineEdit(std::make_shared<QLineEdit>()),
          portLabel(std::make_shared<QLabel>()),
          startButton(std::make_shared<QPushButton>()),
          udpSocket(std::make_shared<QUdpSocket>(this)),
          port(port) {
    setWindowTitle("gRPC Server");
    initWidget();
    initLayout();
    initConnections();
    initStyles();
}

void ServerMainWindow::initWidget() {
    setCentralWidget(centerWidget.get());
    centerWidget->setLayout(mainLayout.get());

    messagesLogArea->setReadOnly(true);

    portLineEdit->setPlaceholderText("Порт, по которому клиенты смогут подключаться.");

    portLabel->setText("Порт:");
    portLabel->setAlignment(Qt::AlignRight);

    startButton->setText("Start server");

    udpSocket->bind(QHostAddress::LocalHost, port);
}

void ServerMainWindow::initLayout() {
    mainLayout->addWidget(messagesLogArea.get(), 0, 0, 7, 10);
    mainLayout->addWidget(portLabel.get(), 7, 0, 1, 1);
    mainLayout->addWidget(portLineEdit.get(), 7, 1, 1, 9);
    mainLayout->addWidget(startButton.get(), 8, 1, 1, 9);
}

void ServerMainWindow::initConnections() {
    connect(startButton.get(), &QPushButton::clicked, this, &ServerMainWindow::logMessage);
    connect(startButton.get(), &QPushButton::clicked, this, &ServerMainWindow::broadcastMessage);
}

void ServerMainWindow::logMessage() {
//    messagesLogArea->append("message");
}

void ServerMainWindow::broadcastMessage() {
    bool ok = false;
    uint16_t grpcPort = portLineEdit->text().toUShort(&ok);
    if (ok) {
        messagesLogArea->append("Starting server at localhost:" + QString::number(grpcPort));
        QByteArray dgram = ("localhost:" + QString::number(grpcPort)).toLocal8Bit();
        udpSocket->writeDatagram(dgram.data(), dgram.size(), QHostAddress::Broadcast, port);
    } else {
        messagesLogArea->append("Error starting server");
    }
}

void ServerMainWindow::initStyles() {
    QFile styles("../styles/server/server_main_window.qss");
    styles.open(QFile::ReadOnly);
    if (!styles.isOpen()) {
        qCritical() << "File with styles was not opened";
    } else {
        messagesLogArea->setStyleSheet(QString::fromLatin1(styles.readAll()));
        styles.close();
    }
}
