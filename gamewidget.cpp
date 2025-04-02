#include "gamewidget.h"
#include <QDebug>



GameWidget::GameWidget(int level, QWidget *parent)
    : QWidget(parent), currentLevel(level) {
    setFixedSize(800, 600);

    //设置背景
    QLabel *bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/image_forzhuye/sucai1.png"));//要改*****
    bg->setGeometry(0, 0, width(), height());


//     // 初始化计时器
//     gameTimer = new QTimer(this);
//     connect(gameTimer, &QTimer::timeout, this, &GameWidget::updateArrows);
//     gameTimer->start(50); // 每50ms更新


//     // 测试箭头生成
//     loadTestArrow();

//     // // 初始化音乐（示例）
//     // musicPlayer = new QMediaPlayer(this);
//     // musicPlayer->setMedia(QUrl("qrc:/sounds/bgm/theme.mp3"));
//     // musicPlayer->play();
// }



// //仅测试生成箭头
// void GameWidget::loadTestArrow() {
//     // 在轨道1（中间左侧）生成测试箭头
//     QLabel *arrow = new QLabel(this);
//     //加入箭头图片
//     arrow->setPixmap(QPixmap(":/images/arrow_up.png"));
//     arrow->move(200, 0); // 轨道位置需要根据实际布局调整
//     arrows.append({arrow, 1, true});
// }

// //箭头移动
// void GameWidget::updateArrows() {
//     // 移动所有箭头
//     for(auto &arrow : arrows) {
//         arrow.label->move(arrow.label->x(), arrow.label->y() + 5);

//         // 碰撞检测（基础版）？？？？？？
//         if(arrow.label->y() > judgeLineY + 30) {
//             if(arrow.isActive) failedCount++;
//             arrow.label->deleteLater();
//             arrows.removeOne(arrow);
//         }
//     }
//     update(); // 触发重绘
// }


// void GameWidget::keyPressEvent(QKeyEvent *event) {
//     const int keyTrackMap[] = {
//         Qt::Key_Left,   // Track 0
//         Qt::Key_Up,     // Track 1
//         Qt::Key_Down,   // Track 2
//         Qt::Key_Right   // Track 3
//     };

//     // 查找匹配的箭头
//     for(auto &arrow : arrows) {
//         if(arrow.isActive &&
//             event->key() == keyTrackMap[arrow.track] &&
//             qAbs(arrow.label->y() - judgeLineY) < 30)
//         {
//             arrow.label->setPixmap(QPixmap(":/images/hit_effect.png"));
//             arrow.isActive = false;
//             return;
//         }
//     }

//     // 未命中处理
//     failedCount++;
//     qDebug() << "Miss! Total fails:" << failedCount;
 }



