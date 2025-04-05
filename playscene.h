#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelnum);
    int levelIndex;//记录选择关卡

    void paintEvent(QPaintEvent*);

signals:
    //自定义信号，告诉关卡场景，点击了返回
    void playSceneBack();

};

#endif // PLAYSCENE_H
