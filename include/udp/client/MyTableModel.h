#ifndef GRPCTESTTASK_MYTABLEMODEL_H
#define GRPCTESTTASK_MYTABLEMODEL_H

#include <cstdint>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QPushButton>
#include <QDateTime>

#include "AddressRecord.h"


class MyTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:


    explicit MyTableModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent) const final;

    int rowCount(const QModelIndex &parent) const final;

    QVariant data(const QModelIndex &index, int role) const final;

    bool insertRows(int row, int count, const QModelIndex &parent) override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:

    void addButtonToTableView(int row, int col, QPushButton *btn);

public slots:

    void updateData(AddressRecord*);

    void addNewAddress(const QString &host, const QString &port);

private:
    QVector<std::shared_ptr<AddressRecord>> records;
    QVector<QVariant> horizontalHeaders;
    int rows = 0;
    int cols = 4;
};

#endif //GRPCTESTTASK_MYTABLEMODEL_H
