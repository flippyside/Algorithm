#ifndef ENEMY_H
#define ENEMY_H


#include "Basic/role.h"
#include "Tool/affix.h"
#include <Qmutex>
#include <QMutexLocker>


class Enemy : public Role
{friend class EnemyManager;
private:


    int enemyCoin = 1;// 掉落金币

    Path p;
    int pathType;
    Coordinate next_position; // e的前进目标（e的下一个坐标, 且是相对的）
    Coordinate end; // 终点
    int path_index = 0; // 当前路径坐标

    int speed = 1;
    bool blocked = false;
    bool attackable = true;


    bool icy = 0;
    bool bleeding = 0;
    bool speedUp = 0;

    int icyTime = 0;
    int bleedingTime = 0;
public:
    Enemy(int x, int y, const Path& pa);
    Enemy(int x = 0,int y = 0) : Role(x,y){};

    // 访问
    int getPathType() const {return pathType;}
    Path getPath() const {return p; }
    int getPath_index() const { return path_index;}
    Coordinate getNext_position() const {return next_position; }
    Coordinate getEnd()const{return end;}
    int getSpeed()const{return speed; }
    bool getBlocked()const{return blocked; }
    bool getIcy()const{return icy; }
    int getIcyTime()const{return icyTime; }
    bool getAttackable()const{return attackable; }
    bool getBleeding()const {return bleeding; }
    int getBleedingTime()const{return bleedingTime; }
    bool getSpeedUp()const{return speedUp; }
    int getEnemyCoin()const {return enemyCoin; }

    // 修改
    void setPath(Path path){p = path; }
    void setPathType(int x) {pathType = x; }
    void setPath_index(int x) { path_index = x;}
    void setNext_position(Coordinate c) { next_position = c; }
    void setEnd(Coordinate c) {end = c; }
    void setIcy(bool a){icy=a; }
    void setIcyTime(int a){icyTime = std::max(0,a); }
    void setSpeed(int x) {speed = x; }
    void setBlocked(bool a){ blocked=a; }
    void setBleeding(bool a){bleeding = a; }
    void setBleedingTime(int a){ bleedingTime = std::max(0,a); }
    void setAttackable(bool a){ attackable=a; }
    void setSpeedUp(bool a){speedUp = a; }


    //void attack(){};
    //void hit(){};

    // 行为
    void move();
    void die(){
        setAlive(false);
    }


    //~Enemy(){ }
};

class EnemyManager : public QObject {
    Q_OBJECT
    Scenemap map;
    std::shared_ptr<ConditionMap> cmap;
    std::vector<std::shared_ptr<Enemy>> enemyList;
    bool noMoreNewEnemy = false;
public:

    EnemyManager(const Scenemap& m, std::shared_ptr<ConditionMap> cm):map(m),cmap(cm){ }

    // 访问
    std::vector<std::shared_ptr<Enemy>> getEnemyList()const{return enemyList;}
    std::vector<std::shared_ptr<Enemy>>& getEnemyList(){return enemyList;}



    // 修改
    void addEnemy(std::shared_ptr<Enemy> e){enemyList.push_back(e);}
    void setEnemyList(std::vector<std::shared_ptr<Enemy>>e){enemyList = e;}
    // void deleteEnemy(std::shared_ptr<Enemy> e);

    // 行为
    void moveManager(std::shared_ptr<Enemy> e);
    void allEnemyMove(){
        for (const auto& enemy : enemyList){
            if(!enemy->getAlive() || enemy->getIcy()) continue;
            moveManager(enemy);
        }
    }

    void healthSystem();
public slots:
    void noMoreNewEnemy_slot(){
        noMoreNewEnemy = true;
    }
signals:
    void enemyReachEnd();
    void allEnemyDead();
    // ~EnemyManager(){ }
};


#endif
