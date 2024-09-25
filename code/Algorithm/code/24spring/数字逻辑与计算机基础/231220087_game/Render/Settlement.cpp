#include "Settlement.h"



void Settlement::paintEvent(QPaintEvent *event)  {

    QPixmap backgroundImage(":/res/background/window.png");

    if(quit){
        QPainter painter(this);
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);

        coin_label->setText( "Game Over. ");
        coin_label->setStyleSheet("color: black; font-size: 24px;");

        confirmButton->setText("OK");
        return;
    }
    else if(lose == true){
        QPainter painter(this);
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);

        coin_label->setText( "Game Over... ");
        coin_label->setStyleSheet("color: black; font-size: 24px;");

        confirmButton->setText("Oh...");

        return;
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), backgroundImage);

    coin_label->setText( "You Win! You Get: " + QString::number(coin));
    coin_label->setStyleSheet("color: black; font-size: 24px;");
    coin_label->setTextFormat(Qt::MarkdownText);

    confirmButton->setText("Yeah!");
}


UpgradePage::UpgradePage(QWidget *parent) : QWidget(parent){
    upgradeAttackPowerButton = new QPushButton("upgradeAttackPower!", this);
    upgradeDefenceButton = new QPushButton("upgradeDefence!", this);
    upgradeHPButton = new QPushButton("upgradeHP!", this);
    back = new QPushButton("back", this);
    text = new QLabel("choose your preference", this);


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(upgradeAttackPowerButton);
    layout->addWidget(upgradeDefenceButton);
    layout->addWidget(upgradeHPButton);
    layout->addWidget(back);
    setLayout(layout);



    connect(upgradeAttackPowerButton, &QPushButton::clicked, this, &UpgradePage::upgradeAttackPower);
    connect(upgradeDefenceButton, &QPushButton::clicked, this, &UpgradePage::upgradeDefence);
    connect(upgradeHPButton, &QPushButton::clicked, this, &UpgradePage::upgradeHP);
    connect(back, &QPushButton::clicked, this, &UpgradePage::upgrade_ToStageSelect);
}
