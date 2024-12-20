#include "../../../include/udp/client/AddressRecord.h"

const int AddressRecord::max_retries = 3;

AddressRecord::AddressRecord(const QString &host, uint16_t port, int row) :
        host(host),
        port(port),
        status(false),
        lastPing(),
        connectButton(std::make_shared<QPushButton>("connect")),
        timer(std::make_shared<QTimer>(this)),
        row(row) {
    connect(connectButton.get(), &QPushButton::clicked, this, &AddressRecord::pingServer);
    connect(timer.get(), &QTimer::timeout, this, &AddressRecord::ping);
}

void AddressRecord::pingServer() {
    if (status) {
        status = false;
        connectButton->setText("Connect");
        timer->stop();
        pong(this);
    } else {
        timer->start(5000);
    }
}

void AddressRecord::ping() {
    auto channel_args = grpc::ChannelArguments();
    channel_args.SetServiceConfigJSON(std::string(kRetryPolicy));
    QString target_str = host + ":" + QString::number(port);
    QString client_ip = "localhost";
    grpcClient client(
            grpc::CreateCustomChannel(target_str.toStdString(), grpc::InsecureChannelCredentials(), channel_args));
    std::string response = client.Ping(client_ip.toStdString());

    if (response == "pong") {
        connectButton->setText("disconnect");
        status = true;
        lastPing = QDateTime(QDate::currentDate(), QTime::currentTime());
        qDebug() << response.c_str();
    } else {
        status = false;
        connectButton->setText("Connect");
        qDebug() << target_str << "is unavailable";
        timer->stop();
    }
    pong(this);
}