#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include"gamewidget.h"

namespace Ui {
class LevelSelect;
}

class LevelSelect : public QWidget
{
    Q_OBJECT


public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();

    //重写绘图事件
    void paintEvent(QPaintEvent *);


signals:
    //自定义信号，告诉主场景，点击了返回
    void levelSelectBack();


private:
    Ui::LevelSelect *ui;
    GameWidget *currentGame = nullptr; // 当前游戏窗口指针
};

#endif // LEVELSELECT_H
