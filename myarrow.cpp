#include "myarrow.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"
#include"QPushButton"
#include"QTimer"
#include"QMediaPlayer"
#include"QAudioOutput"
#include<playscene.h>

MyArrow::MyArrow(Direction dir,int track,QWidget*parent)
    :QLabel(parent),m_direction(dir),m_track(track)
{

    QString imgPath;
    switch(dir){
    case(U):
        imgPath=":/arrow/picture1/1.png";
        break;
    case(D):
        imgPath=":/arrow/picture1/arrowb2.png";
        break;
    case(L):
        imgPath=":/arrow/picture1/arrowleft2.png";
        break;
    case(R):
        imgPath=":/arrow/picture1/arrowright2.png";
        break;
    }

    //更改箭头大小
    setPixmap(QPixmap(imgPath).scaled(30,30,Qt::KeepAspectRatio));
    setAlignment(Qt::AlignCenter);



    // // 加上阴影，区分重叠箭头
    // QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    // shadow->setBlurRadius(10);
    // shadow->setColor(Qt::yellow);
    // shadow->setOffset(2, 2);
    // setGraphicsEffect(shadow);
    // 确保新箭头显示在最上层
    // setAttribute(Qt::WA_TranslucentBackground);
    // raise();


}


// 开始移动方法
void MyArrow::startMove()
{
    // // 计算初始X坐标：轨道中心 - 箭头宽度/2  - width()/2
    // int initX = 400;

    // // 设置初始位置在屏幕上方
    // move(initX, 75);

    // 初始化位置逻辑，箭头x坐标=100（最左轨道x坐标）+轨道宽度*轨道号（0,1,2,3）+轨道宽一半-箭头宽一半
    const int trackWidth = 150;
    move(trackWidth * m_track + trackWidth/2+100 - width()/2, 75);


    // 显示箭头
    show();


}




void MyArrow::moveStep(int speed)
{
    // 垂直移动逻辑
    move(x(), y() + speed);

    // 超出屏幕处理
    if(y() > 480 ) {

        if(m_isActive)
            emit arrowMissed(); // 只有激活状态，且超出475才触发未命中

        deleteLater(); // 删除
    }
}

void MyArrow::setFailed() {
    m_isFailed = true;

    setPixmap(QPixmap(":/arrow/picture1/arrowup2.png").scaled(100,100,Qt::KeepAspectRatio));
}


