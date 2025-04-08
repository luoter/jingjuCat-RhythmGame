#include "playscene.h"
#include"QPainter"
#include"QPixmap"
#include"QLabel"
#include"mypushbutton.h"
#include"QDebug"
#include<myarrow.h>
#include"QMediaPlayer"
#include"QAudioOutput"
#include<QKeyEvent>
#include<mainmenu.h>
#include<qmediaplayer.h>

PlayScene::PlayScene(int levelnum)
{
    this->setWindowIcon(QPixmap(":/forzhuye/picture1/jingjulogo4.png"));
    this->levelIndex=levelnum;


    //初始化游戏场景
    //设置初始大小
    this->setFixedSize(800,600);


    //返回按钮
    MyPushButton*backBtn=new MyPushButton(":/forselect/picture1/back5.png");
    backBtn->setParent(this);
    backBtn->move(this->width()*0.05,this->height()*0.85);
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){

        //发送信号
        emit this ->playSceneBack();

    });


    //显示轨道
    for(int i=0;i<4;i++){
        QLabel*label=new QLabel;
        label->setGeometry(0,0,150,450);
        label->setPixmap(QPixmap(":/forplayscene/picture1/track2.png"));
        label->setParent(this);
        label->move(100+150*i,75);//轨道坐标
        label->lower();

    }




    // 统一定时器初始化**********************
    m_unifiedTimer = new QTimer(this);
    connect(m_unifiedTimer, &QTimer::timeout, this, &PlayScene::moveAllArrows);

    m_unifiedTimer->start(10);//定时器，每0.01秒箭头移动

    //设置键盘事件
    // 设置窗口可接收键盘事件
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();  // 获取焦点




    // 测试代码：每秒生成随机箭头
    testTimer = new QTimer(this);
    connect(testTimer, &QTimer::timeout, [=](){
        // srand(time(NULL));
        // 随机生成方向和轨道
        createArrow(rand()%4 );
    });
    testTimer->start(450);  // 间隔0.45秒


    if(levelIndex==1){
        //设置标题
        this->setWindowTitle("《京剧猫》，加油( ´ ▽ ` )ノ");

        }

        if(levelIndex==2){
            //设置标题
            this->setWindowTitle("《飘荡》，你可以的┐(￣ヮ￣)┌");
        }



    //音乐有关
    setBackMusic();


    //停止生成


    QTimer*jishi=new QTimer(this);
    jishi->start(5000);


    connect(jishi,&QTimer::timeout,[=](){



            stopTimer=new QTimer(this);
            stopTimer->setSingleShot(true);
            stopTimer->start();
            connect(stopTimer,&QTimer::timeout,[=](){
                testTimer->stop();
                // m_unifiedTimer->stop();

                qDebug()<<"停止生成箭头";
            });

            jishi->stop();

    });





        musicPlayer->play();


}

//游戏界面背景
void PlayScene::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/forplayscene/picture1/gameground.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //判定线
    QPainter painter1(this);
    painter1.setPen(QPen(Qt::darkGreen, 3, Qt::DashLine));
    painter1.drawLine(75, 400, 725,400 );



}

//音乐
void PlayScene::setBackMusic(){

    musicPlayer=new QMediaPlayer(this);
    QAudioOutput*audioOutput=new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);

    QString musicPath=(levelIndex==1)
    ?"qrc:/sound/picture1/jingjumao.mp3"
    :"qrc:/sound/picture1/piaodang.mp3";

    musicPlayer->setSource(QUrl(musicPath));
    audioOutput->setVolume(30);



}

//新的析构函数
PlayScene::~PlayScene() {
    if(testTimer) {
        testTimer->stop();
        delete testTimer;
    }
    if(stopTimer) {
        stopTimer->stop();
        delete stopTimer;
    }
}


