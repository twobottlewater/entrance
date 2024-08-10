#include "mainwindow.h"
#include "httpcar.h"
#include "ui_mainwindow.h"
#include  "config.h"
#include <QDateTime>
#include <QDebug>
#include <QLinearGradient>
#include <QPainter>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      weather(new HttpWeather(this)), httpCar(new HttpCar(this)),
      scrollTimer(new QTimer(this)),
      scrollText("--永远把人民对美好生活的向往作为我们的奋斗目标"),
      scrollPosition(0)
{
    ui->setupUi(this);
    tcpClient = new TcpClient(this);

    ledTimer = new QTimer(this);
    doorbar = new OpenDoorbar();

    // 初始化摄像头
    camera = new mycamera();
    camera->camera_init();
    camera->start(); // 启动线程，预览画面

    feeAmount = 0;
    J_plate = "粤A66666";

    mytimer = new QTimer(this);
    connect(mytimer, &QTimer::timeout, this, &MainWindow::updateTime);
    mytimer->start(1000);

    numOfPark = 120;
    numString = "剩余车位：" + QString::number(numOfPark);
    ui->cheweilab->setText(numString);
    httpCar->DriverRegister(DRIVERNAME, DRIVERTYPE);

    // 初始化时间显示
    updateTime();

    // 连接天气信息信号
    connect(weather, &HttpWeather::weatherInfoReceived, this,
            &MainWindow::onWeatherInfoReceived);

    // 获取天气信息
    weather->getWeather("广东", "广州", "海珠");

   
    // 槽函数displayLicensePlate(const QString &plate)
    connect(this, &MainWindow::responseProcessed, this, &MainWindow::displayLicensePlate);

    // 连接滚动播放的槽函数
    connect(scrollTimer, &QTimer::timeout, this, &MainWindow::updateScrollText);

    // tcp的信号与槽函数连接
    connect(tcpClient, &TcpClient::dataReceived, this,
            &MainWindow::onDataReceived);
    connect(tcpClient, &TcpClient::dataSent, this, &MainWindow::onDataSent);
    connect(tcpClient, &TcpClient::connected, this, &MainWindow::onConnected);
    connect(tcpClient, &TcpClient::disconnected, this,
            &MainWindow::onDisconnected);
    connect(tcpClient, &TcpClient::errorOccurred, this,
            &MainWindow::onErrorOccurred);
    // 连接定时器的超时信号到关闭LED的槽函数
    connect(ledTimer, &QTimer::timeout, this, &MainWindow::closeLed);

    connect(httpCar, &HttpCar::failedbord, this, &MainWindow::immobi);

}

MainWindow::~MainWindow() {
    camera->camera_uninit();
    delete ui;
}

void MainWindow::playAudio(const QString &ptahmusic)
{
    // 创建 QProcess 对象
       QProcess *process = new QProcess(this);

       // 设置要执行的命令
       QString program = "aplay";

       // 设置命令行参数
       QStringList arguments;
       arguments << ptahmusic;

       // 启动进程并传递参数
       process->start(program, arguments);

       // 检查是否成功启动
       if (!process->waitForStarted()) {
           qDebug() << "Failed to start aplay:" << process->errorString();
           return;
       }

       // 等待进程结束
       if (!process->waitForFinished()) {
           qDebug() << "Failed to finish aplay:" << process->errorString();
       } else {
           qDebug() << "Audio played successfully!";
       }
}


void MainWindow::updateTime() {
    // 获取当前系统时间
    QDateTime dateTime = QDateTime::currentDateTime();
    // 保存为 yyyyMMddHHmm:ss 格式的字符串
    currentTime = dateTime.toString("yyyyMMddHHmm:ss");
    // 将时间格式化为 "x月xx号 hh:mm"
    QString displayTime = dateTime.toString("M月d号 HH:mm");
    // 更新显示标签
    ui->timelab->setText("时间：" + displayTime);
}

void MainWindow::onWeatherInfoReceived(const QString &weatherInfo) {
    ui->watherlab->setText(weatherInfo);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 获取窗口的宽度和高度
    int width = this->width();

    // 创建一个从中间亮到两边暗的渐变
    QLinearGradient gradient(0, 0, width, 0);
    gradient.setColorAt(0.0, QColor(0, 0, 139));     // 深蓝色
    gradient.setColorAt(0.5, QColor(173, 216, 230)); // 淡蓝色
    gradient.setColorAt(1.0, QColor(0, 0, 139));     // 深蓝色

    // 使用渐变填充背景
    painter.fillRect(this->rect(), gradient);

    // 调用基类的paintEvent
    QMainWindow::paintEvent(event);
}


//入库按钮
void MainWindow::on_comeButton_clicked() {
    camera->save_image(); // 保存图像
    status = "come";

    QString imagePath = "new.jpg";
    httpCar->CarEnter(imagePath, [this](QByteArray response) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << response;
        if (jsonObj.contains("error")) {
            qDebug() << "Error occurred:" << jsonObj["error"].toString();
            status="error";
            qDebug()<<"display"<<status;
            return;
        }

        QString plateNumber;

        // 根据不同的 JSON 结构提取车牌号
        if (jsonObj.contains("plate")) {
            // 本地服务器响应
            plateNumber = jsonObj["plate"].toString();
        }
        J_plate = plateNumber;
        displayLicensePlate(J_plate);

    });
}


