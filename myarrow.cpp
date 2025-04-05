#include "myarrow.h"
#include"QLabel"
#include"QPainter"
#include"QPixmap"
#include"QPushButton"
#include"QTimer"
#include"QMediaPlayer"
#include"QAudioOutput"

MyArrow::MyArrow(Direction dir,int track,QWidget*parent)
    :QLabel(parent),m_direction(dir),m_track(track)
{

    QString imgPath;
    switch(dir){
    case(U):
        imgPath=":/arrow/picture1/arrowup.png";
        break;
    case(D):
        imgPath=":/arrow/picture1/arrowdown.png";
        break;
    case(L):
        imgPath=":/arrow/picture1/arrowleft.png";
        break;
    case(R):
        imgPath=":/arrow/picture1/arrowright.png";
        break;
    }

    setPixmap(QPixmap(imgPath).scaled(130,130,Qt::KeepAspectRatio));







}
