#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg ="");

    QString normalImgPath;
    QString pressImgPath;

    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;


};

#endif // MYPUSHBUTTON_H
