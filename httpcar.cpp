#include "httpcar.h"
#include "config.h"

HttpCar::HttpCar(QObject *parent) : QObject(parent)
{
    connect(&httpClient, &HttpClient::requestFailed, this, &HttpCar::handleRequestFailed);

}

QString HttpCar::getImageBase64(const QString &filePath) {
    try {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file:" << filePath;
            return QString();
        }

        QByteArray imageData = file.readAll();
        file.close();

        return QString::fromLatin1(imageData.toBase64());
    } catch (...) {
        qDebug() << "Failed to convert image to base64";
        return QString();
    }
}

void HttpCar::DriverRegister(QString driver_name, uint8_t driver_type) {
    QUrl url(REMOTE_HOST "/api/dev/register");

    QNetworkRequest request(url);
    QString host = REMOTE_HOST;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Host", host.toLocal8Bit());

    QJsonObject jsonObj;
    jsonObj.insert("driver_name", driver_name);
    jsonObj.insert("driver_type", driver_type);
    QJsonDocument jsonDoc(jsonObj);
    QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);

    httpClient.sendPostRequest(
        request, postData, [this, driver_name, driver_type](QByteArray data) {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("err")) {
                qDebug() << "Failed to register driver:"
                         << jsonObj.value("err").toString();
                return;
            }
            this->driver_id = jsonObj.value("driver_id").toString();
            this->driver_name = driver_name;
            this->driver_type = driver_type;
        });
}

void HttpCar::CarEnter(const QString &imagePath,
                       std::function<void(const QByteArray &)> callback) {
    QString base64Data = getImageBase64(imagePath);
    if (base64Data.isEmpty()) {
        qDebug() << "Failed to get base64 data";
        return;
    }
    QUrl url(REMOTE_HOST "/api/car/enter");

    QNetworkRequest request(url);
    QString host = REMOTE_HOST;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Host", host.toLocal8Bit());

    QJsonObject jsonObj;
    jsonObj.insert("driver_id", this->driver_id);
    jsonObj.insert("license_plate_image", base64Data);
    QJsonDocument jsonDoc(jsonObj);
    QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << "get request";
    httpClient.sendPostRequest(request, postData, callback);
}

void HttpCar::CarExit(const QString &imagePath, std::function<void(const QByteArray &)> callback) {
    QString base64Data = getImageBase64(imagePath);
    if (base64Data.isEmpty()) {
        qDebug() << "Failed to get base64 data";
        return;
    }
    QUrl url(REMOTE_HOST "/api/car/exit");

    QNetworkRequest request(url);
    QString host = REMOTE_HOST;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Host", host.toLocal8Bit());

    QJsonObject jsonObj;
    jsonObj.insert("driver_id", this->driver_id);
    jsonObj.insert("license_plate_image", base64Data);
    QJsonDocument jsonDoc(jsonObj);
    QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);

    httpClient.sendPostRequest(request, postData, callback);
}

void HttpCar::handleRequestFailed(const QString &errorMessage)
{
    emit failedbord("error");
}
