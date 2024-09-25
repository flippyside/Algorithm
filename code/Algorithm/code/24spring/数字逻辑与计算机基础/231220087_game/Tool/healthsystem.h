#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "qobject.h"
#include "qpoint.h"
#include "qtmetamacros.h"
#include "Special.h"

class Bullet;
class Enemy;
class EnemyManager;
class TowerManager;

class HealthSystem : public QObject
{
    Q_OBJECT
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<TowerManager> towerManager;
    std::vector<std::shared_ptr<Bullet>> cureList;
public:
    HealthSystem(std::shared_ptr<EnemyManager> em, std::shared_ptr<TowerManager> tm)
        : enemyManager(em), towerManager(tm){
    }

    std::vector<std::shared_ptr<Bullet>> getCureImagePos(){return cureList;}

public slots:
    void cureLowestHPTower(int hp, QPoint pos, int range); // 治疗攻击范围内hp最低的tower
};

#endif // HEALTHSYSTEM_H