//出库按钮
void MainWindow::on_outButton_clicked() {
    camera->save_image(); // 保存图像
    status = "out";

    QString imagePath = "new.jpg";
    httpCar->CarExit(imagePath, [this](QByteArray response) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        qDebug()<<jsonObj;
        if (jsonObj.contains("error")) {
            qDebug() << "Error occurred:" << jsonObj["error"].toString();
            status="error";
            qDebug()<<"display"<<status;
            return;
        }

        QString plateNumber;

        // 根据不同的 JSON 结构提取车牌号
        if (jsonObj.contains("plate")) {
            // 本地服务器响应
            plateNumber = jsonObj["plate"].toString();
        }
        J_plate = plateNumber;

        displayLicensePlate(J_plate);

    });
}

void MainWindow::sendToTcp() {
    QString imagePath1 = "new.jpg";
    QString timestamp = getCurrentTimestamp(); // 获取当前时间戳

    QString base64Image1 = httpCar->getImageBase64(imagePath1);

    if (!base64Image1.isEmpty()) {
        QString jsonData =
        tcpClient->createJsonData(base64Image1, timestamp, J_plate, status);
        tcpClient->connectToServer("192.168.1.162", 50001); // 连接到服务器
        tcpClient->sendData(jsonData);                      // 发送数据
    } else {
        qDebug() << "Failed to convert images to base64.";
    }
}

void MainWindow::closeLed() {
    doorbar->closeLed();
    ledTimer->stop(); // 停止定时器
}

void MainWindow::getParkFee(const QString &plate)
{
    for (auto it = carList.begin(); it != carList.end(); ++it)
    {
        if (it->plateNumber == plate)
        {
                QString enterTimeStr = it->timestamp;
             QString currentTimeStr=getCurrentTimestamp();
               feeAmount = currentTimeStr.toLongLong()- enterTimeStr.toLongLong(); // 计算停留时间（毫秒）

            carList.erase(it); // 从链表中删除该车辆信息
            break;
        }
    }

}

void MainWindow::immobi(const QString &errorcode)
{
     qDebug() << "Error message received in MainWindow:" << errorcode;
     status="error";
}

// 滚动播报函数族群
void MainWindow::showScrollingText() {
    ui->TextLabel->clear();
    scrollPosition = 0;      // 重置滚动位置
    scrollTimer->start(500); // 设置滚动速度
}

void MainWindow::updateScrollText() {
    QString displayText =
        scrollText.mid(scrollPosition) + scrollText.left(scrollPosition);
    ui->TextLabel->setText(displayText);
    scrollPosition++;

    // 如果滚动位置超过文本长度，则重置滚动位置
    if (scrollPosition >= scrollText.length()) {
        scrollPosition = 0;
    }
}

void MainWindow::displayLicensePlate(const QString &plate) {

    QString settxt;
    if (status == "come") {
        // 停止滚动广告定时器
        scrollTimer->stop();
        settxt = plate + "\n 欢迎业主回家！";
        numOfPark = numOfPark - 1;
        numString = "剩余车位：" + QString::number(numOfPark);
        CarInfo newCar;
        newCar.plateNumber = J_plate;
        newCar.timestamp = getCurrentTimestamp();
        carList.append(newCar);
        ui->TextLabel->setText(settxt);
        playAudio("./huanyin.wav");
        ui->cheweilab->setText(numString);
        // 打开LED灯
        doorbar->openLed();
        // 设置定时器，6秒后关闭LED灯
        ledTimer->start(6000); // 6000 毫秒 = 6 秒
        // 10秒后重新显示滚动广告
        QTimer::singleShot(10000, this, &MainWindow::showScrollingText);
    }
    else if (status == "out")
    {
        // 停止滚动广告定时器
        scrollTimer->stop();
        // 执行与 "out" 相关的操作
        settxt = plate + "\n 应缴 " + QString::number(feeAmount) + "元";
        settxt = settxt + "\n 祝您一路顺风";
        numOfPark = numOfPark +1;
        numString = "剩余车位：" + QString::number(numOfPark);
        getParkFee(J_plate);
        ui->TextLabel->setText(settxt);
        playAudio("./yilu.wav");
        ui->cheweilab->setText(numString);
        // 打开LED灯
        doorbar->openLed();
        // 设置定时器，6秒后关闭LED灯
        ledTimer->start(6000); // 6000 毫秒 = 6 秒
        // 10秒后重新显示滚动广告
        QTimer::singleShot(10000, this, &MainWindow::showScrollingText);
    }
    else
    {
        qDebug() << "shibiecuowu";
    }   
}

// tcp函数族群
void MainWindow::onDataReceived(const QString &data) {
    //    ui->TextLabel->setText(data);
    qDebug() << "Received data:" << data;
    feeAmount = data.toInt();
    emit responseProcessed(J_plate);
}

void MainWindow::onDataSent(bool success) {
    if (success) {
        qDebug() << "Data sent successfully.";
    } else {
        qDebug() << "Failed to send data.";
    }
}

void MainWindow::onConnected() { qDebug() << "Connected to server."; }

void MainWindow::onDisconnected() { qDebug() << "Disconnected from server."; }

void MainWindow::onErrorOccurred(const QString &error) {
    qDebug() << "Error occurred:" << error;
}

QString MainWindow::getCurrentTimestamp() {
    QDateTime dateTime = QDateTime::currentDateTime();
    return QString::number(dateTime.toTime_t());
}
