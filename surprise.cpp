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

        switch(index){
        case(0):
            imgPath=":/surprise/surprise/0.png";
            break;

        case(1):
            imgPath=":/surprise/surprise/1.png";
            break;
        case(2):
            imgPath=":/surprise/surprise/2.png";
            break;
        case(3):
            imgPath=":/surprise/surprise/3.png";
            break;
        case(4):
            imgPath=":/surprise/surprise/4.png";
            break;
        case(5):
            imgPath=":/surprise/surprise/5.png";
            break;
        case(6):
            imgPath=":/surprise/surprise/6.png";
            break;
        case(7):
            imgPath=":/surprise/surprise/7.png";
            break;
        case(8):
            imgPath=":/surprise/surprise/8.png";
            break;
        case(9):
            imgPath=":/surprise/surprise/9.png";
            break;
        case(10):
            imgPath=":/surprise/surprise/10.png";
            break;
        case(11):
            imgPath=":/surprise/surprise/11.png";
            break;
        case(12):
            imgPath=":/surprise/surprise/12.png";
            break;
        case(13):
            imgPath=":/surprise/surprise/13.png";
            break;
        case(14):
            imgPath=":/surprise/surprise/14.png";
            break;
        case(15):
            imgPath=":/surprise/surprise/15.png";
            break;
        case(16):
            imgPath=":/surprise/surprise/16.png";
            break;
        case(17):
            imgPath=":/surprise/surprise/17.png";
            break;
        case(18):
            imgPath=":/surprise/surprise/18.png";
            break;
        case(19):
            imgPath=":/surprise/surprise/19.png";
            break;
        case(20):
            imgPath=":/surprise/surprise/20.png";
            break;
        case(21):
            imgPath=":/surprise/surprise/21.png";
            break;
        case(22):
            imgPath=":/surprise/surprise/22.png";
            break;
        case(23):
            imgPath=":/surprise/surprise/23.png";
            break;
        case(24):
            imgPath=":/surprise/surprise/24.png";
            break;
        case(25):
            imgPath=":/surprise/surprise/25.png";
            break;
        case(26):
            imgPath=":/surprise/surprise/26.png";
            break;
        case(27):
            imgPath=":/surprise/surprise/27.png";
            break;
        case(28):
            imgPath=":/surprise/surprise/28.png";
            photoTimer->stop();
            break;
        }



        photoPix.load(imgPath);

        photoLabel->setPixmap(photoPix);
        photoLabel->setScaledContents(true);
        photoAnimation->start();
        index=index+1;
        qDebug()<<index;
    });

}


void Surprise::mousePressEvent(QMouseEvent *event){

    if(index>=28){

        photoLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 允许点击穿透

        QWidget::mousePressEvent(event);

        emit  surpriseBack();

    }
}
