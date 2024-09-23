#include "Special.h"
#include "Basic/enemy.h"
#include "Tool/fightSystem.h"
#include <limits>


std::shared_ptr<Enemy> findClosestEnemy(const QPoint& a, int range, const std::vector<std::shared_ptr<Enemy>> enemyList){

    std::shared_ptr<Enemy> target = nullptr;
    int minDistance = std::numeric_limits<int>::max();
    Coordinate end = enemyList[0]->getEnd();

    for (const auto& enemy : enemyList) {
        if (enemy && enemy->getAlive() && isInRange(enemy->getPosition().pos, range, a)) {
            int distance = distanceToEnd(enemy->getPosition().pos, end.pos);

            if (distance < minDistance) {
                minDistance = distance;
                target = enemy;
            }
        }
    }
    return target;
}

std::shared_ptr<Tower> findLowestHpTower(const QPoint& a, int range, const std::vector<std::shared_ptr<Tower>> towerList){
    // 寻找包括自己在内的最低hp的tower
    std::shared_ptr<Tower> target = nullptr;
    int minHP = std::numeric_limits<int>::max();

    for (const auto& t : towerList) {
        if(!t || !t->getAlive() || !isInRange(a, range, t->getPosition().pos)) continue;
        if (t->getHp() < minHP) {
            minHP = t->getHp();
            target = t;
        }
    }
    return target;
}

std::shared_ptr<Tower> findClosestTower(const QPoint& a, int range, const std::vector<std::shared_ptr<Tower>> towerList){

    std::shared_ptr<Tower> target = nullptr;
    int minDistance = std::numeric_limits<int>::max();

    for (const auto& t : towerList) {
        if(!t || !t->getAlive()) continue;
        int distance = isInRange(t->getPosition().pos, range, a);
        if (distance != 0) {
            if (distance < minDistance) {
                minDistance = distance;
                target = t;
            }
        }
    }
    return target;
}

int isInRange(const QPoint& a, int r, const QPoint& b) {
    int distance = (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y());
    return distance <= r * r;
}

int distanceToEnd(const QPoint& a, const QPoint& b){ // 距离终点
    int distance = (a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y());
    return distance;
}
