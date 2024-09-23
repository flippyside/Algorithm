#ifndef STAGESELECT_H
#define STAGESELECT_H

#include "game.h"
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class Game;
class Render;
class InputManager;

class StageSelect : public QWidget
{
    Q_OBJECT
    friend class TDgame;
protected:
    QTimer* timer;
    QPushButton *stage0;
    QPushButton *stage1;
    QPushButton* stage2;
    QPushButton *upgradeTower;
    QLabel* COIN_label;
    int COIN = 1;
    int windowLength = 1200;
    int windowWidth = 900;
public:
    StageSelect(QWidget* parent = nullptr);

    void setCOIN(int x){COIN = x;}

signals:
    void initializeGame(int stage);
    void showUpgradePage();
public slots:
    // 开始新游戏
    void startGame0();
    void startGame1();
    void startGame2();



protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap backgroundImage(":/res/background/menu.png");
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
        COIN_label->setText( "COIN: " + QString::number(COIN));
    }
};

#endif // STAGESELECT_H
