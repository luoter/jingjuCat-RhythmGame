#include "mypushbutton.h"
#include"QDebug"

// MyPushButton::MyPushButton(QWidget *parent)
//     : QPushButton{parent}
// {}


MyPushButton::MyPushButton(QString normalImg,QString pressImg )
{
    this ->normalImgPath=normalImg;
    this ->pressImgPath=pressImg;


    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;

    }

    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());

    //设置样式
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));



}

void MyPushButton:: mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;

        }

        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    //让父类执行其他操作
    return QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;

        }

        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());

        //设置样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }


    return QPushButton::mouseReleaseEvent(e);
}
