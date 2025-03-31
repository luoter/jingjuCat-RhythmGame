#include "mainmenu.h"
#include "ui_mainmenu.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //版权声明
    QLabel*copyright=new QLabel(this);
    copyright->setText("素材来自《京剧猫》动画，版权归原作者所有，仅用于学习交流");
    copyright->setStyleSheet("color:white;font-size:12px;");
    copyright->setGeometry(10,20,300,20);



}

MainMenu::~MainMenu()
{
    delete ui;
}


//主界面设置
//背景图
void MainMenu::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap bg(":/imageone/sucai1.png");//导入背景图*****
    painter.drawPixmap(0, 0, width(), height(), bg);
}
