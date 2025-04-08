#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<myarrow.h>
#include"QMediaPlayer"
#include"QAudioOutput"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:

    PlayScene(int levelnum);
    ~PlayScene();

    int levelIndex;//记录选择关卡


    int m_judgelineY=400;//判断线

    // // 四个轨道的中心X坐标（从左到右0-3）
    //     int m_trackPositions[4] = {175,325,475,625};

    // 分数系统
    int m_score = 0;



    void paintEvent(QPaintEvent*);

signals:

    //自定义信号，告诉关卡场景，点击了返回
    void playSceneBack();


private:

     // 统一定时器
    QTimer *m_unifiedTimer;
    QTimer*testTimer;

    int m_moveSpeed = 5; // 全局移动速度，后期更改，两首歌不一样

    // 箭头存储用QList
    QList<MyArrow*> m_activeArrows;
    //

    void moveAllArrows();//移动箭头

    // 轨道方向映射表（轨道号 -> 箭头方向）
    const QMap<int, MyArrow::Direction> TRACK_DIRECTION_MAP = {
        {0, MyArrow::U},
        {1, MyArrow::D},
        {2, MyArrow::L},
        {3, MyArrow::R}
    };

    // 定义按键到轨道的映射表
    const QMap<int, int> keyTrackMap = {
        {Qt::Key_Up,    0},  // 上键对应轨道0
        {Qt::Key_Down,  1},  // 下键对应轨道1
        {Qt::Key_Left,  2},  // 左键对应轨道2
        {Qt::Key_Right, 3}   // 右键对应轨道3
    };

    void keyPressEvent(QKeyEvent *event);


    //创造新的箭头
    void createArrow(int track);

    //生成箭头测试
    void createTestPattern();

    //碰撞检测，上1 下2 左3 右4
    void checkCollision(int keyTrack);

    //处理击中箭头
    void handleHit(MyArrow *arrow);

    //处理为击中箭头
    void handleMiss(MyArrow *arrow);




    //下一阶段
    //游戏音乐
    void setBackMusic();
    QMediaPlayer*musicPlayer=nullptr;

    //结算界面
    QWidget*resultWidget=nullptr;

    //停计时器
    QTimer*stopTimer=nullptr;






};

#endif // PLAYSCENE_H
