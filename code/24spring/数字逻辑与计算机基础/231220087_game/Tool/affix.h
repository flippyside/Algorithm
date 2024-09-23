#ifndef AFFIX_H
#define AFFIX_H
#include "Basic/role.h"
#include "Basic/tower.h"
#include<QObject>
#include <Qmutex>
#include <QMutexLocker>

class EnemyManager;
class TowerManager;


class Affix{
    friend class AffixManager;

    AffixType type;
    std::shared_ptr<Role> owner = nullptr; // 装备该词缀的角色
    bool isOccupied = false;
    // int time;
    QMutex mutex;
public:
    Affix(AffixType type = awake) : type(type){

    }

// 访问
   AffixType getType() const { return type;}
   bool getOccupied()const{return isOccupied; }
   std::shared_ptr<Role> getOwner()const{return owner;}
   //int getTime(){return time; }


// 修改
   void changeOwner(std::shared_ptr<Role> p){owner = p; }
   void setOccupied(bool a){isOccupied = a; }
   void setType(AffixType t){type = t;}


// 行为
    void effect();    // 添加效果
    void remove();    // 移除效果

    ~Affix(){ }
};

class AffixManager : public QObject {
    friend class Game;
    Q_OBJECT
    // 存有所有词缀, 管理词缀与塔之间的关系
protected:
    std::vector<std::shared_ptr<Affix>> affixList_tower;
    std::vector<std::shared_ptr<Affix>> affixList_enemy;
    std::shared_ptr<EnemyManager> enemyManager;
    std::shared_ptr<TowerManager> towerManager;
    std::map<std::string, int> affixNum_tower;// 词缀总数
    std::map<std::string, int> free_affixNum_tower;// 空闲词缀数
    QMutex mutex;
public:

    AffixManager(    std::shared_ptr<EnemyManager> enemyManager, std::shared_ptr<TowerManager> towerManager)
        : enemyManager(enemyManager), towerManager(towerManager){
        affixNum_tower["Awake"] = 0;
        affixNum_tower["Icy"] = 0;
        affixNum_tower["Poison"] = 0;
        affixNum_tower["AOE"] = 0;
        free_affixNum_tower["Awake"] = 0;
        free_affixNum_tower["Icy"] = 0;
        free_affixNum_tower["Poison"] = 0;
        free_affixNum_tower["AOE"] = 0;
    }

    // 访问
    std::vector<std::shared_ptr<Affix>>& getAffixList_tower(){return affixList_tower; }
    const std::vector<std::shared_ptr<Affix>> getAffixList_tower()const{return affixList_tower; }
    std::vector<std::shared_ptr<Affix>>& getAffixList_enemy(){return affixList_enemy; }
    const std::vector<std::shared_ptr<Affix>> getAffixList_enemy()const{return affixList_enemy; }

    const std::map<std::string, int> getAffixNum_tower()const {return affixNum_tower;}
    const std::map<std::string, int> getFree_affixNum_tower()const {return free_affixNum_tower;}

    std::shared_ptr<Affix> searchFreeAffix(AffixType type);
    std::shared_ptr<Affix> searchOccupiedAffix(AffixType type);

    // 修改
    void addAffix_tower(std::shared_ptr<Affix> a){
        affixList_tower.push_back(a);
    }
    void addAffix_enemy(std::shared_ptr<Affix> a){
        affixList_enemy.push_back(a);
    }

    // 行为



public slots:
    void randomCreateForEnemy();
    void randomCreateForTower(); // 随机
    void randomBind();// 敌人随机装备词缀


};

#endif // AFFIX_H \
    // switch(type){ \
    //     // 持续时间无限 \
    // case AffixType::awake : case AffixType::speedUp: case AffixType::aoe : {time = 0;break;}

// // 作用时间
// case AffixType::icy :{time = 2000; break;}
// case AffixType::poison:{time = 5000; break;}
// // 时间间隔
// case AffixType::teleport:{time = 10000; break;}
// }
