#ifndef SURPRISE_H
#define SURPRISE_H

#include <QMainWindow>
#include"QPainter"
#include"QPixmap"
#include"QLabel"

#include"QDebug"

#include"QMediaPlayer"
#include"QAudioOutput"
#include<QKeyEvent>
#include<mainmenu.h>
#include<qmediaplayer.h>
#include<QPropertyAnimation>

class Surprise : public QMainWindow
{
    Q_OBJECT


public:

    explicit Surprise(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);


    //图片展示场景的对象指针
    Surprise*photo=NULL;

    //结束图片
    QLabel*photoLabel=new QLabel;
    QPixmap photoPix;

    int index=0;

    QString imgPath;

    void photoSwitch();
    //图片
    QPropertyAnimation*photoAnimation=new QPropertyAnimation(photoLabel,"geometry");

    void mousePressEvent(QMouseEvent *);


signals:
    void surpriseBack();

};

#endif // SURPRISE_H
