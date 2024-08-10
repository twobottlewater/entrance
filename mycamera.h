#ifndef MYCAMERA_H
#define MYCAMERA_H
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <linux/videodev2.h>  //跟V4L2架构相关的头文件，一定要加上
#include "jpeglib.h" //移植得到的jpeg头文件
#include <QThread>

#include <QMutex>
#include <QMutexLocker>

/*
    坑爹的地方：液晶屏分辨率800*480
                但是摄像头厂家出场设置，最大画面640*480
*/
#define W 640
#define H 480
/*
    知识点1：
       大体思路：实际写代码，步骤会多一些
            1.设置摄像头画面采集格式--》宽，高，画面是什么格式
            2.找摄像头的驱动申请缓冲区--》画面可以存放到缓冲区
            3.启动摄像头
    知识点2：应用程序如何跟摄像头的驱动相互通信(控制摄像头的驱动，给摄像头的驱动发送你的要求指令)
             ioctl()  -->作用ioctl - control device，给硬件设备的驱动发送控制指令来控制硬件
              #include <sys/ioctl.h>
              int ioctl(int fd, unsigned long request, ...);
                       返回值：成功 返回0  失败 -1
                         参数：fd --》硬件设备的文件描述符
                               request --》你要给这个硬件设备发送什么控制指令
*/
//定义一个结构体把每个缓冲块的大小和首地址保存
struct camerabuf
{
    void *start; //保存每个缓冲区的首地址
    int size; //保存每个缓冲区大小
};


class mycamera :public  QThread
{
public:
    mycamera();
    //初始化摄像头
    int camera_init();
    //关闭摄像头
    int camera_uninit();
    //摄像头捕捉画面预览
    int camera_preview();
    //摄像头捕捉画面保存成jpg图片
    int save_image();

    //重写qthrea父类的run函数
    void run();


private:
    int camerafd;
    int lcdfd;
    int *lcdmem; //保存液晶屏的首地址
    //分配缓冲区给你--》由于第三步你申请了四个缓冲区，分配就需要分配四次
    struct v4l2_buffer otherbuf;
    //定义结构体数组存放四个缓冲区的首地址和大小
    struct camerabuf array[4];
    enum v4l2_buf_type mytype=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    void display_rgb(char *rgbdata);
    QMutex mutex;
};

#endif // MYCAMERA_H
