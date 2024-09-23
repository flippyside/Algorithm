#ifndef GAME_H
#define GAME_H
#include <Basic/scenemap.h>
#include <Basic/enemy.h>
#include <Tool/fightSystem.h>
#include <Tool/affix.h>
#include <Basic/tower.h>
#include "Tool/enemywave.h"
#include <qobject.h>
#include <Tool/Special.h>
#include <Qmutex>
#include <QtConcurrent/qtconcurrentrun.h>
#include <maps.h>

class Game : public QObject{
    Q_OBJECT
    friend class InputManager;
protected:
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<TowerManager> towerManager;
    std::shared_ptr<Scenemap> map;
    std::shared_ptr<ConditionMap> conditionMap;
    std::shared_ptr<FightSystem> fightSystem;
    std::shared_ptr<AffixManager> affixManager;
    std::shared_ptr<EnemyWave> enemyWave;
    std::shared_ptr<HealthSystem> healthSystem;

    int coin = 60; // 初始硬币
    int stage = 0;// 关卡编号
    bool isPaused = false;
    QTimer* timer_affix;
    QTimer* timer1;
    QTimer* timer2;

public:

    Game(std::shared_ptr<Scenemap> m, std::shared_ptr<ConditionMap> cm,std::shared_ptr<EnemyManager> enemyManager,
         std::shared_ptr<TowerManager> towerManager,std::shared_ptr<FightSystem> fightSystem,
         std::shared_ptr<AffixManager> affixManager,std::shared_ptr<EnemyWave> enemyWave,
         std::shared_ptr<HealthSystem> healthSystem);// 通过存档创建
    Game(std::shared_ptr<Scenemap> map);// 通过用户导入的地图创建
    Game();

    // 访问
    int getStage() {return stage; }
    bool getIsPaused(){return isPaused; }
    const std::shared_ptr<EnemyManager>& getEnemyManager() const {return enemyManager;}
    const std::shared_ptr<TowerManager>& getTowerManager() const {return towerManager;}
    const std::shared_ptr<Scenemap>& getMap() const {return map;}
    const std::shared_ptr<ConditionMap>& getConditionMap() {return conditionMap;}
    const std::shared_ptr<FightSystem>& getFightSystem() {return fightSystem;}
    const std::shared_ptr<AffixManager>& getAffixManager() {return affixManager;}
    const std::shared_ptr<HealthSystem>& getHealthSystem(){return healthSystem; }
    int getCoin()const{return coin; }

    // 修改
    void setPaused(bool a){isPaused = a; }
    void setCoin(int x){coin = x; }

    // 行为
    void connecting();// 搭建信号与槽
    void arrangeMTtower(QPoint pos, TowerName name = TowerName::_Flippy);
    void arrangeRTtower(QPoint pos, TowerName name = TowerName::_Giggles);
    void bindAffixToTower(const QPoint &pos, AffixType affix);
    void unbindAffixOfTower(const QPoint &pos, AffixType affix);
    std::shared_ptr<Tower> findTower(QPoint pos);// 根据鼠标点击寻找tower
    void pause(); // 暂停游戏
    void resume(); // 继续游戏


    ~Game(){
    }

public slots:
    void changeCoin(int x){ coin += x; }
    void updateTowerCondition();// 检查tower是否可以升级

    void startGame(int stage);
    void gameOver_lose();
    void gameOver_win();
    void quit();
    void towerLevelUp(std::shared_ptr<Tower> tower);
    void disarrangeTower(std::shared_ptr<Tower> tower);
    void tower_release_skill(std::shared_ptr<Tower> tower);


signals:
    void game_backToStageSelect();
    void showSettlement(int coin);
    void stageStatusChange(int stage); // 游戏通关后，设置当前stage为true
};



#endif // GAME_H
