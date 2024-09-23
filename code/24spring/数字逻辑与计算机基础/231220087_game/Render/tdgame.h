#ifndef TDGAME_H
#define TDGAME_H

#include "Render/Settlement.h"
#include "Render/inputmanager.h"
#include "Render/render.h"
#include "Render/stageselect.h"
#include "qwidget.h"
#include <map>
#include <memory>
#include<memory.h>
#include<QObject>

class Menu;
class Game;
class StageSelect;


class TDgame :public QWidget
{
    Q_OBJECT
protected:
    int COIN = 1;// 全局硬币，可用来在游戏开始前升级tower
    std::map<int, bool> stageStatus;
    std::shared_ptr<Menu> menu;
    std::shared_ptr<StageSelect> stageSelect;
    std::shared_ptr<Settlement> settlement;
    std::shared_ptr<UpgradePage> upgradePage;
    std::shared_ptr<TowerStatus> towerStatus;
    GlobalAttributes globalAttributes;


    std::shared_ptr<Game> game;
    std::shared_ptr<Render> render;
    std::shared_ptr<InputManager> inputManager;

public:
    TDgame();
    void connecting();
public slots:
    void backToStageSelect_slot();
    void showStageSelect_slot();

    void showSettlement(int coin);

    void showUpgradePage_slot();
    void hideUpgradePage();

    void hideMenu_slot();
    void hideRender();


    void changeCOIN(int num){
        COIN += num;
        qInfo() << "coin has been changed to " << COIN;
        stageSelect->setCOIN(COIN);
    }
    void upgradeAttackPower();
    void upgradeDefence();
    void upgradeHP();
    void stageStatusChange(int stage);

    // 初始化游戏
    void initializeGame(int stage);
    void initializeGame_save(GameSave gamesave);
    void initializeGame_map(std::shared_ptr<Scenemap> map);

    void showTowerStatus(std::shared_ptr<Tower> tower);
    void closeTowerStatus();

signals:

};

#endif // TDGAME_H
