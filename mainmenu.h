#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QMovie>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainMenu;
}
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{protected:
    Q_OBJECT


    //背景设置
    void paintEvent(QPaintEvent*)override;

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private:
    Ui::MainMenu *ui;
};
#endif // MAINMENU_H