//统一移动所有活动箭头
void PlayScene::moveAllArrows()
{
    // 使用for循环遍历所有激活箭头
    for(MyArrow *arrow : m_activeArrows) {
        arrow->moveStep(m_moveSpeed);

        // 检查是否未命中且超过判定线
        if (arrow->isActive() && arrow->y() > m_judgelineY +1) {

            arrow->deactivate();

        }


    }

    // 自动清理无效指针
    m_activeArrows.erase(
        std::remove_if(m_activeArrows.begin(), m_activeArrows.end(),
        [](MyArrow* arrow) { return !arrow || !arrow->isVisible(); }),
        m_activeArrows.end()
        );


}

//创建箭头
void PlayScene::createArrow(int track)
{
    // 根据轨道号获取对应方向
    MyArrow::Direction dir = TRACK_DIRECTION_MAP.value(track);

    MyArrow *arrow = new MyArrow(dir, track, this);

    // 开始移动箭头
    arrow->startMove();

    // 连接信号
    connect(arrow, &MyArrow::arrowMissed, [=](){
        qDebug() << "Missed"<<dir<<" arrow at track:" << track;
    });

    // 窗口退出，移除所有箭头
    connect(arrow, &MyArrow::destroyed, [=](){
        m_activeArrows.removeAll(arrow);
    });



    m_activeArrows.append(arrow);//生成的箭头加入列表

}

// 键盘事件处理
    void PlayScene::keyPressEvent(QKeyEvent *event)
{

    if(!keyTrackMap.contains(event->key())) return;

    const int track = keyTrackMap[event->key()];

    checkCollision(track);
}






//碰撞检测，判定是否成功点击按键
void PlayScene::checkCollision(int track)
{
    const int judgeRange = 1;
    bool hit = false;//一开始的撞击状态

    // 只检测对应轨道的箭头
    for(MyArrow *arrow : m_activeArrows) {

        if(arrow->track() != track&&arrow->isActive()) break;

        if(arrow->isActive() &&
            (  m_judgelineY-arrow->y()) > judgeRange)
        {
            handleHit(arrow);
            hit = true;
            break; // 每个按键只命中一个箭头
        }


    }

    if(!hit) handleMiss(m_activeArrows[0]);


}


//命中处理
void PlayScene::handleHit(MyArrow *arrow)
{
    arrow->deactivate();

    arrow->hide();

    arrow->deleteLater();

    m_score += 100;

    qDebug() << "Perfect hit! Current score:" << m_score;
}

// 未命中处理
void PlayScene::handleMiss(MyArrow *arrow)
{
    m_score = qMax(0, m_score - 200);

    if(arrow->y()<m_judgelineY){

        arrow->setFailed();

        arrow->deactivate();

        m_activeArrows.removeAll(arrow);

        QTimer::singleShot(2000,this,[=](){

            arrow->hide();

            arrow->deleteLater();

        });


        qDebug() << "Miss! Current score:" << m_score;

    }



}


//测试箭头实现
void PlayScene::createTestPattern()
{
    srand(time(nullptr));

    // 轨道0
    QTimer::singleShot(500, [=](){ createArrow(0); });
    QTimer::singleShot(800, [=](){ createArrow(0); });

    QTimer::singleShot(rand()%4000+1000, [=](){ createArrow(0); });

    // 轨道1
    for(int i=0; i<3; i++) {
        QTimer::singleShot(4000 + i*100, [=](){ createArrow(1); });

    }
    QTimer::singleShot(rand()%2000, [=](){ createArrow(1); });

    // 轨道2
    QTimer::singleShot(1900, [=](){ createArrow(2); });
    QTimer::singleShot(1300, [=](){ createArrow(2); });

    QTimer::singleShot(rand()%1000+1000, [=](){ createArrow(2); });

    // 轨道3
    QTimer::singleShot(1000, [=](){ createArrow(3); });

    QTimer::singleShot(rand()%4000+500, [=](){ createArrow(3); });
}



//音乐播放
// void PlayScene::startGame(int levelnum) {
//     // 音乐播放器初始化
//     m_musicPlayer = new QMediaPlayer(this);
//     QAudioOutput *audioOutput = new QAudioOutput(this);
//     m_musicPlayer->setAudioOutput(audioOutput);
//     m_musicPlayer->setSource(QUrl("qrc:/music/game.mp3"));
//     m_musicPlayer->play();
// }

