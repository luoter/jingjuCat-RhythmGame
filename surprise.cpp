#include "surprise.h"
#include"QPainter"
#include"QPixmap"
#include"QLabel"
#include"QDebug"
#include<QKeyEvent>
#include<QTimer>



Surprise::Surprise(QWidget *parent)
    : QMainWindow{parent}
{
    //设置标题
    this->setWindowTitle("surprise");
    this->setWindowIcon(QPixmap(":/forzhuye/picture1/jingjulogo4.png"));
    this->setFixedSize(1280,720);


    //防置阻碍鼠标事件
    photoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    photoSwitch();


    photoLabel->setGeometry(0,0,1280,720);

    photoLabel->setParent(this);
    photoLabel->move(0,-720);



    photoAnimation->setDuration(1500);
    //开始位置
    photoAnimation->setStartValue(QRect(photoLabel->x(),photoLabel->y(),photoLabel->width(),photoLabel->height()));
    //结束位置
    photoAnimation->setEndValue(QRect(photoLabel->x(),photoLabel->y()+720,photoLabel->width(),photoLabel->height()));
    //设置缓和曲线
    photoAnimation->setEasingCurve(QEasingCurve::OutCubic);


}



void Surprise::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap bg(":/surprise/picture1/IMG_20250412_212658.png");
    painter.drawPixmap(0, 0, width(), height(), bg);
}



void Surprise::photoSwitch(){
    //定时器
    QTimer*photoTimer=new QTimer(this);

    photoTimer->start(2000);

    //变化
    connect(photoTimer, &QTimer::timeout, [=](){

        imgPath = QString(":/surprise/surprise/%1.png").arg(index);

        photoPix.load(imgPath);

        photoLabel->setPixmap(photoPix);
        photoLabel->setScaledContents(true);
        photoAnimation->start();
        index=index+1;

        if(index>=29){//可更改
            photoTimer->stop();
        }
    });

}


void Surprise::mousePressEvent(QMouseEvent *event){

    if(index>=0){//可更改

        photoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 允许点击穿透

        QWidget::mousePressEvent(event);

        emit  surpriseBack();

    }
}
