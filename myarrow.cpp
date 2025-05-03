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
        imgPath=":/arrow/picture1/arrowone.png";
        break;
    case(D):
        imgPath=":/arrow/picture1/arrowtwe.png";
        break;
    case(L):
        imgPath=":/arrow/picture1/arrowthree.png";
        break;
    case(R):
        imgPath=":/arrow/picture1/arrowfour.png";
        break;
    }

    //更改箭头大小
    setPixmap(QPixmap(imgPath).scaled(40,40,Qt::KeepAspectRatio));
    setAlignment(Qt::AlignCenter);


}


// 开始移动方法
void MyArrow::startMove()
{

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

    setPixmap(QPixmap(":/arrow/picture1/arrowfail.png").scaled(45,45,Qt::KeepAspectRatio));
}


