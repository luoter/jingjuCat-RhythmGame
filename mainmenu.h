#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainMenu;
}
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{protected:
    Q_OBJECT

    void paintEvent(QPaintEvent*);

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void toggleMusic();

private:
    Ui::MainMenu *ui;

    void setupMusicControls();

    QMediaPlayer *bgmPlayer;
    QAudioOutput *audioOutput;
    QPushButton *muteBtn;
    bool isMusicMuted = false;

};
#endif // MAINMENU_H
