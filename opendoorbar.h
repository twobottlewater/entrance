#ifndef OPENDOORBAR_H
#define OPENDOORBAR_H

#include <QObject>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
class OpenDoorbar : public QObject
{
    Q_OBJECT
public:
    explicit OpenDoorbar(QObject *parent = nullptr);
    void openLed();
    void closeLed();

signals:


private:
    int ledfd;

};

#endif // OPENDOORBAR_H
