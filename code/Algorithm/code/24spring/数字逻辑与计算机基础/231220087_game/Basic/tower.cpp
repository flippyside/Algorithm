#include<Basic/tower.h>
#include "enemy.h"



void Tower::setBlockList(std::shared_ptr<Enemy> e){
    if(e && e->getAlive()){
        blockList = e;
        e->setBlocked(true);
    }
}
void Tower::die(){
    setAlive(false);
    if(blockList && blockList->getAlive()) blockList->setBlocked(false);
}

void Tower::levelUP(){// 最高3级
    switch(level){
    case 0:{
        attackPower += 50;
        break;
    }
    case 1:{
        defence += 5;
        break;
    }
    case 2:{
        hp += 200;
        totalHP += 200;
        break;
    }
    }
    if(level<3) level++;
}

int Tower::getTrueAttackPower(){
    if(!getAffixSlot().empty()){
        for(const auto& it : getAffixSlot()) {
            if(it->getType() == AffixType::awake){ // 可叠加
                int true_attackPower = attackPower * 2;
                return true_attackPower;
            }
        }
    }
    return attackPower;
}

int Tower::getTrueAttackInterval(){
    if(!getAffixSlot().empty()){
        for(const auto& it : getAffixSlot()) {
            if(it->getType() == AffixType::awake){ // 可叠加
                int true_attackInterval = attackInterval / 2;
                return true_attackInterval;
            }
        }
    }
    return attackInterval;
}

// 部署塔
void TowerManager::TowerArrange(std::shared_ptr<Tower> t,const Coordinate& coo){

    if(map.isInEndPoints(coo) || map.isInStartPoints(coo)){
        qInfo() << "invalid position: start or end point";
        return;
    }

    if(t->getType() == TowerType::MeleeTower){
        // 检查位置是否合法
        if(!map.isInPath(coo)){
            qInfo() << "invalid position: not MTable"; return;
        }
        std::shared_ptr<Tower> it = cmap->findTowerInGrid(coo);
        if(it != NULL){qInfo() << "invalid position: occupied"; return;}
    }
    else{// 远程塔
        // 检查位置是否合法
        if(!map.isInRTable(coo)){
            qInfo() << "invalid position: not RTable";
            return;
        }
        auto it = cmap->findTowerInGrid(coo);
        if(it){qInfo() << "invalid position: occupied"; return;}
    }
    // 合法, 部署t
    t->position = coo;
    cmap->addTowerInGrid(t, coo); // 修改状态地图
    towerList.push_back(t); // 加入队列
    qInfo()<<"arrange success"; return;
}

