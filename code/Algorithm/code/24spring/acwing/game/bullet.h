#include "role.h"
#include "enemy.h"
#include "tower.h"
#include "Special.h"

class Bullet{
    friend class BulletManager;
    friend class Tower;
Coordinate position;
int range;
int damage;
std::vector<Special> specialList;

public:
    Coordinate getPosition(){return position; }
    int getRange(){return range; }
    std::vector<Special> getType(){return specialList; }

};


class BulletManager{
std::vector<Bullet> bullets;

public:
    void createBullet();
    void deleteBullet();
    void TowerAttackEnemy(Tower* t, Enemy* e);
    void EnemyAttackTower(Tower* t, Enemy* e);


};