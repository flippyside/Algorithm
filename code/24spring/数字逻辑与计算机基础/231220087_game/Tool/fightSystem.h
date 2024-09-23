#ifndef FIGHTSYSTEM_H
#define FIGHTSYSTEM_H
#include <QtConcurrent/qtconcurrentrun.h>
#include <Basic/enemy.h>
#include <Basic/tower.h>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <Tool/bullet.h>
#include"Special.h"

struct QPointCompare {
    bool operator()(const QPoint &a, const QPoint &b) const {
        if (a.x() == b.x()) {
            return a.y() < b.y();
        }
        return a.x() < b.x();
    }
};
class FightSystem : public QObject {
    Q_OBJECT
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<TowerManager> towerManager;
    std::shared_ptr<ConditionMap> cmap;
    std::vector<std::shared_ptr<Bullet>> bulletList;
public:
    FightSystem(std::shared_ptr<EnemyManager> em, std::shared_ptr<TowerManager> tm, std::shared_ptr<ConditionMap> cm)
        : enemyManager(std::move(em)), towerManager(std::move(tm)), cmap(std::move(cm)) {

    }

    // 访问
    std::vector<std::shared_ptr<Bullet>>& getBulletList(){return bulletList;}

    // 行为
    void enemyFindTarget(std::shared_ptr<Enemy> e);
    void towerFindTarget(std::shared_ptr<Tower> t);
    void AttackGenerator();
    void enemyAttackTower(std::shared_ptr<Enemy> e, std::shared_ptr<Tower> t);
    bool towerAttackEnemy(std::shared_ptr<Tower> t, std::shared_ptr<Enemy> e);

    ~FightSystem(){ }
signals:
    void aEnemyDead(int drop_coin);
    void cure(int hp, QPoint pos, int range);
    void towerLowHp();
    void enemyAttackTower_signal();
    void towerAttackEnemy_signal();
};

std::vector<std::shared_ptr<Enemy>>* findAllEnemyInRange(const Coordinate& a, int range, const std::vector<std::shared_ptr<Enemy>>& enemyList);// AOE攻击

#endif // FIGHTSYSTEM_H
