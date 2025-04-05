#ifndef MYARROW_H
#define MYARROW_H

#include<QWidget>
#include<QLabel>
#include<QTimer>

class MyArrow : public QLabel//实现可视化箭头
{
    Q_OBJECT
public:
    //定义箭头枚举类型
    enum Direction{
        U,//上up
        D,//down
        L,//left
        R//right
    };

    //构造函数
    explicit MyArrow(Direction dir,int track,QWidget*parent=nullptr);





signals:



private:
    Direction m_direction;//当前箭头方向
    int m_track;//当前轨道

    //控制移动参数
    //QTimer*m_moverTimer;//控制移动的定时器

    static const int MOVE_INTERVAL=16;//移动间隔16ms
    static const int MOVE_SPEED=5;//移动5个像素


private slots:
    //定时器触发时的移动操作
    // void moveStep();


};

#endif // MYARROW_H
