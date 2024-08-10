#ifndef HTTPCAR_H
#define HTTPCAR_H

#include "http_client.hpp"
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

class HttpCar : public QObject {
    Q_OBJECT
public:
    explicit HttpCar(QObject *parent = nullptr);

    QString getImageBase64(const QString &filePath);
    void DriverRegister(QString driver_name, uint8_t driver_type);
    void CarEnter(const QString &imagePath, std::function<void(const QByteArray &)>);
    void CarExit(const QString &imagePath, std::function<void(const QByteArray &)> callback);

signals:
    void failedbord(const QString &errorMessage);

private slots:
     void handleRequestFailed(const QString &errorMessage);


private:
    QString driver_id;
    QString driver_name;
    QString driver_type;
    HttpClient httpClient;
};

#endif // HTTPCAR_H
