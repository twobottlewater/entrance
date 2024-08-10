#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mycamera.h"
#include <QTimer>
#include <QString>
#include <httpweather.h>
#include "httpcar.h"
#include "TcpClient.h"
#include "opendoorbar.h"
#include <QLinkedList>


struct CarInfo {
    QString plateNumber;
    QString timestamp;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void playAudio(const QString &ptahmusic);

private slots:


    //更新时间
    void updateTime();

    void onWeatherInfoReceived(const QString &weatherInfo);


    //滚动播放的槽函数
    void showScrollingText();
    void updateScrollText();
    void displayLicensePlate(const QString &plate);


    //按钮槽函数
    void on_comeButton_clicked();
    void on_outButton_clicked();



    void onDataReceived(const QString &data);
    void onDataSent(bool success);
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(const QString &error);

    // 添加获取当前时间戳的方法
     QString getCurrentTimestamp();

     //统一和服务器发送函数
     void sendToTcp();

     void closeLed();
     void getParkFee(const QString &plate);
    void immobi(const QString &errorcode);


signals:
    void responseProcessed(const QString &plate);

protected:
    //画背景的函数，本来就属于mainwindow
    void paintEvent(QPaintEvent *event) override;



private:
    Ui::MainWindow *ui;

    QTimer *mytimer;
    mycamera *camera;
    HttpWeather *weather;//天气对象
    HttpCar *httpCar;//车牌识别对象
    QString currentTime; // 用于保存时间的字符串变量

    //滚动字幕
    QTimer *scrollTimer;
    QString scrollText;
    int scrollPosition;
    //保存剩余车位
    int numOfPark;
    QString numString;

    //临时保存车牌号
    QString J_plate;


    //进出状态
    QString status;
    TcpClient *tcpClient;

    //收费的数
    int feeAmount;

    //控制门杠的开启
    OpenDoorbar *doorbar; // OpenDoorbar实例
    QTimer *ledTimer; // 定时器用于延迟关闭LED

    QLinkedList<CarInfo> carList;


};
#endif // MAINWINDOW_H
