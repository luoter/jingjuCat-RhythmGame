#include "mainmenu.h"
#include "ui_mainmenu.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"
#include"QPushButton"
#include"levelselect.h"
#include"QTimer"
#include"mypushbutton.h"
#include"QMediaPlayer"
#include"QAudioOutput"
#include <QIcon>


MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setFixedSize(1000,600);

    //版权声明
    QLabel*copyright=new QLabel(this);
    copyright->setText("素材来自《京剧猫》动画，版权归原作者所有");
    copyright->setStyleSheet("color:black;font-size:12px;");
    copyright->setGeometry(750,580,300,20);


    this->setWindowIcon(QPixmap(":/forzhuye/picture1/jingjulogo4.png"));




    //开始按钮设置//需要更改

    MyPushButton*startBtn=new MyPushButton(":/forzhuye/picture1/begin3.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.7,this->height()*0.3);


    // // 音乐播放器
    // QMediaPlayer *player = new QMediaPlayer(this);
    // QAudioOutput*outPut=new QAudioOutput(this);
    // player->setAudioOutput(outPut);
    // player->setSource(QUrl("qrc:/sound/picture1/shiyan.wav"));//添加背景音乐
    // outPut->setVolume(200);
    // player->play();
    // QPushButton*muteBtn=NULL;
    // connect(muteBtn,&QPushButton::clicked,[=](){

    //     outPut->setMuted(!outPut->isMuted());
    //     muteBtn->setIcon(QIcon(!outPut->isMuted()
    //         ?":/forzhuye/picture1/jingyin22.png"
    //         :":/forzhuye/picture1/jingyin12.png"));
    // });
    setupMusicControls();




    LevelSelect*levelselect=new LevelSelect;


    //延时跳转选择关卡界面
    connect(startBtn, &MyPushButton::clicked, [=](){

        audioOutput->setMuted(isMusicMuted);

    //点击返回后操作
    connect(levelselect,&LevelSelect::levelSelectBack,this,[=](){
        this->show();
        levelselect->hide();


    });

        QTimer::singleShot(200,this,[=](){
            levelselect->show();
            this->hide();

        });

    });


}

//


//主界面设置
//背景图
void MainMenu::paintEvent(QPaintEvent*){
    QPainter painter1(this);
    QPixmap bg(":/forzhuye/picture1/zhuyebeijing.png");
    painter1.drawPixmap(0, 0, width(), height(), bg);
}

//音乐控制
void MainMenu::setupMusicControls()
{

    audioOutput = new QAudioOutput(this);

    // 创建播放器
    bgmPlayer = new QMediaPlayer(this);
    bgmPlayer->setAudioOutput(audioOutput);
    bgmPlayer->setSource(QUrl("qrc:/sound/picture1/shiyan.wav"));//音频更改
    audioOutput->setVolume(50);  // 初始音量

    // 创建静音按钮
    muteBtn = new QPushButton(this);
    muteBtn->setObjectName("muteBtn");

    // 设置按钮属性
    muteBtn->setGeometry(20, 40, 40, 40);  // 左上角位置
    muteBtn->setIcon(QIcon(":/forzhuye/picture1/jingyin13.png"));
    muteBtn->setIconSize(QSize(42, 42));

    // 连接信号槽
    connect(muteBtn, &QPushButton::clicked, this, &MainMenu::toggleMusic);

    // 自动循环播放
    connect(bgmPlayer, &QMediaPlayer::playbackStateChanged, [this](){
        if(bgmPlayer->playbackState() == QMediaPlayer::StoppedState) {
            bgmPlayer->play();
        }
    });

    bgmPlayer->play();

}


void MainMenu::toggleMusic()
{
    isMusicMuted = !isMusicMuted;

    // 静音控制
    audioOutput->setMuted(isMusicMuted);

    // 更新按钮图标
    muteBtn->setIcon(isMusicMuted
        ? QIcon(":/forzhuye/picture1/jingyin23.png")
        :  QIcon(":/forzhuye/picture1/jingyin13.png"));
}

MainMenu::~MainMenu()
{
    bgmPlayer->stop();
    delete bgmPlayer;  // 父对象会自动删除，但显式释放更安全
}

