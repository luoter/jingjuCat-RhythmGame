#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "QLabel"
#include "QPainter"
#include "QPixmap"
#include "levelselect.h"
#include "surprise.h"
#include "QTimer"
#include "mypushbutton.h"
#include <QIcon>
#include <QKeyEvent>


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

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();  // 获取焦点，为了获取按键事件


    //开始按钮设置
    MyPushButton*startBtn=new MyPushButton(":/forzhuye/picture1/begin3.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.7,this->height()*0.3);

    startBtn->setFocusPolicy(Qt::NoFocus); // 禁止按钮获取焦点

    setupMusicControls();


    //延时跳转选择关卡界面
    connect(startBtn, &MyPushButton::clicked, [=](){

        //要在点了按钮之后生成
        LevelSelect*levelselect=new LevelSelect;

        audioOutput->setMuted(true);

        this->setFocus();
        this->hide();
        QTimer::singleShot(500,this,[=](){

            levelselect->show();

        });

        //点击返回后操作
        connect(levelselect,&LevelSelect::levelSelectBack,this,[=](){

            levelselect->hide();

            QTimer::singleShot(500,this,[=](){

                this->show();

                //音乐播放状态恢复
                audioOutput->setMuted(isMusicMuted);
            });

        });

    });




}


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
    audioOutput->setVolume(30);  // 初始音量,但这个设置是一点用没有
    bgmPlayer->setSource(QUrl("qrc:/sound/picture1/yugan.mp3"));
    bgmPlayer->play();

    // 创建静音按钮
    muteBtn = new QPushButton(this);
    muteBtn->setObjectName("muteBtn");
    muteBtn->setFocusPolicy(Qt::NoFocus);

    // 设置按钮属性
    muteBtn->setGeometry(20, 40, 40, 40);
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

}


void MainMenu::toggleMusic()
{
    //改变静音bool值
    isMusicMuted = !isMusicMuted;

    // 静音控制
    audioOutput->setMuted(isMusicMuted);

    // 更新按钮图标
    muteBtn->setIcon(isMusicMuted
        ? QIcon(":/forzhuye/picture1/jingyin23.png")
        :  QIcon(":/forzhuye/picture1/jingyin13.png"));

    this->setFocus();
}

MainMenu::~MainMenu()
{
    bgmPlayer->stop();
    delete bgmPlayer;  // 父对象会自动删除，但显式释放更安全
}

void MainMenu::keyPressEvent(QKeyEvent*event)
{
    //跳转彩蛋界面
    if(event->key()==Qt::Key_Up){

        Surprise*surprise=new Surprise();

        this->hide();

        surprise->show();

        connect(surprise,&Surprise::surpriseBack,this,[=](){

            surprise->hide();
            this->show();
            surprise->deleteLater();

        });

    }
    QMainWindow::keyPressEvent(event);
}

