/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *comeButton;
    QPushButton *outButton;
    QPushButton *testBt;
    QLabel *TextLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *timelab;
    QLabel *watherlab;
    QLabel *cheweilab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        comeButton = new QPushButton(centralwidget);
        comeButton->setObjectName(QStringLiteral("comeButton"));
        comeButton->setGeometry(QRect(20, 340, 111, 51));
        comeButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(10, 10, 35);\n"
"font-weight: bold; \n"
" border: none;\n"
"border-radius: 18px;"));
        outButton = new QPushButton(centralwidget);
        outButton->setObjectName(QStringLiteral("outButton"));
        outButton->setGeometry(QRect(20, 400, 111, 51));
        outButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(10, 10, 35);\n"
"font-weight: bold; \n"
" border: none;\n"
"border-radius: 18px;"));
        testBt = new QPushButton(centralwidget);
        testBt->setObjectName(QStringLiteral("testBt"));
        testBt->setGeometry(QRect(20, 280, 111, 51));
        testBt->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(10, 10, 35);\n"
"font-weight: bold; \n"
" border: none;\n"
"border-radius: 18px;"));
        TextLabel = new QLabel(centralwidget);
        TextLabel->setObjectName(QStringLiteral("TextLabel"));
        TextLabel->setGeometry(QRect(180, 250, 481, 221));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(22);
        TextLabel->setFont(font);
        TextLabel->setStyleSheet(QStringLiteral("color: rgb(255, 14, 98);"));
        TextLabel->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 13, 351, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        timelab = new QLabel(layoutWidget);
        timelab->setObjectName(QStringLiteral("timelab"));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        timelab->setFont(font1);
        timelab->setStyleSheet(QStringLiteral("color: rgb(255, 247, 0);"));

        verticalLayout->addWidget(timelab);

        watherlab = new QLabel(layoutWidget);
        watherlab->setObjectName(QStringLiteral("watherlab"));
        watherlab->setFont(font1);
        watherlab->setStyleSheet(QStringLiteral("color: rgb(255, 247, 0);"));

        verticalLayout->addWidget(watherlab);

        cheweilab = new QLabel(layoutWidget);
        cheweilab->setObjectName(QStringLiteral("cheweilab"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(20);
        font2.setBold(false);
        font2.setWeight(50);
        cheweilab->setFont(font2);
        cheweilab->setStyleSheet(QStringLiteral("color: rgb(255, 12, 0);"));
        cheweilab->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(cheweilab);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        comeButton->setText(QApplication::translate("MainWindow", "\345\205\245\345\272\223", 0));
        outButton->setText(QApplication::translate("MainWindow", "\345\207\272\345\272\223", 0));
        testBt->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\346\214\211\351\222\256", 0));
        TextLabel->setText(QApplication::translate("MainWindow", "\346\260\270\350\277\234\350\267\237\345\205\232\350\265\260", 0));
        timelab->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", 0));
        watherlab->setText(QApplication::translate("MainWindow", "\345\244\251\346\260\224\357\274\232", 0));
        cheweilab->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\350\275\246\344\275\215\357\274\23299", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
