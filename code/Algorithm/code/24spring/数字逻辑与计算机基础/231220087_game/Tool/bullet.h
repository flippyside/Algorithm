#include "Basic/role.h"
#include "Basic/enemy.h"
#include "Basic/tower.h"
#include "qlabel.h"
#include "qpropertyanimation.h"
#include "qwidget.h"
/*
enum bulletType{melee_stab, remote_boom};
*/
class Bullet : QWidget{
    friend class BulletManager;
    friend class Tower;
QPoint pos;
QPoint pos_tower;
QPoint begin;
QPoint end;
bulletType type;
int time;
QLabel* bullet;
public:
    Bullet(QPoint pos, bulletType type, int time):pos(pos),type(type)
            ,time(time){}

    Bullet(QPoint pos, QPoint pos_tower, bulletType type, int time):pos(pos),pos_tower(pos_tower),type(type)
            ,time(time){}
    Bullet(QPoint begin, QPoint end, bulletType type, int time, int isAnimation):begin(begin)
        , end(end), type(type), time(time){
    }
    QPoint getPosition(){return pos; }
    QPoint getPosition_tower(){return pos_tower; }
    QPoint getBegin(){return begin; }
    QPoint getEnd(){return end; }

    bulletType getType(){return type; }
    int getTime(){return time;}

    void decreaseTime(){time--;}


};


// class BulletManager{
// std::vector<Bullet> bullets;

// public:
//     void createBullet();
//     void deleteBullet();
//     void TowerAttackEnemy(Tower* t, Enemy* e);
//     void EnemyAttackTower(Tower* t, Enemy* e);


// };
