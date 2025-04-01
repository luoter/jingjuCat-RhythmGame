#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>

namespace Ui {
class LevelSelect;
}

class LevelSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();

private:
    Ui::LevelSelect *ui;
};

#endif // LEVELSELECT_H
