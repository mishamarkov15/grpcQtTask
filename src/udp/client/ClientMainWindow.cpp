#include "../../../include/udp/client/ClientMainWindow.h"

ClientMainWindow::ClientMainWindow(uint16_t portToListen, QWidget *parent) :
        QMainWindow(parent),
        centerWidget(std::make_shared<QWidget>()),
        mainLayout(std::make_shared<QGridLayout>()),
        udpSocket(std::make_shared<QUdpSocket>(this)),
        tableView(std::make_shared<QTableView>()),
        tableModel(std::make_shared<MyTableModel>()),
        portToListen(portToListen) {
    setWindowTitle("gRPC client");
    resize(600, 600);
    initWidget();
    initLayout();
    initConnections();
    initStyles();
}

void ClientMainWindow::initWidget() {
    setCentralWidget(centerWidget.get());
    centerWidget->setLayout(mainLayout.get());

    udpSocket->bind(portToListen, QUdpSocket::ShareAddress);


    tableModel->setHeaderData(0, Qt::Horizontal, "IP");
    tableModel->setHeaderData(1, Qt::Horizontal, "Last ping");
    tableModel->setHeaderData(2, Qt::Horizontal, "Status");
    tableModel->setHeaderData(3, Qt::Horizontal, "Action");

    tableView->setModel(tableModel.get());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ClientMainWindow::initLayout() {
    mainLayout->addWidget(tableView.get(), 0, 0, 1, 1);
}

void ClientMainWindow::initConnections() {
    connect(udpSocket.get(), &QUdpSocket::readyRead, this, &ClientMainWindow::readPendingDatagrams);
    connect(this,
            &ClientMainWindow::newAddressAvailable,
            reinterpret_cast<MyTableModel *>(tableModel.get()),
            &MyTableModel::addNewAddress);
    connect(reinterpret_cast<MyTableModel *>(tableModel.get()),
                                                         &MyTableModel::addButtonToTableView,
                                                         this,
                                                         &ClientMainWindow::addButtonToTable);
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
        if (isAddressCorrect(buffer)) {
            QByteArrayList items = buffer.split(':');
            newAddressAvailable(QString(items[0]), QString(items[1]));
            tableView->update();
        } else {
            qWarning() << "Address" << buffer << "is incorrect";
        }
    }
}

//void ClientMainWindow::addNewServerToTable(const QString &host, const QString &port) {
//    tableModel->insertRows(tableModel->rowCount(), 1);
//    tableView->update();
//}

/**
 * @example Correct address "127.0.0.1:10001" (i.e. "host:port"). Not correct address "127.0.0.1 10001"
 * @param address
 * @return
 */
bool ClientMainWindow::isAddressCorrect(const QString &address) {
    if (!address.contains(':')) return false;

    QStringList items = address.split(':');
    if (items.size() != 2) return false;

    if (items.at(0) != "localhost") {
        if (items.at(0).count('.') != 3) return false;
        for (const auto &ipPart: items.at(0).split('.')) {
            bool correctInt = false;
            int part = ipPart.toInt(&correctInt);

            if (!correctInt) return false;
            if (!(0 <= part && part <= 255)) return false;
        }
    }

    bool isPortCorrect;
    try {
        items.at(1).toUShort(&isPortCorrect);
        if (!isPortCorrect) {
            return false;
        }
    } catch (...) {
        return false;
    }
    return true;
}

void ClientMainWindow::addButtonToTable(int row, int col, QPushButton *btn) {
    tableView->setIndexWidget(tableModel->index(row, col), btn);
}
