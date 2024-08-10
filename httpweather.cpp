#include "httpweather.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>

HttpWeather::HttpWeather(QObject *parent) : QObject(parent)
{

}

void HttpWeather::getWeather(const QString &province, const QString &city, const QString &area)
{
    QString urlstr = QString("http://iweather.market.alicloudapi.com/address?needday=1&prov=%1&city=%2&area=%3")
                     .arg(province).arg(city).arg(area);
    QUrl url(urlstr);
    QNetworkRequest request(url);
    //qDebug() << "Generated URL:" << urlstr; // 打印生成的 URL

    // 设置请求头
    request.setRawHeader("Authorization", "APPCODE 5d9ebeff853145a7b80cbe3dbfd9580e");

    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::readyRead, this, &HttpWeather::read_data);
    connect(reply, &QNetworkReply::finished, this, &HttpWeather::down_finished);

    allArray.clear();
}

void HttpWeather::read_data()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray tmp = reply->readAll();
    allArray.append(tmp);
}

void HttpWeather::down_finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    //qDebug() << "Received JSON Data:" << allArray; // 打印返回的 JSON 数据

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(allArray, &jsonerror);
    if (jsonerror.error != QJsonParseError::NoError)
    {
        qDebug() << "json error";
        return;
    }

    QJsonObject obj = doc.object();
    QJsonObject dataObj = obj.value("data").toObject();
    QJsonObject nowObj = dataObj.value("now").toObject();
    QJsonObject cityObj = nowObj.value("city").toObject();

    QString weather = cityObj.value("weather").toString();
    QString temperature = cityObj.value("day_air_temperature").toString();

    QString weatherInfo = QString("天气：%1，%2°").arg(weather).arg(temperature);

    emit weatherInfoReceived(weatherInfo);

    disconnect(reply, &QNetworkReply::readyRead, this, &HttpWeather::read_data);
    disconnect(reply, &QNetworkReply::finished, this, &HttpWeather::down_finished);
    reply->deleteLater();
}
