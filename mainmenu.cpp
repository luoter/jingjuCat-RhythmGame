#include "mainmenu.h"
#include "ui_mainmenu.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"
#include"QPushButton"
#include"levelselect.h"


MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //版权声明
    QLabel*copyright=new QLabel(this);
    copyright->setText("素材来自《京剧猫》动画，版权归原作者所有");
    copyright->setStyleSheet("color:white;font-size:12px;");
    copyright->setGeometry(10,20,300,20);

    //开始按钮设置//需要更改
    QPushButton *startBtn = new QPushButton("开始游戏", this);
    startBtn->setGeometry(width()/2-50, height()-150, 100, 50);
    connect(startBtn, &QPushButton::clicked, [=](){
        // qDebug() << "进入关卡选择界面"; // 临时验证
    });


    // // 音乐播放器
    // QMediaPlayer *bgmPlayer = new QMediaPlayer(this);
    // bgmPlayer->setMedia(QUrl("qrc:/sounds/bgm/theme.mp3"));//添加背景音乐
    // bgmPlayer->play();

    // // 静音按钮
    // QPushButton *muteBtn = new QPushButton(this);
    // muteBtn->setIcon(QIcon(":/images/cat_head.png"));
    // muteBtn->setGeometry(10, 40, 40, 40);
    // connect(muteBtn, &QPushButton::clicked, [=](){
    //     bgmPlayer->setMuted(!bgmPlayer->isMuted());
    // });


    //跳转选择关卡界面
    connect(startBtn, &QPushButton::clicked, [=](){
        LevelSelect *levelSelect = new LevelSelect();
        levelSelect->show();
        this->hide();
    });


}

MainMenu::~MainMenu()
{
    delete ui;
}


//主界面设置
//背景图
void MainMenu::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap bg(":/image_forzhuye/sucai1.png");//导入背景图*****
    painter.drawPixmap(0, 0, width(), height(), bg);
}
