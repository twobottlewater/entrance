#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <functional>

class HttpClient : public QObject {
    Q_OBJECT

public:
    using Callback = std::function<void(const QByteArray &)>;

    HttpClient(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this,
                &HttpClient::onFinished);
    }

    // 发送 GET 请求，带查询参数
    void sendGetRequest(QNetworkRequest request, HttpClient::Callback callback) {
        QNetworkReply *reply = manager->get(request);
        callbacks[reply] = callback;
    }

    // 发送 POST 请求，带请求体
    void sendPostRequest(QNetworkRequest request, const QByteArray &body,
                         HttpClient::Callback callback) {
        QNetworkReply *reply = manager->post(request, body);
        callbacks[reply] = callback;
    }
signals:
    void requestFailed(const QString &errorMessage);

private slots:
    void onFinished(QNetworkReply *reply) {
        if (callbacks.contains(reply)) {
            auto callback = callbacks.take(reply);
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray response = reply->readAll();
                callback(response);
            } else {
                auto data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();
                if (jsonObj.contains("error")) {
                    qWarning() << "Request failed:" << jsonObj["error"].toString();
                    // 发射信号
                    emit requestFailed("error");
                }
                qWarning() << "Request failed: not error";
            }
        }
        reply->deleteLater();
    }

private:
    QNetworkAccessManager *manager;
    QHash<QNetworkReply *, Callback> callbacks;
};
