#ifndef RENDER_H
#define RENDER_H
#include <Basic/enemy.h>
#include "game.h"
#include "pause.h"
#include <QtConcurrent/qtconcurrentrun.h>
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

class Render : public QWidget{
    Q_OBJECT
    friend class InputManager;
    // size
    int length;
    int width;
    int gridsize;
    int windowLength = 1200;
    int windowWidth = 900;

    QPixmap backgroundImage;
    QPixmap pathImage;
    QPixmap rtableImage;

    QPixmap melee_stab_image;
    QPixmap remote_boom_image;
    QPixmap flippy_stab_image;

    QPixmap enemyImage;

    QPixmap affix_tel;
    QPixmap affix_spe;

    QLabel* bullet;

protected:
    std::shared_ptr<Game> game;
    QTimer* timer;
    QPushButton *RTbutton;
    QPushButton *Flippy;
    QPushButton* Giggles;
    QPushButton* Splendid;

    QPushButton *loadMapFileButton;
    QPushButton *loadSaveFileButton;
    QPushButton *saveButton;
    QPushButton *saveMapButton;
    QMenuBar *menuBar;
    QStatusBar* status;
    QMenu* menu[10];
    QAction* act[10];
    QLabel* awake_num;
    QLabel* icy_num;
    QLabel* poison_num;
    QLabel* aoe_num;
    QLabel *coinLabel;
public:
    Render(std::shared_ptr<Game> game, QWidget *parent = nullptr): QWidget(parent),  game(game) {
        bullet = new QLabel(this);
        bullet->setPixmap(QPixmap(":/res/tower/bullet_earth.png"));  // 设置图片路径
        bullet->setFixedSize(20,20);
        bullet->hide();  // 初始位置
    }
    // void move(QPoint begin, QPoint end) {
    //     bullet->move(begin);

    //     QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
    //     animation->setDuration(1000);  // 动画持续时间
    //     animation->setStartValue(begin);
    //     animation->setEndValue(end);
    //     animation->start(QAbstractAnimation::DeleteWhenStopped);
    // }
    void hideBullet(){
        bullet->hide();
    }
    void initialize();// 确定game对象后，再初始化
    void showDamage(int dmg, const QPoint &position);
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Z) {
            qInfo() << "z pressed";
            if (game->getIsPaused()) {
                game->resume();
            } else {
                game->pause();
            }
        }
        if (event->key() == Qt::Key_Q) {
            qInfo() << "q pressed";
            game->quit();
        }
        QWidget::keyPressEvent(event);
    }
signals:
    void mousePressEvent(QMouseEvent *event) override;


private slots:


protected:
    void paintEvent(QPaintEvent *event) override;


};

class TowerStatus : public QWidget{
    Q_OBJECT
    friend class InputManager;
    // size
    int pos = 30;
    int interval = 50;
    int size = 50;
protected:
    std::shared_ptr<Tower> tower;

    QPushButton *upGrade;
    QPushButton *close;
    QPushButton* release_skill;
    QPushButton *disarrange;


    QLabel* name;
    QLabel* hp;
    QLabel* attackPower;
    QLabel* defence;
    QLabel* attackInterval;
public:
    TowerStatus(QWidget *parent = nullptr): QWidget(parent) {


        upGrade = new QPushButton("upGrade", this);
        close = new QPushButton("close", this);
        release_skill = new QPushButton("release skill", this);
        disarrange = new QPushButton("disarrange", this);
        QFont font = upGrade->font();
        font.setPointSize(14);

        name = new QLabel("  ", this);name->setFont(font);
        hp = new QLabel("HP：", this);hp->setFont(font);
        attackPower = new QLabel("攻击力：", this);attackPower->setFont(font);
        defence = new QLabel("防御力：", this);defence->setFont(font);
        // attackInterval = new QLabel("攻击间隔：", this);attackInterval->setFont(font);

        name->setGeometry(pos,pos*2,size*3,size);
        hp->setGeometry(pos,pos*2+interval,size*3,size);
        attackPower->setGeometry(pos,pos*2+interval*2,size*3,size);
        defence->setGeometry(pos,pos*2+interval*3,size*3,size);
        // attackInterval->setGeometry(pos,pos*2+interval*4,size*3,size);
        upGrade->setGeometry(pos,pos*2+interval*5,size*3,size);
        close->setGeometry(pos,pos*2+interval*6,size*3,size);
        release_skill->setGeometry(pos,pos*2+interval*7,size*3,size);
        disarrange->setGeometry(pos,pos*2+interval*8,size*3,size);


        QObject::connect(close, &QPushButton::clicked, this, &TowerStatus::closeTowerStatus);
        QObject::connect(upGrade, &QPushButton::clicked, this, &TowerStatus::emit_towerLevelUp);
        QObject::connect(disarrange, &QPushButton::clicked, this, &TowerStatus::emit_disarrangeTower);
        QObject::connect(release_skill, &QPushButton::clicked, this, &TowerStatus::emit_release_skill);




    }

    void setTower(std::shared_ptr<Tower> tower){
        this->tower = tower;
    }


public slots:

    void emit_towerLevelUp(){emit towerLevelUp(tower); }
    void emit_disarrangeTower(){emit disarrangeTower(tower); }
    void emit_release_skill(){emit tower_release_skill(tower); }

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void closeTowerStatus();
    void towerLevelUp(std::shared_ptr<Tower> tower);
    void disarrangeTower(std::shared_ptr<Tower> tower);
    void tower_release_skill(std::shared_ptr<Tower> tower);

};



#endif // RENDER_H
