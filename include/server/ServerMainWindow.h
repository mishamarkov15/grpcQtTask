#ifndef GRPCTESTTASK_SERVERMAINWINDOW_H
#define GRPCTESTTASK_SERVERMAINWINDOW_H

#include <memory>
#include <cstdint>
#include <iostream>

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QUdpSocket>
#include <QByteArray>
#include <QString>


class ServerMainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit ServerMainWindow(uint16_t port = 10001, QWidget* parent = nullptr);

public slots:
    void logMessage();

    void broadcastMessage();

private:
    void initWidget();
    void initConnections();
    void initLayout();
    void initStyles();

    std::shared_ptr<QWidget> centerWidget;
    std::shared_ptr<QGridLayout> mainLayout;
    std::shared_ptr<QTextEdit> messagesLogArea;
    std::shared_ptr<QLineEdit> portLineEdit;
    std::shared_ptr<QLabel> portLabel;
    std::shared_ptr<QPushButton> startButton;
    std::shared_ptr<QUdpSocket> udpSocket;

    uint16_t port;
};


#endif //GRPCTESTTASK_SERVERMAINWINDOW_H
