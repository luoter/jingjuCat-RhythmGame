#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H


#pragma once//?
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QMediaPlayer>
#include <QObject>
#include <QQuickItem>



class GameWidget : public QWidget

{
    Q_OBJECT
    QML_ELEMENT




public:
    // 接收关卡编号
    explicit GameWidget(int level, QWidget *parent = nullptr);
    ~GameWidget();


protected:
    //按键事件
    void keyPressEvent(QKeyEvent *event) override;
    //背景填充
    void paintEvent(QPaintEvent *event) override;


private slots:
    //更新箭头
    void updateArrows();

private://箭头类
    struct Arrow {

        // 箭头显示对象
        QLabel *label;
        // 轨道编号（0-3对应左、上、下、右）
        int track;
        // 是否可被击中
        bool isActive;

    };

    //QTime对象gameTimer计时
    QTimer *gameTimer;
    //播放器对象
    QMediaPlayer *musicPlayer;
    //箭头列表
    QList<Arrow> arrows;
    //关卡
    int currentLevel;
    //失败次数统计
    int failedCount = 0;
    //分解线坐标
    const int judgeLineY = 500; // 判定线Y坐标

    void loadTestArrow(); // 测试用箭头生成

signals:
    //游戏结束处理
    void gameFinished(bool isWin);

private:
    void showResult(bool isWin);

};

#endif // GAMEWIDGET_H
