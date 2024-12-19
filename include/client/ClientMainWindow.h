#ifndef GRPCTESTTASK_CLIENTMAINWINDOW_H
#define GRPCTESTTASK_CLIENTMAINWINDOW_H

#include <memory>
#include <cstdint>

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QUdpSocket>

class ClientMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ClientMainWindow(uint16_t portToListen = 10001, QWidget* parent = nullptr);
public slots:
    void readPendingDatagrams();
private:
    void initWidget();
    void initLayout();
    void initConnections();
    void initStyles();

    std::shared_ptr<QWidget> centerWidget;
    std::shared_ptr<QGridLayout> mainLayout;
    std::shared_ptr<QUdpSocket> udpSocket;

    uint16_t portToListen;
};


#endif //GRPCTESTTASK_CLIENTMAINWINDOW_H
