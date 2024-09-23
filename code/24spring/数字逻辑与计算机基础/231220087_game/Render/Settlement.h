#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qtimer.h"
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QObject>

class Settlement : public QWidget
{
    Q_OBJECT
    QTimer* timer;
    QPushButton* confirmButton;
    int coin;
    QLabel* coin_label;
    bool lose = false;
    bool quit = false;


public:
    Settlement(QWidget *parent = nullptr) : QWidget(parent){
        int interval_time = 100;
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(interval_time); // 启动定时器
        confirmButton = new QPushButton("Yeah!", this);
        coin_label = new QLabel(this);

        coin_label->setGeometry(100,100,300,100);
        confirmButton->setGeometry(300,300,150,50);
        connect(confirmButton, &QPushButton::clicked, this, &Settlement::backToStageSelect);
    }
    void setCoin(int n){coin = n; }
    void setLose(bool x){lose = x; }
    void setQuit(bool x){quit = x; }
protected:
    void paintEvent(QPaintEvent *event);

public slots:

signals:
    void backToStageSelect();
};


class UpgradePage : public QWidget{
    Q_OBJECT

    QPushButton* upgradeAttackPowerButton;
    QPushButton* upgradeDefenceButton;
    QPushButton* upgradeHPButton;
    QPushButton* back;

    QLabel* text;

public:
    UpgradePage(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap backgroundImage(":/res/background/dream.png");
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    }
signals:
    void upgradeAttackPower();
    void upgradeDefence();
    void upgradeHP();
    void upgrade_ToStageSelect();
};


#endif // SETTLEMENT_H
