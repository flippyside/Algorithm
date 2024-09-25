#include "stageselect.h"
#include "Render/inputmanager.h"
#include "Render/render.h"

StageSelect::StageSelect(QWidget* parent) : QWidget(parent){
    // int buttonSize = 100;
    // int interval = buttonSize*1.5;

    QFont ft;
    ft.setPointSize(14);

    int interval_time = 100;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(interval_time); // 启动定时器

    stage0 = new QPushButton("stage 0", this); stage0->setFont(ft);
    stage1 = new QPushButton("stage 1", this); stage1->setFont(ft);
    stage2 = new QPushButton("stage 2", this); stage2->setFont(ft);
    upgradeTower = new QPushButton("upgrade tower", this); upgradeTower->setFont(ft);

    upgradeTower->setGeometry(300,300,200,100);

    COIN_label = new QLabel(this);
    COIN_label->setGeometry(100,100,200,200);
    COIN_label->setText( "COIN: " + QString::number(COIN));
    COIN_label->setStyleSheet("color: black; font-size: 24px;");
    COIN_label->setTextFormat(Qt::MarkdownText);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(stage0);
    layout->addWidget(stage1);
    layout->addWidget(stage2);
    setLayout(layout);


    connect(stage0, &QPushButton::clicked, this, &StageSelect::startGame0);
    connect(upgradeTower, &QPushButton::clicked, this, &StageSelect::showUpgradePage);// 显示升级界面


    // 未解锁关卡
    // connect(stage1, &QPushButton::clicked, this, &StageSelect::startGame1);
    // connect(stage2, &QPushButton::clicked, this, &StageSelect::startGame2);

}


void StageSelect::startGame0(){
    emit initializeGame(0);
}
void StageSelect::startGame1(){
    emit initializeGame(1);
}
void StageSelect::startGame2(){
    emit initializeGame(2);
}
