#include "../../../include/udp/client/MyTableModel.h"


MyTableModel::MyTableModel(QObject *parent) :
        QAbstractTableModel(parent),
        horizontalHeaders(4, "") {
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return cols;
}

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return rows;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return records[index.row()]->host + ":" + QString::number(records[index.row()]->port);
        } else if (index.column() == 1) {
            QDateTime lastPing = records[index.row()]->lastPing;
            if (lastPing.isNull()) {
                return "-";
            }
            return lastPing.toString("hh:mm:ss");
        } else if (index.column() == 2) {
            return records[index.row()]->status ? "ONLINE" : "OFFLINE";
        } else if (index.column() == 3) {
            return QVariant::fromValue(records[index.row()]->connectButton);
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        try {
            return horizontalHeaders[section];
        } catch (...) {}
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool MyTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    if (orientation == Qt::Horizontal && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        try {
            horizontalHeaders[section] = value;
            return true;
        } catch (...) {
            return false;
        }
    }
    return QAbstractItemModel::setHeaderData(section, orientation, value, role);
}

bool MyTableModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    rows += count;
    endInsertRows();
    return QAbstractItemModel::insertRows(row, count, parent);
}

void MyTableModel::addNewAddress(const QString &host, const QString &port) {
    std::shared_ptr<AddressRecord> ar = std::make_shared<AddressRecord>(host, port.toUShort(), 0);
    if (records.contains(ar)) {
        qWarning() << "Address" << host << ":" << port << "already exist in table";
    } else {
        qDebug() << "New address was added!";
        insertRows(rows, 1, QModelIndex());
        ar->row = rows-1;
        setData(index(rows - 1, 0), ar->host);
        setData(index(rows - 1, 1), ar->port);
        setData(index(rows - 1, 2), ar->status ? "ONLINE" : "OFFLINE");
        records.push_back(ar);

        addButtonToTableView(rows - 1, 3, ar->connectButton.get());

        connect(ar.get(), &AddressRecord::pong, this, &MyTableModel::updateData);
    }
}

void MyTableModel::updateData(AddressRecord* ar) {
    setData(index(ar->row, 2), ar->status ? "ONLINE" : "OFFLINE");
}
