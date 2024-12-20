#ifndef GRPCTESTTASK_ADDRESSRECORD_H
#define GRPCTESTTASK_ADDRESSRECORD_H

#include "../../grpc/client/grpcClient.h"

#include <cstdint>
#include <memory>

#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QPushButton>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

#include <grpcpp/grpcpp.h>


constexpr absl::string_view kRetryPolicy =
        "{\"methodConfig\": [{"
//        "   \"name\": [{\"service\": \"api.Pong\"}],"
        "   \"waitForReady\": true,"
        "   \"retryPolicy\": {"
        "       \"maxAttempts\": 4,"
        "       \"initialBackoff\": \"1s\","
        "       \"maxBackoff\": \"1s\","
        "       \"backoffMultiplier\": 1.0,"
        "       \"retryableStatusCodes\": [\"UNAVAILABLE\"]"
        "}"
        "}]}";

class AddressRecord : public QObject {
Q_OBJECT
public:
    AddressRecord(const QString& host, uint16_t port, int row);

    bool operator==(const AddressRecord &other) const {
        return host == other.host && port == other.port;
    }

    QString host;
    uint16_t port;
    bool status;
    QDateTime lastPing;
    std::shared_ptr<QPushButton> connectButton;
    int row;
    signals:
    void pong(AddressRecord*);

public slots:
    void pingServer();

private slots:

    void ping();

private:
    std::shared_ptr<QTimer> timer;
    static const int max_retries;
};

inline uint qHash(const AddressRecord &key, uint seed) {
    return qHash(key.host, seed) ^ qHash(key.port, seed + 1);
}

#endif //GRPCTESTTASK_ADDRESSRECORD_H
