#include "levelselect.h"
#include "ui_levelselect.h"
#include"QPainter"
#include"QPixmap"
#include"QLabel"
#include"mypushbutton.h"
#include"QDebug"


LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    //设置标题
    this->setWindowTitle("选择想听的歌吧Fight!!(ｏ^-^)尸~''☆ミ☆ミ");
    this->setWindowIcon(QPixmap(":/forzhuye/picture1/jingjulogo4.png"));

    //返回按钮
    MyPushButton*backBtn=new MyPushButton(":/forselect/picture1/back5.png");
    backBtn->setParent(this);
    backBtn->move(this->width()*0.05,this->height()*0.85);

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //发送信号
        emit this ->levelSelectBack();

    });

    //关卡选择按钮
    MyPushButton*leveloneBtn=new MyPushButton(":/forselect/picture1/level14.png");
    leveloneBtn->setParent(this);
    leveloneBtn->move(this->width()*0.02,this->height()*0.28);

    MyPushButton*leveltweBtn=new MyPushButton(":/forselect/picture1/level23.png");
    leveltweBtn->setParent(this);
    leveltweBtn->move(this->width()*0.66,this->height()*0.6);

    //监视关卡的点击
    connect(leveloneBtn,&MyPushButton::clicked,[=]()
    {
        //进入游戏场景
        this->hide();
        play=new PlayScene(1);//游戏场景的对象指针
        play->show();

        //点击返回
        connect(play,&PlayScene::playSceneBack,this,[=](){
            this->show();
            delete play;
            play=NULL;



        });

    });

    connect(leveltweBtn,&MyPushButton::clicked,[=]()
    {

        //进入游戏场景
        this->hide();
        play=new PlayScene(2);
        play->show();

        //点击返回
        connect(play,&PlayScene::playSceneBack,this,[=](){
            this->show();
            delete play;
            play=NULL;
        });

    });






}

LevelSelect::~LevelSelect()
{
    delete ui;
}

//关卡选择背景
void LevelSelect::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/forselect/picture1/guanqia.png");//更改*****
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}






