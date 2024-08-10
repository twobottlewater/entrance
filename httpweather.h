#ifndef HTTPWEATHER_H
#define HTTPWEATHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class HttpWeather : public QObject
{
    Q_OBJECT
public:
    explicit HttpWeather(QObject *parent = nullptr);

    void getWeather(const QString &province, const QString &city, const QString &area);


signals:
        void weatherInfoReceived(const QString &weatherInfo);

private slots:
        void read_data();
        void down_finished();


private:
        QNetworkAccessManager manager;
        QByteArray allArray;


};

#endif // HTTPWEATHER_H
