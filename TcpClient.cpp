#include "TcpClient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &TcpClient::onError);
}

void TcpClient::connectToServer(const QString &host, quint16 port)
{
    tcpSocket->connectToHost(host, port);
}

void TcpClient::sendData(const QString &jsonString)
{
    QByteArray data = jsonString.toUtf8()+ '\n';
    qint64 bytesSent = tcpSocket->write(data);
    if (bytesSent == -1) {
        emit dataSent(false);
        qDebug() << "Failed to send data:" << tcpSocket->errorString();
    } else {
        emit dataSent(true);
        qDebug() << "Data sent, bytes:" << bytesSent;
    }
}

QString TcpClient::createJsonData(const QString &base64Image1, const QString &timestamp, const QString &j_plate, const QString &status)
{
    QJsonObject jsonObj;
    jsonObj.insert("status", status);  // 添加status to JSON
    jsonObj.insert("plate", j_plate); //车牌号
    jsonObj.insert("time", timestamp);  //时间
    jsonObj.insert("image", base64Image1);  //图片的base64编码

    QJsonDocument jsonDoc(jsonObj);
    return QString::fromUtf8(jsonDoc.toJson(QJsonDocument::Compact));
}



void TcpClient::onReadyRead()
{
    // 读取所有可用的数据
    QByteArray data = tcpSocket->readAll();
    // 发射数据接收信号，将数据转换为QString类型
    emit dataReceived(QString::fromUtf8(data));
}

void TcpClient::onConnected()
{
    // 发射连接信号
    emit connected();
    // 输出连接成功信息
    qDebug() << "Connected to server.";
}

void TcpClient::onDisconnected()
{
    // 发射断开连接信号
    emit disconnected();
    // 输出断开连接信息
    qDebug() << "Disconnected from server.";
}

void TcpClient::onError(QAbstractSocket::SocketError socketError)
{
    // 忽略socketError参数
    Q_UNUSED(socketError);
    // 发射错误信号，将错误信息转换为QString类型
    emit errorOccurred(tcpSocket->errorString());
    // 输出TCP socket错误信息
    qDebug() << "TCP socket error:" << tcpSocket->errorString();
}