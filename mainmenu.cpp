#include "mainmenu.h"
#include "ui_mainmenu.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"
#include"QPushButton"
#include"levelselect.h"
#include"QTimer"
#include"mypushbutton.h"


MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setFixedSize(1000,560);

    //版权声明
    QLabel*copyright=new QLabel(this);
    copyright->setText("素材来自《京剧猫》动画，版权归原作者所有");
    copyright->setStyleSheet("color:black;font-size:12px;");
    copyright->setGeometry(10,20,300,20);

    //开始按钮设置//需要更改

    MyPushButton*startBtn=new MyPushButton(":/forzhuye/picture1/begin3.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.7,this->height()*0.3);








    // // 音乐播放器
    // QMediaPlayer *bgmPlayer = new QMediaPlayer(this);
    // bgmPlayer->setMedia(QUrl("qrc:/sounds/bgm/theme.mp3"));//添加背景音乐
    // bgmPlayer->play();



    // // 静音按钮
    // QPushButton *muteBtn = new QPushButton(this);
    // QPixmap pixmap;
    // pixmap.load("");
    // muteBtn->setFixedSize(pixmap.width(),pixmap.height());
    // muteBtn->setStyleSheet("QPushButton{border:0px}");
    // muteBtn->setIcon(pixmap);
    // muteBtn->setIconSize(QSize(pixmap.width(),pixmap.height()));
    // muteBtn->setGeometry(20, 40, 40, 40);
    // // connect(muteBtn, &QPushButton::clicked, [=](){
    // //     bgmPlayer->setMuted(!bgmPlayer->isMuted());
    // // });
    // MyPushButton*jinyinBtn=new MyPushButton(":/forzhuye/picture1/jingyin12.png",":/forzhuye/picture1/jingyin2.png");
    // jingyinBtn->setParent(this);

     LevelSelect*levelselect=new LevelSelect;


    //延时跳转选择关卡界面
    connect(startBtn, &MyPushButton::clicked, [=](){

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

MainMenu::~MainMenu()
{
    delete ui;
}


//主界面设置
//背景图
void MainMenu::paintEvent(QPaintEvent*){
    QPainter painter1(this);
    QPixmap bg(":/forzhuye/picture1/zhuyebeijing.png");
    painter1.drawPixmap(0, 0, width(), height(), bg);
}
