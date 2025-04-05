#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#pragma once
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget( QWidget *parent = nullptr);
    ~GameWidget();


protected:



private:
    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
