/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "responseProcessed"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "plate"
QT_MOC_LITERAL(4, 36, 10), // "updateTime"
QT_MOC_LITERAL(5, 47, 21), // "onWeatherInfoReceived"
QT_MOC_LITERAL(6, 69, 11), // "weatherInfo"
QT_MOC_LITERAL(7, 81, 17), // "showScrollingText"
QT_MOC_LITERAL(8, 99, 16), // "updateScrollText"
QT_MOC_LITERAL(9, 116, 19), // "displayLicensePlate"
QT_MOC_LITERAL(10, 136, 21), // "on_comeButton_clicked"
QT_MOC_LITERAL(11, 158, 20), // "on_outButton_clicked"
QT_MOC_LITERAL(12, 179, 14), // "onDataReceived"
QT_MOC_LITERAL(13, 194, 4), // "data"
QT_MOC_LITERAL(14, 199, 10), // "onDataSent"
QT_MOC_LITERAL(15, 210, 7), // "success"
QT_MOC_LITERAL(16, 218, 11), // "onConnected"
QT_MOC_LITERAL(17, 230, 14), // "onDisconnected"
QT_MOC_LITERAL(18, 245, 15), // "onErrorOccurred"
QT_MOC_LITERAL(19, 261, 5), // "error"
QT_MOC_LITERAL(20, 267, 19), // "getCurrentTimestamp"
QT_MOC_LITERAL(21, 287, 9), // "sendToTcp"
QT_MOC_LITERAL(22, 297, 8), // "closeLed"
QT_MOC_LITERAL(23, 306, 10), // "getParkFee"
QT_MOC_LITERAL(24, 317, 6), // "immobi"
QT_MOC_LITERAL(25, 324, 9) // "errorcode"

    },
    "MainWindow\0responseProcessed\0\0plate\0"
    "updateTime\0onWeatherInfoReceived\0"
    "weatherInfo\0showScrollingText\0"
    "updateScrollText\0displayLicensePlate\0"
    "on_comeButton_clicked\0on_outButton_clicked\0"
    "onDataReceived\0data\0onDataSent\0success\0"
    "onConnected\0onDisconnected\0onErrorOccurred\0"
    "error\0getCurrentTimestamp\0sendToTcp\0"
    "closeLed\0getParkFee\0immobi\0errorcode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  107,    2, 0x08 /* Private */,
       5,    1,  108,    2, 0x08 /* Private */,
       7,    0,  111,    2, 0x08 /* Private */,
       8,    0,  112,    2, 0x08 /* Private */,
       9,    1,  113,    2, 0x08 /* Private */,
      10,    0,  116,    2, 0x08 /* Private */,
      11,    0,  117,    2, 0x08 /* Private */,
      12,    1,  118,    2, 0x08 /* Private */,
      14,    1,  121,    2, 0x08 /* Private */,
      16,    0,  124,    2, 0x08 /* Private */,
      17,    0,  125,    2, 0x08 /* Private */,
      18,    1,  126,    2, 0x08 /* Private */,
      20,    0,  129,    2, 0x08 /* Private */,
      21,    0,  130,    2, 0x08 /* Private */,
      22,    0,  131,    2, 0x08 /* Private */,
      23,    1,  132,    2, 0x08 /* Private */,
      24,    1,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   25,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->responseProcessed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateTime(); break;
        case 2: _t->onWeatherInfoReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->showScrollingText(); break;
        case 4: _t->updateScrollText(); break;
        case 5: _t->displayLicensePlate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_comeButton_clicked(); break;
        case 7: _t->on_outButton_clicked(); break;
        case 8: _t->onDataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onDataSent((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onDisconnected(); break;
        case 12: _t->onErrorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: { QString _r = _t->getCurrentTimestamp();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: _t->sendToTcp(); break;
        case 15: _t->closeLed(); break;
        case 16: _t->getParkFee((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->immobi((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::responseProcessed)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::responseProcessed(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
