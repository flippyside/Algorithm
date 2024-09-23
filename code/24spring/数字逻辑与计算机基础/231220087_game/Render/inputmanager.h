#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <Basic/enemy.h>
#include "Tool/archive.h"
#include"render.h"
#include <game.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <memory>
#include <QtCore/QMetaType>

#include<qwidget.h>
#include<QObject>
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
#include <QKeyEvent>
 #include<QFileDialog>

class InputManager : public QObject
{
    Q_OBJECT

    friend class Render;
    std::shared_ptr<Render> render;
    std::shared_ptr<Game> game;

    bool waitingForMTDeployment = false;
    bool waitingForRTDeployment = false;
    bool waitingForGiggles = false;
    bool waitingForFlippy = false;
    bool waitingForSplendid = false;
    bool wfTargetTower = false;
    bool wfBind = false;
    bool wfUnbind = false;
    AffixType affix;
public:
    InputManager(std::shared_ptr<Render> render, std::shared_ptr<Game> game, QObject *parent = NULL)
        : QObject(parent), render(render), game(game)
    {
        qRegisterMetaType<std::shared_ptr<Tower>>("std::shared_ptr<Tower>");
    }

    void connecting(){

        // 操作相关
        connect(render->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(trigerMenu(QAction*)));
        connect(render->Flippy, &QPushButton::clicked, this, &InputManager::FlippyChoosed);
        connect(render->Giggles, &QPushButton::clicked, this, &InputManager::GigglesChoosed);
        connect(render->Splendid, &QPushButton::clicked, this, &InputManager::SplendidChoosed);

        // 存档相关
        connect(render->saveButton, &QPushButton::clicked, this, &InputManager::save);
        connect(render->saveMapButton, &QPushButton::clicked, this, &InputManager::saveMap);
    }

public slots:
    void trigerMenu(QAction* act);
    void mousePressEvent(QMouseEvent *event);
    void arrangeMTtower(const QPoint &pos)
    {
        qInfo()<<pos;
    }

signals:
    void deployAffix_signal();
    void showTowerStatus(std::shared_ptr<Tower> tower);// 记得注册


private slots:
    void RTButtonClicked() {
        waitingForRTDeployment = true;
    }
    void MTButtonClicked()
    {
        waitingForMTDeployment = true;
    }
    void GigglesChoosed(){
        waitingForGiggles = true;
    }

    void FlippyChoosed(){
        waitingForFlippy = true;
    }
    void SplendidChoosed(){
        waitingForSplendid  =true;
    }

    void save(){ // 保存存档
        GameSave gamesave(0);
        if(gamesave.saveGame(game->getCoin(), *game->map,*game->conditionMap,*game->towerManager,*game->enemyManager,*game->affixManager,*game->enemyWave)){
            qInfo() << "save success!";
        }
        else qInfo() << "save failed!";
    }

    void saveMap(){ // 保存当前地图(尺寸)信息
        GameSave gamesave(0);
        if(gamesave.saveMap(*game->map)) qInfo() << "save success!";
        else qInfo() << "save failed!";
    }
};

#endif // INPUTMANAGER_H
