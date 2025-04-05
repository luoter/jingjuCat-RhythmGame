#include "playscene.h"
#include"QPainter"
#include"QPixmap"
#include"QLabel"
#include"mypushbutton.h"
#include"QDebug"

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


    if(levelIndex==1){
        //设置标题
        this->setWindowTitle("《京剧猫》，加油( ´ ▽ ` )ノ");
    }

    if(levelIndex==2){
        //设置标题
        this->setWindowTitle("《飘荡》，你可以的┐(￣ヮ￣)┌");
    }



}

//关卡选择背景
void PlayScene::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/forplayscene/picture1/gameground.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
