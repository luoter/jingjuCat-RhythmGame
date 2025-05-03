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
#include<QPropertyAnimation>

PlayScene::PlayScene(int levelnum)
{
    this->setWindowIcon(QPixmap(":/forzhuye/picture1/jingjulogo4.png"));
    this->levelIndex=levelnum;

    //设置初始大小
    this->setFixedSize(800,600);
    //背景音乐有关
    setBackMusic();

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


    // 统一定时器初始化
    m_unifiedTimer = new QTimer(this);
    m_unifiedTimer->start(16);//定时器，每0.16秒箭头移动
    connect(m_unifiedTimer, &QTimer::timeout, this, &PlayScene::moveAllArrows);


    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();  // 获取焦点


    //结束图片
    QLabel*finishLabel=new QLabel;

    //阻碍鼠标事件
    finishLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    QPixmap finishPix;
    finishPix.load(":/forplayscene/picture1/finish3.png");
    finishLabel->setGeometry(0,0,finishPix.width(),finishPix.height());
    finishLabel->setPixmap(finishPix);//不能将finishPix设为指针，因为这个函数要求const参数
    finishLabel->setParent(this);
    finishLabel->move((this->width()-finishPix.width())*0.5,-finishPix.height());



    //结束后出现结束图片
    QPropertyAnimation*finish=new QPropertyAnimation(finishLabel,"geometry");
    //设置间隔
    finish->setDuration(5000);
    //开始位置
    finish->setStartValue(QRect(finishLabel->x(),finishLabel->y(),finishLabel->width(),finishLabel->height()));
    //结束位置
    finish->setEndValue(QRect(finishLabel->x(),finishLabel->y()+600,finishLabel->width(),finishLabel->height()));
    //设置缓和曲线
    finish->setEasingCurve(QEasingCurve::OutCubic);


    //进入关卡1
    if(levelIndex==1){
        //设置标题
        this->setWindowTitle("《京剧猫》，加油( ´ ▽ ` )ノ");

        // 测试代码：每秒生成随机箭头
        testTimer = new QTimer(this);
        testTimer->start(500);  // 间隔0.5秒
        connect(testTimer, &QTimer::timeout, [=](){

            // 随机生成方向和轨道
            createArrow(rand()%4 );
        });

        //结算计时
        QTimer*jishi=new QTimer(this);
        jishi->start(167000);

        connect(jishi,&QTimer::timeout,[=](){

            testTimer->stop();
            jishi->stop();
            //播放音效
            finishMusic();


            stopTimer=new QTimer(this);
            stopTimer->start(7000);
            connect(stopTimer,&QTimer::timeout,[=](){

                //结束动画
                finish->start();

                this->setWindowTitle("加油加油加油！！！");

                connect(finish, &QPropertyAnimation::finished, [=]() {
                    m_isAnimationFinished = true;    // 标记动画完成
                    finishLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 允许点击穿透
                    finish->stop();
                });

                stopTimer->stop();
            });

        });

        }

        //关卡二
        if(levelIndex==2){
            //设置标题
            this->setWindowTitle("《飘荡》，你可以的┐(￣ヮ￣)┌");

            // 测试代码：每秒生成随机箭头
            testTimer = new QTimer(this);
            testTimer->start(600);  // 间隔0.6秒
            connect(testTimer, &QTimer::timeout, [=](){

                // 随机生成方向和轨道
                createArrow(rand()%4 );
            });


            //停止生成，不知道为什么duration 用不了，只能用定时器了
            QTimer*jishi=new QTimer(this);
            jishi->start(137000);

            connect(jishi,&QTimer::timeout,[=](){

            testTimer->stop();
            jishi->stop();
            //播放音效
            finishMusic();


            stopTimer=new QTimer(this);
            stopTimer->start(7000);
            connect(stopTimer,&QTimer::timeout,[=](){

                //结束动画
                finish->start();

                this->setWindowTitle("加油加油加油！！！");

                connect(finish, &QPropertyAnimation::finished, [=]() {
                    m_isAnimationFinished = true;    // 标记动画完成
                    finishLabel->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 允许点击穿透
                    finish->stop();
                });

                stopTimer->stop();
            });

            });

        }






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

    musicPlayer->play();

}

void PlayScene::finishMusic(){

    finishPlayer=new QMediaPlayer(this);
    QAudioOutput*finishOutput=new QAudioOutput(this);
    finishPlayer->setAudioOutput(finishOutput);

    finishPlayer->setSource(QUrl("qrc:/sound/picture1/kaichang.mp3"));
    finishOutput->setVolume(30);
    finishPlayer->play();
}

//析构函数
PlayScene::~PlayScene() {
    if(testTimer) {
        testTimer->stop();
        delete testTimer;
    }
    // if(stopTimer) {
    //     stopTimer->stop();
    //     delete stopTimer;
    // }
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
        arrow->deactivate();
        qDebug() << "Missed"<<dir;
    });

    // 窗口退出，移除所有箭头
    connect(arrow, &MyArrow::destroyed, [=](){
        m_activeArrows.removeAll(arrow);
    });

    m_activeArrows.append(arrow);//生成的箭头加入列表

}

//键盘事件处理
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

    if(!hit) handleMiss(m_activeArrows[0]);//保证只与最近箭头匹配
}

//命中
void PlayScene::handleHit(MyArrow *arrow)
{
    arrow->deactivate();

    arrow->hide();

    arrow->deleteLater();
}

// 未命中
void PlayScene::handleMiss(MyArrow *arrow)
{
    if(arrow->y()<m_judgelineY){
        arrow->setFailed();
        arrow->deactivate();
        m_activeArrows.removeAll(arrow);
        QTimer::singleShot(2000,this,[=](){
            arrow->hide();
            arrow->deleteLater();
        });
    }
}

//箭头随机生成
void PlayScene::createTestPattern()
{
    srand(time(nullptr));

    // 轨道0
    QTimer::singleShot(3500, [=](){ createArrow(0); });
    QTimer::singleShot(10000, [=](){ createArrow(0); });

    QTimer::singleShot(rand()%4000+1000, [=](){ createArrow(0); });

    // 轨道1
    for(int i=0; i<3; i++) {
        QTimer::singleShot(9000 + i*100, [=](){ createArrow(1); });

    }
    QTimer::singleShot(rand()%4000, [=](){ createArrow(1); });

    // 轨道2
    QTimer::singleShot(1900, [=](){ createArrow(2); });
    QTimer::singleShot(10300, [=](){ createArrow(2); });

    QTimer::singleShot(rand()%1000+1000, [=](){ createArrow(2); });

    // 轨道3
    QTimer::singleShot(3500, [=](){ createArrow(3); });

    QTimer::singleShot(rand()%4000+500, [=](){ createArrow(3); });
}


//动画结束后点击鼠标返回关卡选择页面
void PlayScene::mousePressEvent(QMouseEvent *event) {

    if (m_isAnimationFinished) {

        emit playSceneBack();  // 触发返回信号
    }
    QWidget::mousePressEvent(event);
}






