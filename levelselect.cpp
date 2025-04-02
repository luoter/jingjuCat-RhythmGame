#include "levelselect.h"
#include "ui_levelselect.h"

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelSelect)
{
    ui->setupUi(this);

    // connect(ui->level1Btn, &QPushButton::clicked, [this](){
    //     startGame(1); // 关卡1
    // });
    // connect(ui->level2Btn, &QPushButton::clicked, [this](){
    //     startGame(2); // 关卡2
    // });




}

LevelSelect::~LevelSelect()
{
    delete ui;
}


// void LevelSelect::startGame(int level) {
//     GameWidget *game = new GameWidget(level);
//     game->show();
//     this->hide();
// }


