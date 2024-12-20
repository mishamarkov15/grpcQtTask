#ifndef GRPCTESTTASK_CLIENTMAINWINDOW_H
#define GRPCTESTTASK_CLIENTMAINWINDOW_H

#include <memory>
#include <cstdint>

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QUdpSocket>
#include <QAbstractItemModel>
#include <QTableView>
#include <QHeaderView>

#include "MyTableModel.h"


class ClientMainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit ClientMainWindow(uint16_t portToListen = 10001, QWidget *parent = nullptr);

public slots:

    void readPendingDatagrams();

    void addButtonToTable(int row, int col, QPushButton* btn);

signals:

    void newAddressAvailable(const QString& host, const QString& port);

private:
    void initWidget();

    void initLayout();

    void initConnections();

    void initStyles();

    static bool isAddressCorrect(const QString& address);

    std::shared_ptr<QWidget> centerWidget;
    std::shared_ptr<QGridLayout> mainLayout;
    std::shared_ptr<QUdpSocket> udpSocket;

    std::shared_ptr<QTableView> tableView;
    std::shared_ptr<QAbstractItemModel> tableModel;

    uint16_t portToListen;
};


#endif //GRPCTESTTASK_CLIENTMAINWINDOW_H
