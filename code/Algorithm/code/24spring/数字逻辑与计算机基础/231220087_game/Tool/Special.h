#ifndef SPECIAL_H
#define SPECIAL_H

#include "qpoint.h"
#include <memory>
#include <vector>
struct Coordinate;
class Enemy;
class Tower;

enum class Special {none,awake, aoe, icy, poison, teleport };
enum AffixType{awake, icy, aoe, poison, teleport, speedUp };
enum bulletType{
    melee_stab,
    remote_boom,
    cure,
    flippy_stab,
    laser
};

enum TowerName{
    _Giggles,
    _Flippy,
    _Splendid,
    Flaky

};

// 给出中心点和范围，找到最近的目标
std::shared_ptr<Tower> findLowestHpTower(const QPoint& a, int range, const std::vector<std::shared_ptr<Tower>> towerList);
std::shared_ptr<Enemy> findClosestEnemy(const QPoint& a, int range, const std::vector<std::shared_ptr<Enemy>> enemyList);
std::shared_ptr<Tower> findClosestTower(const QPoint& a, int range, const std::vector<std::shared_ptr<Tower>> towerList);
int isInRange(const QPoint& a, int r, const QPoint& b);
int distanceToEnd(const QPoint& a, const QPoint& b);



#endif
