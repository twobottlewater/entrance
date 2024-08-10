#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>


class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    void sendData(const QString &jsonString);
    QString createJsonData(const QString &base64Image1, const QString &timestamp,const QString &j_plate, const QString &status);//, const QString &timestamp

signals:
    void dataReceived(const QString &data);
    void dataSent(bool success);
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIENT_H
