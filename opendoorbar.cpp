#include "opendoorbar.h"
#include<QDebug>
OpenDoorbar::OpenDoorbar(QObject *parent) : QObject(parent)
{
    ledfd=::open("/dev/led_drv",O_RDWR);
    if(ledfd == -1)
        {
          qDebug()<<"open";
            return ;
    }
}

void OpenDoorbar::openLed()
{
    char buf[2];
    buf[0] = 1; //关灯
    buf[1] = 8;
    ::write(ledfd,buf,sizeof(buf));

}

void OpenDoorbar::closeLed()
{       
    char buf[2];
    buf[0] = 0; //关灯
    buf[1] = 8;
    ::write(ledfd,buf,sizeof(buf));
}
