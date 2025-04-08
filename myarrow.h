#ifndef MYARROW_H
#define MYARROW_H

#include<QWidget>
#include<QLabel>
#include<QTimer>
#include <QGraphicsEffect>

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

    // 开始移动箭头
    void startMove();

    //************************
    bool isActive() const { return m_isActive; }

    void setFailed();

    void deactivate() { m_isActive = false; }
    //**********************

    int track() const { return m_track; } // 获取轨道号

    void moveStep(int speed);//控制移动

signals:

    void arrowMissed();//箭头未被命中且移出屏幕时发射的信号


private:

    Direction m_direction;//当前箭头方向
    int m_track;//当前轨道
    bool m_isActive = true;//箭头激活状态

    bool m_isFailed=false;

    //控制移动参数
    //QTimer*m_moverTimer;//控制移动的定时器





private slots:
    // //定时器触发时的移动操作
    //  void moveStep();


};

#endif // MYARROW_H
